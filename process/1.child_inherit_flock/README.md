# Description

This prarent process flocks one file, then forks one child process. Then the parent exits directly, while the child sleeps 30 seconds.
At that time, run this process again. You would find the second instance blocks until the child of first instance exits.

# Conclusion

The flock is shared between the parent and child process. Although the flock would be release automatically when process exits, it must be done until both of parent and child exit.
