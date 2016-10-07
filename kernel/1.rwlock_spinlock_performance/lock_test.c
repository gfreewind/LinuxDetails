#include <linux/init.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/irqflags.h>
#include <linux/preempt.h>

static void lock_test(void)
{
#define TEST_TIMES				(100000000)
#define ONE_SEC_NS				(1000000000)

	DEFINE_RWLOCK(rwlock);
	spinlock_t spinlock;
	struct timespec	start;
	struct timespec end;
	struct timespec cost;
	unsigned long long startns;
	unsigned long long endns;
	int i;

	preempt_disable();
	local_bh_disable();
	local_irq_disable();

	spin_lock_init(&spinlock);

	getnstimeofday(&start);
	for (i = 0; i < TEST_TIMES; ++i) {
		read_lock(&rwlock);
		read_unlock(&rwlock);	
	}
	getnstimeofday(&end);

	startns = start.tv_sec*ONE_SEC_NS+start.tv_nsec;
	endns = end.tv_sec*ONE_SEC_NS+end.tv_nsec;
	cost.tv_sec = end.tv_sec-start.tv_sec;
	if (end.tv_nsec >= start.tv_nsec) {
		cost.tv_nsec = end.tv_nsec-start.tv_nsec;
	} else {
		--cost.tv_sec;
		cost.tv_nsec = end.tv_nsec+ONE_SEC_NS-start.tv_nsec;
	}

	printk(KERN_INFO "wrlock start: %ld s, %ld ns\n",
		start.tv_sec, start.tv_nsec);
	printk(KERN_INFO "wrlock end: %ld s, %ld ns\n",
		end.tv_sec, end.tv_nsec);
	printk(KERN_INFO "wrlock costs %ld s, %ld ns\n",
		cost.tv_sec, cost.tv_nsec);

	getnstimeofday(&start);
	for (i = 0; i < TEST_TIMES; ++i) {
		spin_lock(&spinlock);
		spin_unlock(&spinlock);	
	}
	getnstimeofday(&end);

	startns = start.tv_sec*ONE_SEC_NS+start.tv_nsec;
	endns = end.tv_sec*ONE_SEC_NS+end.tv_nsec;
	cost.tv_sec = end.tv_sec-start.tv_sec;
	if (end.tv_nsec >= start.tv_nsec) {
		cost.tv_nsec = end.tv_nsec-start.tv_nsec;
	} else {
		--cost.tv_sec;
		cost.tv_nsec = end.tv_nsec+ONE_SEC_NS-start.tv_nsec;
	}

	printk(KERN_INFO "spinlock start: %ld s, %ld ns\n",
		start.tv_sec, start.tv_nsec);
	printk(KERN_INFO "spinlock end: %ld s, %ld ns\n",
		end.tv_sec, end.tv_nsec);
	printk(KERN_INFO "spinlock costs %ld s, %lu ns\n",
		cost.tv_sec, cost.tv_nsec);

	local_irq_enable();
	local_bh_enable();
	preempt_enable();
}

static int lock_test_init(void)
{
	printk(KERN_INFO "Lock test init\n");

	lock_test();
	return 0;
}

static void lock_test_exit(void)
{
	printk(KERN_INFO "Lock test exit\n");
}

module_init(lock_test_init);
module_exit(lock_test_exit);

