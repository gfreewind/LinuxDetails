# Description 

The parent process opens one file "./test1.txt", and forks one child.
Both of parent and child opens another file "./test2.txt" after fork.
Then the parent writes "I'm parent\n" into these two files, while child does
the same thing too.

How about the content of these two files?

# Answer

./test1.txt:


I'm parent

I'm child

./test2.txt

I'm child

Notic: The content may be different in your environment.
The schedule policy of fork is decided by /proc/sys/kernel/sched_child_runs_first.

Anyway, the parent and child overlap the content of "./test2.txt",
but "./test1.txt" not.

# Conclusion
The fd of parent and child shares one same fd and owns same kernel struct which
maintains the file offset. So the content of "./test1.txt" does not overlap.

The fd which is created after fork owns its file strcture in kernel, so the file
offset is not shared between parent and child.


