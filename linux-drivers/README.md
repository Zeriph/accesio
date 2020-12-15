# ACCES I/O Linux driver repository

This is the Github repository of the ACCES I/O Products, Inc. Linux driver set.

There are quite a few ACCES products already within the Linux kernel, and some should "just work", if you plug them in to your Linux machine. However, there are some that have certain quirks (like our Pericom line of our serial devices).

This repository houses the drivers and tests for the PCI, Serial and USB* line of Linux drivers.

Until further notice, this will be the defacto repository for the new unified Linux driver set.

## Getting Started

Simply grab the latest source through a `git clone https://github.com/accesio/linux-drivers.git` or by grabbing the compressed file from [here](https://github.com/accesio/linux-drivers/archive/master.zip).

Assuming you have the source downloaded to `/usr/src/acces`, the following will get you setup and running:

```
cd /usr/src/acces
sudo make install
```

This will preform a `make` on the PCI, serial and USB* drivers, and then subsequently do a `sudo make install` to install them.

If you have a device supported by the PCI driver, when the drivers are installed, there should be an entry created under `/dev/acces` to which you can `echo` and `dd` to/from. For more information on using the device you can view the [tests](https://github.com/accesio/linux-drivers/tree/master/tests) or you can browse the [source tree](https://github.com/accesio/linux-drivers/tree/master/acces).

### Platform support

Currently, these drivers only support the Linux kernel (2.6.39 and above); support for MacOS and the various BSD systems will be added in the future.

The Linux drivers are designed to run a wide array of architectures and should build and install on all of the various distributions of Linux and CPU's.

The drivers have been tested on Arch, Slackware (and it's derivatives), Debian (and it's derivatives), RedHat (and it's derivatives), just to name a few; due to the [numerous ecosystems of Linux distributions](http://distrowatch.com) that exists, we cannot test every combination of hardware/kernel, which is why our code is built as generic as possible against the base kernel. If you cannot build our drivers, please make sure you have your latest kernel source, and that your kernel supports the functionality that our drivers use (like IRQ's).

## License

The drivers and source within this repository have a permissive free license that allows you to make derivative works or use the source how you see fit without worry of license issues - see the [LICENSE.md](https://github.com/accesio/linux-drivers/blob/master/LICENSE.md) file for details.