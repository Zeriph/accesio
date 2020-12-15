CONFIG_MODULE_SIG = n
obj-m += accesio_pci.o
CC		:= gcc
KVERSION        := $(shell uname -r)
KDMOD		:= /lib/modules/$(KVERSION)
KDIR		:= $(KDMOD)/build

all:
	$(MAKE) CC=$(CC) -C $(KDIR) M=$(PWD) modules

clean: 
	$(MAKE) CC=$(CC) -C $(KDIR) M=$(PWD) clean
	modprobe -r accesio_pci
	rm -vf $(KDMOD)/accesio_pci.ko $(KDMOD)/extra/accesio_pci.ko

install:
	$(MAKE) CC=$(CC) -C $(KDIR) M=$(PWD) modules_install
	cp accesio_pci.ko $(KDMOD)
	depmod -a
	modprobe accesio_pci