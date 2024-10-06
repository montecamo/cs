import re
from socket import *
import os


import os.path
import sys

cwd = os.getcwd()
server_socket = socket(AF_INET, SOCK_STREAM)

server_socket.bind(("", 8000))
server_socket.listen(1)

while True:
    connection_socket, addr = server_socket.accept()
    message = connection_socket.recv(2048).decode()
    match = re.match(r"GET\s\/(.*?)\s.*", message)

    if not match:
        continue

    path = match.group(1)
    full_path = os.path.join(cwd, path)

    if os.path.exists(full_path):
        print("kek")
    else:
        response = "\r\n".join(["HTTP/1.1 404", "Content-Length: 0", "\r\n"])
        connection_socket.send(response.encode())
        connection_socket.close()
