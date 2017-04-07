ifneq ($(KERNELRELEASE),)
	obj-m := lockbench.o
else
	#KERNELDIR ?= /lib/modules/`uname -r`/build
	KERNELDIR ?= /home/justin/open-sailing/kernel/
#	MAKE = make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu-
	MAKE = make ARCH=arm64 
all:
	$(MAKE) -C $(KERNELDIR) M=`pwd` modules

clean:
	$(MAKE) -C $(KERNELDIR) M=`pwd` clean
	rm -f Modules.symvers
endif
