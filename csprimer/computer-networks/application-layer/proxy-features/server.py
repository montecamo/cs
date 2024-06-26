import http.server

PORT = 9000


class NoCacheHTTPRequestHandler(http.server.SimpleHTTPRequestHandler):
    def send_response_only(self, code, message=None):
        super().send_response_only(code, message)
        self.send_header("Cache-Control", "max-age=3600")


if __name__ == "__main__":
    http.server.test(HandlerClass=NoCacheHTTPRequestHandler, port=PORT)
