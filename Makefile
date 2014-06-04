KERNELDIR ?= /lib/modules/$(shell uname -r)/build

ifeq ($(KERNELRELEASE),)

PWD := $(shell pwd)

.PHONY: build clean

build:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	$(RM) *.o *~ core .depend .*.cmd *.ko *.mod.c
	$(RM) modules.order  Module.symvers
else

$(info Building with KERNELRELEASE = ${KERNELRELEASE})
obj-m		:= addone.o timefunc.o
timefuncmod-y	:= timefunc.o
addonemod-y	:= addone.o
endif
