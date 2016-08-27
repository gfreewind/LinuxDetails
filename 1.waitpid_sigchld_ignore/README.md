# Description

This program sets SIGCHLD as ignore, and forks two child processes. The first
child sleeps 30 seconds, and second child exits directly.

The parent process waits the second child firstly, then waits the first.

# Conclustion
When the SIGCHILD is ignored, the waitpid still return immediately without
waiting all child processes terminate.

It is oppsite the description of "man 2 waitpid".


# Reason

Becasue when waitpid for child2, we specify the pid. But the SICHLD is ignored,
the exit status of child1 is not saved.
So the waitpid returns error, and show the reason "No child processes", then
return immediately




