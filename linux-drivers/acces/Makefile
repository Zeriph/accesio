default: lib

all: lib drivers

lib:
	mkdir -p ../bin
	cc -fPIC -shared libacces.c -o ../bin/libacces.so

lib-optimized:
	mkdir -p ../bin
	cc -fPIC -shared libacces.c -Wall -Wno-unused-function -O2 -o ../bin/libacces.so

drivers: pci-driver serial-driver usb-driver

install:
	cd pci && $(MAKE) install
	cd serial && $(MAKE) install
	cd usb && $(MAKE) install

pci-driver:
	cd pci && $(MAKE)

serial-driver:
	cd serial && $(MAKE)

usb-driver:
	cd usb && $(MAKE)

clean:
	rm -vf ../bin/libacces.so
	cd pci && $(MAKE) clean
	cd serial && $(MAKE) clean
	cd usb && $(MAKE) clean