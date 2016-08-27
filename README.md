
# General
This project is used to investigate on the details of Linux programming.
Every directory focuses on one topic.

Becasue they are test codes, so I don't perform the delicated error handler. Just exit the process :))

Every directory verifies one problem about Linux programing. You could check the codes and README.md in every dir to get the detail answer.

#1. waitpid_sigchld_ignore: 

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

## Qeustion

How about wait any pid instead of wait specific pid in case2?  Is it different ? Is it block too?

## Answer
Yes! This waitpid blocks until all childs exits.


# 3.child_inherit_flock

## Question
The flock could be released automatically when process exits. How about it when parent holds one flock and forks one child then exit? Is the flock released after parent exits?

## Answer
No!

# 4.child_share_flock

## Question

The flock is shared between parent and child process. The parent process holds one flock and forks one child process. Now the flock is shared. How about the parent releases the lock and tries to lock it while child is alive ? Is it blocked because child still holds the lock?

## Answer

No !




