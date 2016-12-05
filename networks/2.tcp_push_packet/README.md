# Description

How to make sure kernel send one packet when call send every time

# Conclusion

TCP_NODELAY option:  
Enable TCP_NODELAY, it could send one TCP packet with PUSH every send call.

	int opt = 1;
        setsockopt(fd, SOL_TCP, TCP_NODELAY, &opt, sizeof(opt));


Packet Trace:  
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode  
listening on lo, link-type EN10MB (Ethernet), capture size 65535 bytes  
22:22:20.926263 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [S], seq 2443224076, win 43690, options [mss 65495,sackOK,TS val 398752434 ecr 0,nop,wscale 7], length 0  
22:22:20.926305 IP 127.0.16.0.6000 > 127.0.0.1.46806: Flags [S.], seq 2966002025, ack 2443224077, win 43690, options [mss 65495,sackOK,TS val 398752434 ecr 398752434,nop,wscale 7], length 0  
22:22:20.926331 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [.], ack 1, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
22:22:20.926371 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [P.], seq 1:2, ack 1, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 1  
22:22:20.926404 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [P.], seq 2:3, ack 1, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 1  
22:22:20.926426 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [P.], seq 3:4, ack 1, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 1  
22:22:20.926428 IP 127.0.16.0.6000 > 127.0.0.1.46806: Flags [.], ack 2, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
22:22:20.926442 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [P.], seq 4:5, ack 1, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 1  
22:22:20.926458 IP 127.0.16.0.6000 > 127.0.0.1.46806: Flags [.], ack 3, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
22:22:20.926463 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [P.], seq 5:6, ack 1, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 1  
22:22:20.926474 IP 127.0.16.0.6000 > 127.0.0.1.46806: Flags [.], ack 4, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
22:22:20.926494 IP 127.0.16.0.6000 > 127.0.0.1.46806: Flags [.], ack 5, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
22:22:20.926493 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [F.], seq 6, ack 1, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
22:22:20.926509 IP 127.0.16.0.6000 > 127.0.0.1.46806: Flags [.], ack 6, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
22:22:20.927565 IP 127.0.16.0.6000 > 127.0.0.1.46806: Flags [F.], seq 1, ack 7, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
22:22:20.927613 IP 127.0.0.1.46806 > 127.0.16.0.6000: Flags [.], ack 2, win 342, options [nop,nop,TS val 398752434 ecr 398752434], length 0  
