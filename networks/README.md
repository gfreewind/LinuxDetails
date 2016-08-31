# 1.tcp_close_with_data

## 问题

当没有读取完所有的TCP数据，就关闭套接字，是否会有问题？
这种情况与读完数据再关闭是否一致?

## Question

Is it ok that close the TCP socket before read all bytes?
Is it same as that close fd after read all bytes?

## Answer
No!




