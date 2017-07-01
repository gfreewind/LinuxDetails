# 1.tcp_close_with_data

## 问题

当没有读取完所有的TCP数据，就关闭套接字，是否会有问题？
这种情况与读完数据再关闭是否一致?

## Question

Is it ok that close the TCP socket before read all bytes?
Is it same as that close fd after read all bytes?

## Answer
No!

# 2.tcp_push_packet

## 问题

如何让TCP协议栈不对数据做优化，一次send调用就对应一个数据包。


# 3.tcp_read_hit_rst

## 问题


当tcp套接字read调用，遇到对端发送RST报文时，返回值是什么？

## Answer

read返回-1，errno是ECONNRESET，即Connection reset by peer


# 4.reuse_addr_option


## 问题


什么时候需要使用SO_REUSEADDR?


## Answer


当proto, addr, 和port三个元素都相同时，需要使用SO_REUSEADDR。

其中INADDR_ANY表示任意地址，其与所有地址视为相同。


# 5.no_listen_tcp_conn  

## 问题  
没有listen调用，是否可以建立tcp连接


# 6.tcp_keepalive_reporter
当TCP的KeepAlive机制判定连接超时，应用层如何得到通知。  



# 7.tcp_send_rst  
应用层如何强制TCP发送RST中断连接。 

