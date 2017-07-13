#include <linux/init.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/delay.h>


#define USE_UNINTERRUPTIBLE

static struct task_struct *sleep_task = NULL;

static int thread_func(void *data)
{
    while (1) {
        if (kthread_should_stop()) {
            break;
        }

#ifdef USE_UNINTERRUPTIBLE
        //ssleep(1);
	schedule_timeout_uninterruptible(HZ);
#else
	
	schedule_timeout_interruptible(HZ);
#endif
    }

    return 0;
}

static int __init sleep_task_init(void)
{
    sleep_task = kthread_create(thread_func, NULL, "sleep_task");
    if (IS_ERR(sleep_task)) {
        printk(KERN_ERR "sleep_task: kthread_create failed\n");
        sleep_task = NULL;
        return -1;
    }

    wake_up_process(sleep_task);

    printk(KERN_INFO "sleep_task: init successfully\n");

    return 0;
}

static void __exit sleep_task_exit(void)
{
    if (sleep_task) {
        kthread_stop(sleep_task);
        sleep_task = NULL;
    }

    printk(KERN_INFO "sleep_task: exit successfully\n");
}

MODULE_LICENSE("GPL");

module_init(sleep_task_init);
module_exit(sleep_task_exit);
