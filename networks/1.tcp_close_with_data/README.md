# Description

There are one TCP server thread and one TCP client thread.
At the first time, the server close fd after read all bytes from client.
At the second time, the server close fd after accept. 

# Conclusion

When close TCP socket, it sends the RST if there are some bytes which are
pending to ack.
This behaviro is defined in the section 2.17 of RFC 2525.

To reproduce this issue, you may run this test program some times.
Because the TCP ack is sent by kernel.
Server codes just tris to close fd before kernel response ack.
When achieve it, the output is following:

server: receive 6 bytes: First
server: close fd at the first time
client: ret is 0
server: close fd at the second time
client: ret is -1: Connection reset by peer

But the first close never cause RST is sent.


