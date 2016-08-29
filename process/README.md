# 1.child_inherit_flock

## 问题

当进程退出时，flock可以被自动释放。那么当父进程持有flock并且fork了一个子进程，然后退出。这个flock锁是否还会在父进程推出时释放吗？

## Question
The flock could be released automatically when process exits. How about it when parent holds one flock and forks one child then exit? Is the flock released after parent exits?

## Answer
No!

# 2.child_share_flock

## 问题

既然flock是由父进程和子进程共享，那么父进程持有flock锁并fork一个子进程，这时flock是共享的。那么这时在子进程未退出的情况下，父进程
释放了锁，然后再次尝试获取这个flock，会怎么样呢？父进程会因为子进程持有锁而阻塞吗？

## Question

The flock is shared between parent and child process. The parent process holds one flock and forks one child process. Now the flock is shared. How about the parent releases the lock and tries to lock it while child is alive ? Is it blocked because child still holds the lock?

## Answer

No !




