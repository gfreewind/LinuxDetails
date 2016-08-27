# Description 

The prarent process holds one flock, then forks one child process. Now the flock is shared between with child and parent. Then child sleeps 30 seconds, and parent releases the lock, then tries to get the lock again.


# Conclusion

The parent could get the flock imediately although child does not exit. Because the flock is shared between child and parent, actually there is one instance of flock between child and parent. So when the parent releases the flock, the child does not own the flock yet. So parent could get the lock again immediately.


