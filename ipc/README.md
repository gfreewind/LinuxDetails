# 1.mkfifo_with_unblock

## 问题

调用mkfifo时，如果是只读打开且没有其它进程写入打开时，这个调用会阻塞。
同理，如果是写模式打开且没有其它进程读取打开时，这个调用也会阻塞。
那么当调用设置了非阻塞的标志时，会有什么现象呢？

## Question

When invokes mkfifo with O_RDONLY and there is no process which opened
the fifo with O_WRONLY already, this call would be blocked.
It is blocked too that when invokes mkfifo with O_WRONLY and there is no
process which opened the fifo with O_RDONLY.

Then how about invokes mkfifo with O_NONBLOCK.

## 答案
如果在没有读取者时，非阻塞写模式打开管道文件会返回错误；
如果在没有写入者时，非阻塞读模式打开管道文件会成功打开.

## Answer
mkfifo returns OK with O_RDONLY|O_NONBLOCK eventhough no O_WRONLY process, while
it faied with O_WRONLY|O_NONBLOCK when no O_RDONLY process.

