# 简介

这个工程是用于研究Linux环境编程的一些细节。
其中每个目录聚焦于一个主题。

因为这些是测试代码，所以没有细致的处理错误处理。就直接退出进程了事:))

每一个目录都验证Linux编程的一个问题。要了解细节的话，可以进入具体的目录得到详细的解答。


# General
This project is used to investigate on the details of Linux programming.
Every directory focuses on one topic.

Becasue they are test codes, so I don't perform the delicated error handler. Just exit the process :))

Every directory verifies one problem about Linux programing. You could check the codes and README.md in every dir to get the detail answer.

#1. waitpid_sigchld_ignore: 

## 问题

当SIGCHLD被设置为SIG_IGN时，对waitpid有什么影响呢？
根据"man 2 waitpid"的描述，是否会真的阻塞呢？

## Question


When SIGCHLD is ignored, how about waitpid?

The following is from "man 2 waitpid"
/******************************************************************************************************/


POSIX.1-2001 specifies that if the disposition of SIGCHLD is set to SIG_IGN or the  SA_NOCLDWAIT  flag
is  set  for SIGCHLD (see sigaction(2)), then children that terminate do not become zombies and a call
to wait() or waitpid() will block until all children have terminated, and then fail with errno set  to
ECHILD.   (The  original  POSIX  standard left the behavior of setting SIGCHLD to SIG_IGN unspecified.
Note that even though the default disposition of SIGCHLD is "ignore", explicitly setting the  disposi‐
tion to SIG_IGN results in different treatment of zombie process children.)

Linux  2.6 conforms to the POSIX requirements.  However, Linux 2.4 (and earlier) does not: if a wait()
or waitpid() call is made while SIGCHLD is being ignored, the call behaves just as though SIGCHLD were
not  being  ignored,  that  is,  the  call blocks until the next child terminates and then returns the
process ID and status of that child.


/******************************************************************************************************/

Is it really blocked?

## Answer
No!

# 2.waitanypid_sigchld_ignore

## 问题

当使用waitpid等待任意pid时，而不是指定pid，又会怎么样呢？
与问题1会有什么不同吗？是否也会阻塞呢？

## Qeustion

How about wait any pid instead of wait specific pid in case2?  Is it different ? Is it block too?

## Answer
Yes! This waitpid blocks until all childs exits.


# 3.child_inherit_flock

## 问题

当进程退出时，flock可以被自动释放。那么当父进程持有flock并且fork了一个子进程，然后退出。这个flock锁是否还会在父进程推出时释放吗？

## Question
The flock could be released automatically when process exits. How about it when parent holds one flock and forks one child then exit? Is the flock released after parent exits?

## Answer
No!

# 4.child_share_flock

## 问题

既然flock是由父进程和子进程共享，那么父进程持有flock锁并fork一个子进程，这时flock是共享的。那么这时在子进程未退出的情况下，父进程
释放了锁，然后再次尝试获取这个flock，会怎么样呢？父进程会因为子进程持有锁而阻塞吗？

## Question

The flock is shared between parent and child process. The parent process holds one flock and forks one child process. Now the flock is shared. How about the parent releases the lock and tries to lock it while child is alive ? Is it blocked because child still holds the lock?

## Answer

No !




