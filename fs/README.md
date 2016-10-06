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

mmap和write在写1024，2048，4096字节时性能基本一致；但是写入5120时，mmap的性能仍然比write差。

## Question

When disable the write cache, how about the performance of mmap write and write?

## Answer  

When write 1024, 2048, 4096 bytes, they are same.
When write 5120 bytes, the performance of mmap write is worse than write. 






