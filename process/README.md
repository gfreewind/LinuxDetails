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


# 3.fork_and_print

## 问题

一个有关print和fork有趣的问题

## Question

One interesting problem about printf and fork.

## Answer

Please check out the codes in 3.fork_and_print :))


# 4.fork_with_fd

## 问题
当父子进程同时往一个文件里写数据是什么样的情况呢？
情况1:子进程的fd是fork继承下来的；
情况2:父子进程的fd是fork以后分别打开的;
这两种情况写入的结果一样的吗？

## Question
How about the content when both of parent and child process write the same file?
case1: The child's fd is inherited from parent;
case2: The fd of parent and child is opened after fork;
How about these two cases? Is it same?

## Answer

No. It's totally different!!!





