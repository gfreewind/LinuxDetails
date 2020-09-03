#!/usr/bin/python

import sys
import socket

if __name__ == "__main__":
    if len(sys.argv) <= 2:
        print "Please specify the address & port"
        exit(1)

    addr = sys.argv[1]
    port = int(sys.argv[2])
    print "Connect {}:{}".format(addr, port)

    socks = []
    while True:
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.connect((addr, port))
            print "Connect {} times".format((len(socks)))
            socks.append(sock)
        except Exception as e:
            print "Unexpect error:" + str(e)
            break
