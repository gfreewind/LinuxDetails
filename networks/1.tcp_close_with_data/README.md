# Description

There are one TCP server thread and one TCP client thread.
At the first time, the server close fd after read all bytes from client.
At the second time, the server close fd after accept. 

# Conclusion

When close TCP socket, it sends the RST if there are some bytes which are
not received by app.
This behaviro is defined in the section 2.17 of RFC 2525.

The following codes are from the kernel codes, tcp_close

        /* As outlined in RFC 2525, section 2.17, we send a RST here because
         * data was lost. To witness the awful effects of the old behavior of
         * always doing a FIN, run an older 2.1.x kernel or 2.0.x, start a bulk
         * GET in an FTP client, suspend the process, wait for the client to
         * advertise a zero window, then kill -9 the FTP client, wheee...
         * Note: timeout is always zero in such a case.
         */
        if (data_was_unread) {
                /* Unread data was tossed, zap the connection. */
                NET_INC_STATS_USER(sock_net(sk), LINUX_MIB_TCPABORTONCLOSE);
                tcp_set_state(sk, TCP_CLOSE);
                tcp_send_active_reset(sk, sk->sk_allocation);
        } else if (sock_flag(sk, SOCK_LINGER) && !sk->sk_lingertime) {


server: receive 6 bytes: First
server: close fd at the first time
client: ret is 0
server: close fd at the second time
client: ret is -1: Connection reset by peer

But the first close never cause RST is sent.


