# Description

This program sets SIGCHLD as SIG_IGN, and forks two child processes. The first
child sleeps 30 seconds, and second child exits directly.

The parent process waits the second child firstly, then waits the first.

# Conclustion
When the SIGCHLD is set as SIG_IGN, parent invokes waitpid to wait any child process.
The waitpid would block until all childs exit.

It conforms to the description of "man 2 waitpid".

# Reason

Why the result is different with example1?
Because this waitpid is not specified the pid, so it would not return error when
one child process exits. Only when all child processes exit, the waitpid find there
is no child, and return error.



