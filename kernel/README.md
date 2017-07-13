# 1.rwlock_spinlock_performance

## 问题 

rwlock与spinlock的性能对比，哪个性能更优？

## Question

How about the performance of rwlock and spinlock?

## Answer

In the old kernel, the performance of rwlock is worse than spinlock.
But it is better than spinlock in latest kernel.

You could test it in your environment.


# 2.sleep_test  

## 问题  

当线程sleep时，其状态为TASK_UNINTERRUPTIBLE和TASK_INTERRUPTIBLE有什么区别？

## Question 
 
What's the difference when task's state is sleep with TASK_UNINTERRUPTIBLE or TASK_INTERRUPTIBLE?


## Answer  

When task state is TASK_UNINTERRUPTIBLE, it is counted into the CPU load.  
You would find the CPU load is increasing always when enable the macro USE_UNINTERRUPTIBLE.  
BTW, the ssleep would set the task state as TASK_UNINTERRUPTIBLE.

The following link is my old blog about this topic.   
http://www.linxh.blog.chinaunix.net/uid-23629988-id-3242488.html
