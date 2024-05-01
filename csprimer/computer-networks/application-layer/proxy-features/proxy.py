import socket
from copy import deepcopy
import asyncio
import math
from datetime import datetime

from log import log
import gzip

import enum
from parser import Parser, parse_cache_control
from serializer import serialize


UPSTREAM_ADDR = ("127.0.0.1", 9000)


class ECompression(enum.Enum):
    NONE = 0
    GZIP = 1


class EmptyException(Exception):
    pass


def compress(algorithm, data):
    match (algorithm):
        case ECompression.GZIP:
            pass
        case ECompression.NONE:
            return data

    return data


class CacheEntry:
    def __init__(self, request_parser, response_parser):
        self.request_parser = request_parser
        self.update(response_parser)

    def seconds_passed(self):
        return math.floor((datetime.now() - self.timestamp).total_seconds())

    def is_stale(self):
        return self.seconds_passed() > int(self.cache_control["max-age"])

    def is_older_than(self, seconds):
        return self.seconds_passed() > int(seconds)

    def create_response(self):
        data = deepcopy(self.response_parser.data)

        data["headers"][b"Age"] = str(self.seconds_passed()).encode()

        return serialize("RES", data)

    def update(self, parser):
        self.response_parser = parser
        self.cache_control = parse_cache_control(parser.headers["cache-control"])

        self.refresh()

    def refresh(self):
        self.timestamp = datetime.now()

    def create_request(self):
        data = self.request_parser["data"]

        return serialize(
            "REQ",
            {
                "method": data["method"],
                "url": data["url"],
                "version": data["version"],
                "headers": {
                    b"Host": data["headers"][b"Host"],
                    b"Accept": data["headers"][b"Accept"],
                    b"If-Modified-Since": self.response_parser["data"]["headers"][
                        b"Last-Modified"
                    ],
                },
                "content": b"",
            },
        )


cache = {}

# 1. make handling upstream - async

VALIDATION_HEADERS = set(["if-modified-since", "if-none-match"])


class Proxy:
    def __init__(self, client):
        upstream = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        upstream.connect(UPSTREAM_ADDR)

        # log(f"Connected to {UPSTREAM_ADDR}")

        self.state = "OPEN"
        self.client = client
        self.upstream = upstream
        self.parser = Parser("REQ")

    def reset_parser(self):
        self.parser = Parser("REQ")

    def handle_requestt(self, type):
        future = asyncio.Future()

        data = self.client.recv(4096)
        if not data:
            future.set_exception(EmptyException)

        if type == "REQ":
            log(f"-> *    {len(data)}B")
        else:
            log(f"   * <- {len(data)}B")

    def send_upstream(self, parser):
        self.upstream.send(serialize("REQ", parser.data))

        log(f"   * -> {len(self.parser.bytes)}B")

        parser = Parser("RES")

        while True:
            data = self.upstream.recv(4096)

            if not data:
                return parser

            log(f"   * <- {len(data)}B")

            for byte in data:
                parser.parse(byte.to_bytes(1, byteorder="big"))

            if parser.state == "FINISH":
                return parser

    def close(self):
        self.upstream.close()
        self.client.close()

        self.state = "CLOSE"

    def has_cache(self, parser):
        if not parser.url in cache:
            return False

        entry = cache[parser.url]

        if entry.is_stale():
            print("stale")
            return False

        if VALIDATION_HEADERS & set(parser.headers):
            print("validation headers")
            return False

        if "cache-control" in parser.headers:
            cache_control = parse_cache_control(parser.headers["cache-control"])

            if "no-cache" in cache_control:
                print("no-cache")
                return False

            if entry.is_older_than(cache_control["max-age"]):
                print("olrder than")
                return False

        return True

    def handle_request(self, parser):
        if self.has_cache(parser):
            entry = cache[parser.url]

            self.client.send(entry.create_response())
            log(f"<- *    {len(entry.create_response())}B")

            print("cache hit")

            return

        print("haven't cache", parser.url)

        global compression
        try:
            if "gzip" in self.parser.headers["accept-encoding"]:
                compression = ECompression.GZIP
        except KeyError:
            compression = ECompression.NONE

        response_parser = self.send_upstream(parser)

        match (compression):
            case ECompression.GZIP:
                parser.data["headers"][b"Content-Encoding"] = b"gzip"
                parser.data["content"] = gzip.compress(parser.data["content"])
                parser.data["headers"][b"Content-Length"] = bytes(
                    str(len(parser.data["content"])), "utf-8"
                )

        if "cache-control" in response_parser.headers:
            if response_parser.url == "200":
                if parser.url in cache:
                    cache[parser.url].update(response_parser)
                else:
                    print("save cache")
                    cache[parser.url] = CacheEntry(self.parser, response_parser)

            if response_parser.url == "304" and parser.url in cache:
                cache[parser.url].refresh()

        self.client.send(serialize("RES", response_parser.data))

        log(f"<- *    {len(response_parser.bytes)}B")

    def handle(self):
        data = self.client.recv(4096)

        if not data:
            self.close()
            return

        log(f"-> *    {len(data)}B")

        for byte in data:
            self.parser.parse(byte.to_bytes(1, byteorder="big"))

        if self.parser.state == "FINISH":
            self.handle_request(self.parser)

            self.reset_parser()
