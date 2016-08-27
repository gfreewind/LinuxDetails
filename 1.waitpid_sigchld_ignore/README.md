# 描述

这个程序将SIGCHLD设置为SIG_IGN，然后fork两个子进程。第一个子进程会sleep 30秒，
而第二个子进程会直接退出。

父进程先waitpid第2个进程，然后在waitpid第一个。

# Description

This program sets SIGCHLD as SIG_IGN, and forks two child processes. The first
child sleeps 30 seconds, and second child exits directly.

The parent process waits the second child firstly, then waits the first.

# 结论

当SIGCHLD被置为SIG_IGN时，waitpid仍然会立刻返回，而不是等待所有子进程终止
才退出。
这与"man 2 waitpid"的描述不符。

# Conclustion
When the SIGCHILD is ignored, the waitpid still return immediately without
waiting all child processes terminate.

It is oppsite the description of "man 2 waitpid".

# 原因

当使用waitpid等待子进程2时，这里指定了pid。但是由于SIGCHLD是被设置为忽略的，
所以子进程2退出后，其状态不会保存。
因此waitpid会因为得不到指定进程的状态而返回错误，No child process，并立刻返回。

# Reason

Becasue when waitpid for child2, we specify the pid. But the SICHLD is ignored,
the exit status of child2 is not saved.
So the waitpid fail to get the child2's status and returns error, and show the reason "No child processes", then
return immediately




