# 1.mmap_write_performance  

## 问题  

对比mmap和write的性能，哪个性能更好？

## 结论  

利用mmap写文件的性能不如直接写文件。

## Question 

Compare the performance of mmap and write, which is better?

## Answer  

The performance of mmap write is worser than direct write.

# 2.mmap_read_performance  

## 问题  

对比mmap和read的性能，哪个性能更好？

## 结论  

利用mmap读文件的性能不如直接读文件。

## Question 

Compare the performance of mmap and read, which is better?

## Answer  

The performance of mmap read is worse than direct read.

# 3.mmap_write_sync_nocache

## 问题

一般情况下，write都会使用cache，本例中禁止了cache，再次比较mmap和write的性能

## 结论
随着写入字节的增加，mmap消耗的时间也越来越多。
但是write消耗的时间并没有明显增加。

## Question

When disable the write cache, how about the performance of mmap write and write?

## Answer  

The cost increases with bytes increasing when use mmap.
But the cost of write does not increase.

# 4.mmap_read_sync_nocache

## 问题

同上。本例中禁止了cache，再次比较mmap和read的性能

## 性能 
随着读入字节的增加，mmap消耗的时间也在增加。
但是read消耗的时间增加的非常少







