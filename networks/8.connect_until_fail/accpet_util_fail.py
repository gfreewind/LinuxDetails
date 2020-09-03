#!/usr/bin/python

import sys
import socket

if __name__ == "__main__":
    if len(sys.argv) <= 2:
        print "Please specify the address & port"
        exit(1)

    addr = sys.argv[1]
    port = int(sys.argv[2])
    print "Listen {}:{}".format(addr, port)

    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.bind((addr, port))
    sock.listen(1024)

    socks = []
    while True:
        try:
            new_sock = sock.accept()
            socks.append(new_sock)
            print "Establish {} connections".format(len(socks))
        except Exception as e:
            print "Unexpected error: " + str(e)
            break
