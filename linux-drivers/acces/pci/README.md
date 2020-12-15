# ACCES I/O Linux PCI drivers

To build the driver, you'll need to ensure you have the latest kernel source and headers; see your respective distributions documentation on how to achieve this (usually it's just issuing a `$PAC_MAN install linux-headers-generic` where `$PAC_MAN` is your distributions package manger, like `yum` or `apt`).

Please note: the following assumes you have unzipped the current ACCES Linux driver source to `/usr/src/acces`.

## PCI driver install

The ACCES PCI driver is a loadable kernel module, to install it do the following:

```
cd /usr/src/acces/acces/pci
make
sudo make install
```

Note: if you've unzipped the `linux-drivers` source to `/usr/src/acces`, then the drivers would be under `/usr/src/acces/acces` and the tests under `/usr/src/acces/tests`.

To verify that the module is loaded, you can do `lsmod | grep accesio` and you should see an entry for `accesio_pci`, additionally, there should be a new device class under the `/dev` folder where any devices that are plugged into the machine will be added. For example, if you have a PCIe-DIO48S, you would see `/dev/accesio/pcie_dio48s_0`. Since these are character devices, you can use common commands, like `echo` and `dd`, to read and write to the device to verify they are working as well.

## Using the device

### Shell and command line access

If you're using the command line to communicate with the device, you can specify the register offset by seeking however the specific command allows. For example, with `dd`, you can specify the `skip` argument if you're reading from the device and the `seek` argument if you're writing to it:

Reading:  `dd if=/dev/accesio/pcie_dio48s_0 bs=1 count=1 skip=5 2>/dev/null`
Writing:  `echo -n "\0" | dd of=/dev/accesio/pcie_dio48s_0 bs=1 seek=5 2>/dev/null`

Since `dd` just spits back what it gets, to see the actual value read, you can use something like `hexdump`:

`dd if=/dev/accesio/pcie_dio48s_0 bs=1 count=1 skip=5 2>/dev/null | hexdump -e '/1 "0x" "%02X" "\n"'`

Note: `2>/dev/null` is being piped on `dd` because `dd` prints the records written to `stderr`.

As a character device, you can only read 1 byte of information at a time; this can be modified in the source to buffer if you wish, but at this time, there are no plans to add internal buffering to the driver. However, there is pseudo write buffering; when you write data to the card through a normal file write operation, the length and buffer are taken into account within the driver.

As an example; if you were to do the following: `echo -n "\0\0\0\0\0" | dd of=/dev/accesio/pcie_dio48s_0 bs=1 seek=5 2>/dev/null`, the driver would receive 5 bytes of `'\0'` and write all 5 bytes at the 5th register offset (since in this command we're telling `dd` to `seek=5`).

Of course, if you specify only 1 byte to be written, then only 1 byte will be received by the driver, for example: `echo -n "\0\0\0\0\0" | dd of=/dev/accesio/pcie_dio48s_0 bs=1 count=1 seek=5 2>/dev/null`, in this command, we specify `dd` to have a `count=1`, thus the driver will only receive 1 byte of data, even though `dd` received 5.

In this way, you can write small "watchdog" type scripts instead of needing an additional programming language/environment (like C/Python/Java, etc.).

### Programming language support

Since the driver supports 1 byte reads and multi-byte writes when accessing the device as a file, as well, since there is the `libacces.c` C wrapper, just about any language can be utilized to communicate with the device.

### libacces

This driver supports the `libacces.c` C wrapper library. For more information see the [HOWTO-LIB](https://github.com/accesio/linux-drivers/blob/master/acces/HOWTO-LIB.md).

### api.h

This driver supports the `api.h` ACCES API. For more information see the [HOWTO-API](https://github.com/accesio/linux-drivers/blob/master/acces/HOWTO-API.md).

## Supported devices

The following is a list (from [`module/ids.h`](https://github.com/accesio/linux-drivers/blob/master/acces/pci/module/ids.h)) of devices supported by this driver:

ACCES I/O PCI Vender ID (VID): `0x494F`

Device Product ID's (PID)

Product        | ID (HEX)
---------------| --------
PCIE_DIO_24    | 0x0C52
PCIE_DIO_24D   | 0x0C53
PCIE_DIO_24S   | 0x0E53
PCIE_DIO_24DS  | 0x0E54
PCIE_DIO_24DC  | 0x0E55
PCIE_DIO_24DCS | 0x0E56
PCIE_DIO_48    | 0x0C61
PCIE_DIO_48S   | 0x0E61
PCIE_DIO_72    | 0x0C6A 
PCIE_DIO_96    | 0x0C71
PCIE_DIO_120   | 0x0C79
PCIE_IIRO_8    | 0x0F02
PCIE_IIRO_16   | 0x0F09
PCI_DIO_24H    | 0x0C50
PCI_DIO_24D    | 0x0C51
PCI_DIO_24H_C  | 0x0E51
PCI_DIO_24D_C  | 0x0E52
PCI_DIO_24S    | 0x0E50
PCI_DIO_48*    | 0x0C60
PCI_DIO_48H*   | 0x0C60
PCI_DIO_48S*   | 0x0E60
PCI_DIO_48HS*  | 0x0E60
PCI_DIO_72     | 0x0C68
PCI_DIO_96     | 0x0C70
PCI_DIO_96CT   | 0x2C50
PCI_DIO_96C3   | 0x2C58
PCI_DIO_120    | 0x0C78
P104_DIO_48S   | 0x0E62
P104_DIO_96    | 0x0C69
PCI_AI12_16    | 0xACA8
PCI_AI12_16A   | 0xACA9
PCI_AIO12_16   | 0xECA8
PCI_A12_16A    | 0xECAA
PCI_DA12_16    | 0x6CB0
PCI_DA12_8     | 0x6CA8
PCI_DA12_6     | 0x6CA0
PCI_DA12_4     | 0x6C98
PCI_DA12_2     | 0x6C90
PCI_DA12_16V   | 0x6CB1
PCI_DA12_8V    | 0x6CA9
PCI_IIRO_8     | 0x0F00
PCI_IIRO_16    | 0x0F08
PCI_IDI_48     | 0x0920
PCI_IDO_48     | 0x0520
PCI_IDIO_16    | 0x0DC8
LPCI_A16_16A   | 0xECE8
LPCI_IIRO_8    | 0x0F01
PCI_WDG_2S     | 0x1250
PCI_WDG_CSM    | 0x22C0
PCI_WDG_IMPAC  | 0x12D0
MPCIE_DIO_24S  | 0x0100

*Please note that the PCI_DIO_48H will be reported as PCI_DIO_48 due to the similar PID, but the functionality will not be reduced. This is true of the PCI_DIO_48S and PCI_DIO_48SH cards.
