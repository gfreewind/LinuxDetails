obj-m := sleep_test.o

KDIR := /lib/modules/`uname -r`/build

modules:
	make -C $(KDIR) M=$(PWD) modules

clean: 
	rm -f *.ko *.o *.mod.o *.mod.c *.order *.symvers

