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


