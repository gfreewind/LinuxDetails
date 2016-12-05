#include <linux/init.h>
#include <linux/module.h>
#include <linux/time.h>
#include <linux/irqflags.h>
#include <linux/preempt.h>

#define TEST_TIMES				(100000000)
#define ONE_SEC_NS				(1000000000)

static void time_cost(struct timespec *start, struct timespec *end, 
	struct timespec *cost)
{
	unsigned long long startns;
	unsigned long long endns;

	startns = start->tv_sec * ONE_SEC_NS + start->tv_nsec;
	endns = end->tv_sec * ONE_SEC_NS + end->tv_nsec;
	cost->tv_sec = end->tv_sec - start->tv_sec;
	if (end->tv_nsec >= start->tv_nsec) {
		cost->tv_nsec = end->tv_nsec - start->tv_nsec;
	} else {
		--cost->tv_sec;
		cost->tv_nsec = end->tv_nsec + ONE_SEC_NS - start->tv_nsec;
	}

	return;
}

static void lock_test(void)
{
	DEFINE_RWLOCK(rwlock);
	spinlock_t spinlock;
	DEFINE_MUTEX(mutex);
	struct timespec	start;
	struct timespec end;
	struct timespec cost;
	int i;

	preempt_disable();
	local_bh_disable();
	local_irq_disable();

	spin_lock_init(&spinlock);

	/* rwlock case */
	getnstimeofday(&start);
	for (i = 0; i < TEST_TIMES; ++i) {
		read_lock(&rwlock);
		read_unlock(&rwlock);	
	}
	getnstimeofday(&end);

	time_cost(&start, &end, &cost);

	printk(KERN_INFO "wrlock start: %ld s, %ld ns\n",
		start.tv_sec, start.tv_nsec);
	printk(KERN_INFO "wrlock end: %ld s, %ld ns\n",
		end.tv_sec, end.tv_nsec);
	printk(KERN_INFO "wrlock costs %ld s, %ld ns\n",
		cost.tv_sec, cost.tv_nsec);

	/* spinlock case */
	getnstimeofday(&start);
	for (i = 0; i < TEST_TIMES; ++i) {
		spin_lock(&spinlock);
		spin_unlock(&spinlock);	
	}
	getnstimeofday(&end);

	time_cost(&start, &end, &cost);

	printk(KERN_INFO "spinlock start: %ld s, %ld ns\n",
		start.tv_sec, start.tv_nsec);
	printk(KERN_INFO "spinlock end: %ld s, %ld ns\n",
		end.tv_sec, end.tv_nsec);
	printk(KERN_INFO "spinlock costs %ld s, %lu ns\n",
		cost.tv_sec, cost.tv_nsec);

	/* rcu case */
	getnstimeofday(&start);
	for (i = 0; i < TEST_TIMES; ++i) {
		rcu_read_lock();
		rcu_read_unlock();	
	}
	getnstimeofday(&end);

	time_cost(&start, &end, &cost);

	printk(KERN_INFO "rculock start: %ld s, %ld ns\n",
		start.tv_sec, start.tv_nsec);
	printk(KERN_INFO "rculock end: %ld s, %ld ns\n",
		end.tv_sec, end.tv_nsec);
	printk(KERN_INFO "rculock costs %ld s, %lu ns\n",
		cost.tv_sec, cost.tv_nsec);

	/* mutex case */
	getnstimeofday(&start);
	for (i = 0; i < TEST_TIMES; ++i) {
		mutex_lock(&mutex);
		mutex_unlock(&mutex);	
	}
	getnstimeofday(&end);

	time_cost(&start, &end, &cost);

	printk(KERN_INFO "mutex start: %ld s, %ld ns\n",
		start.tv_sec, start.tv_nsec);
	printk(KERN_INFO "mutex end: %ld s, %ld ns\n",
		end.tv_sec, end.tv_nsec);
	printk(KERN_INFO "mutex costs %ld s, %lu ns\n",
		cost.tv_sec, cost.tv_nsec);

	local_irq_enable();
	local_bh_enable();
	preempt_enable();
}

static int lock_test_init(void)
{
	
	printk(KERN_INFO "Lock test init\n");

	lock_test();

	printk(KERN_INFO "Lock test exit\n");

	/* Return -1 so that we needn't use rmmod to uninstall module */
	return -1;
}

static void lock_test_exit(void)
{
	printk(KERN_INFO "Lock test exit\n");
}

module_init(lock_test_init);
module_exit(lock_test_exit);

