# 1.vsz_and_rss

## 问题

对比VSZ和RSS，当申请内存时，只会增加VSZ。 
只有真正使用这块内存时，RSS才会增加。 
也就是说，应用层分配内存时，内核仅仅是分配了地址空间，并没有建立与物理内存的
映射关系。

## Question

Comparing with the VSZ and RSS.
Only VSZ is increased when just allocate memory.
The RSS is increased only when app uses the mem.
In other words, when app allocates memories, kernel just allocates the virtual
memory address without corresponding physical page.



