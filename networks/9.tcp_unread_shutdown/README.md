# Description

How about the return value of tcp read when receive one TCP RST?  
There are two threads.  
The server closes the socket after receives the client packet and left the packet in the socket.  
So it would trigger one TCP RST to client from server.  

# Conclusion

The read returns "-1", and errno is set as "ECONNRESET"，"Connection reset by peer".
