# ACCES I/O Linux drivers

To build the drivers, you'll need to ensure you have the latest kernel source and headers; see your respective distributions documentation on how to achieve this (usually it's just issuing a `$PAC_MAN install linux-headers-generic` where `$PAC_MAN` is your distributions package manger, like `yum` or `apt`).

This folder is laid out as follows:
```
./              : source root (this folder)
./common        : Common header files
./pci           : The PCI Linux driver
./serial        : The serial Linux driver
./usb           : The USB Linux driver
./api.h         : The C API
./libacces.c    : The C wrapper library
./LICENSE.md    : The license
./Makefile      : The make system
./README.md     : This readme file
```

## Common header files

This folder contains common header files utilized by the Linux drivers; this folder is also referenced in the C API to expose some functionality of the drivers.

No user code is contained in this folder.

## The PCI Linux driver

This folder contains the source and Makefile for the Linux PCI driver.

<details>
    <summary>Supported devices</summary>
    <p>ACCES Vendor ID: 0x494F | Product ID's: PCIE_DIO_24 (0x0C52), PCIE_DIO_24D (0x0C53), PCIE_DIO_24S (0x0E53), PCIE_DIO_24DS (0x0E54), PCIE_DIO_24DC (0x0E55), PCIE_DIO_24DCS (0x0E56), PCIE_DIO_48 (0x0C61), PCIE_DIO_48S (0x0E61), PCIE_DIO_72 (0x0C6A), PCIE_DIO_96 (0x0C71), PCIE_DIO_120 (0x0C79), PCIE_IIRO_8 (0x0F02), PCIE_IIRO_16 (0x0F09), PCI_DIO_24H (0x0C50), PCI_DIO_24D (0x0C51), PCI_DIO_24H_C (0x0E51), PCI_DIO_24D_C (0x0E52), PCI_DIO_24S (0x0E50), PCI_DIO_48 (0x0C60), PCI_DIO_48H (0x0C60), PCI_DIO_48S (0x0E60), PCI_DIO_48HS (0x0E60), PCI_DIO_72 (0x0C68), PCI_DIO_96 (0x0C70), PCI_DIO_96CT (0x2C50), PCI_DIO_96C3 (0x2C58), PCI_DIO_120 (0x0C78), P104_DIO_48S (0x0E62), P104_DIO_96 (0x0C69), PCI_AI12_16 (0xACA8), PCI_AI12_16A (0xACA9), PCI_AIO12_16 (0xECA8), PCI_A12_16A (0xECAA), PCI_DA12_16 (0x6CB0), PCI_DA12_8 (0x6CA8), PCI_DA12_6 (0x6CA0), PCI_DA12_4 (0x6C98), PCI_DA12_2 (0x6C90), PCI_DA12_16V (0x6CB1), PCI_DA12_8V (0x6CA9), PCI_IIRO_8 (0x0F00), PCI_IIRO_16 (0x0F08), PCI_IDI_48 (0x0920), PCI_IDO_48 (0x0520), PCI_IDIO_16 (0x0DC8), LPCI_A16_16A (0xECE8), LPCI_IIRO_8 (0x0F01), PCI_WDG_2S (0x1250), PCI_WDG_CSM (0x22C0), PCI_WDG_IMPAC (0x12D0), MPCIE_DIO_24S (0x0100)</p>
</details>

For more information on supported devices, how to build/install the driver, and how to communicate with the device, see the [README](https://github.com/accesio/linux-drivers/blob/master/acces/pci/README.md) of the PCI folder.

## The serial Linux driver

This folder contains information for the Linux serial driver.

<details>
    <summary>Supported devices</summary>
    <p>ACCES Vendor ID: 0x494F | Product ID's: PCIE_COM_2SDB (0x1051), MPCIE_COM_2S (0x1053), PCIE_COM_4SDB (0x105C), MPCIE_COM_4S (0x105E), PCIE_COM232_2DB (0x1091), MPCIE_COM232_2 (0x1093), PCIE_COM232_4DB (0x1099), MPCIE_COM232_4 (0x109B), PCIE_COM_2SMDB (0x10D1), MPCIE_COM_2SM (0x10D3), PCIE_COM_4SMDB (0x10DA), MPCIE_COM_4SM (0x10DC), MPCIE_ICM485_1 (0x1108), MPCIE_ICM422_2 (0x1110), MPCIE_ICM485_2 (0x1111), MPCIE_ICM422_4 (0x1118), MPCIE_ICM485_4 (0x1119), PCIE_ICM_2S (0x1152), PCIE_ICM_4S (0x115A), PCIE_ICM232_2 (0x1190), MPCIE_ICM232_2 (0x1191), PCIE_ICM232_4 (0x1198), MPCIE_ICM232_4 (0x1199), PCIE_ICM_2SM (0x11D0), PCIE_COM422_4 (0x105A), PCIE_COM485_4 (0x105B), PCIE_COM422_8 (0x106A), PCIE_COM485_8 (0x106B), PCIE_COM232_4 (0x1098), PCIE_COM232_8 (0x10A9), PCIE_COM_4SM (0x10D9), PCIE_COM_8SM (0x10E9), PCIE_ICM_4SM (0x11D8)</p>
</details>

For more information on supported devices, how to build/install the driver, and how to communicate with the device, see the [README](https://github.com/accesio/linux-drivers/blob/master/acces/serial/README.md) of the serial folder.

## The USB Linux driver

This folder contains the source and Makefile for the Linux USB driver.

<details>
    <summary>Supported devices</summary>
    <p>ACCES Vendor ID: 0x1605 | Product ID's: USB_DIO_32 (0x8001), USB_DIO_32I (0x8004), USB_DIO_24 (0x8005), USB_DIO_48 (0x8002), USB_DIO_96 (0x8003), USB_DIO_24_CTR6 (0x8006), USB_DI_16A_REV_A1 (0x8008), USB_DO_16A_REV_A1 (0x8009), USB_DI_16A_REV_A2 (0x800A), USB_DIO_16H (0x800C), USB_DI_16A (0x800D), USB_DO_16A (0x800E), USB_DIO_16A (0x800F), USB_IIRO_16 (0x8010), USB_II_16 (0x8011), USB_RO_16 (0x8012), USB_IIRO_8 (0x8014), USB_II_8 (0x8015), USB_IIRO_4 (0x8016), USB_IDIO_16 (0x8018), USB_II_16_OLD (0x8019), USB_IDO_16 (0x801A), USB_IDIO_8 (0x801C), USB_II_8_OLD (0x801D), USB_IDIO_4 (0x801E), USB_CTR_15 (0x8020), USB_IIRO4_2SM (0x8030), USB_IIRO4_COM (0x8031), USB_DIO_16_RO_8 (0x8032), USB_DIO_48_DO_24 (0x803C), USB_DIO_24_DO_12 (0x803D), USB_DO_24 (0x803E), PICO_DIO_16_RO_8 (0x8033), USBP_II8_IDO_4A (0x8036), USB_AI16_16A (0x8040), USB_AI16_16E (0x8041), USB_AI12_16A (0x8042), USB_AI12_16 (0x8043), USB_AI12_16E (0x8044), USB_AI16_64MA (0x8045), USB_AI16_64ME (0x8046), USB_AI12_64MA (0x8047), USB_AI12_64M (0x8048), USB_AI12_64ME (0x8049), USB_AI16_32A (0x804A), USB_AI16_32E (0x804B), USB_AI12_32A (0x804C), USB_AI12_32 (0x804D), USB_AI12_32E (0x804E), USB_AI16_64A (0x804F), USB_AI16_64E (0x8050), USB_AI12_64A (0x8051), USB_AI12_64 (0x8052), USB_AI12_64E (0x8053), USB_AI16_96A (0x8054), USB_AI16_96E (0x8055), USB_AI12_96A (0x8056), USB_AI12_96 (0x8057), USB_AI12_96E (0x8058), USB_AI16_128A (0x8059), USB_AI16_128E (0x805A), USB_AI12_128A (0x805B), USB_AI12_128 (0x805C), USB_AI12_128E (0x805D), USB_AO_ARB1 (0x8068), USB_AO16_16A (0x8070), USB_AO16_16 (0x8071), USB_AO16_12A (0x8072), USB_AO16_12 (0x8073), USB_AO16_8A (0x8074), USB_AO16_8 (0x8075), USB_AO16_4A (0x8076), USB_AO16_4 (0x8077), USB_AO12_16A (0x8078), USB_AO12_16 (0x8079), USB_AO12_12A (0x807A), USB_AO12_12 (0x807B), USB_AO12_8A (0x807C), USB_AO12_8 (0x807D), USB_AO12_4A (0x807E), USB_AO12_4 (0x807F), USB_AIO16_16A (0x8140), USB_AIO16_16E (0x8141), USB_AIO12_16A (0x8142), USB_AIO12_16 (0x8143), USB_AIO12_16E (0x8144), USB_AIO16_64MA (0x8145), USB_AIO16_64ME (0x8146), USB_AIO12_64MA (0x8147), USB_AIO12_64M (0x8148), USB_AIO12_64ME (0x8149), USB_AIO16_32A (0x814A), USB_AIO16_32E (0x814B), USB_AIO12_32A (0x814C), USB_AIO12_32 (0x814D), USB_AIO12_32E (0x814E), USB_AIO16_64A (0x814F), USB_AIO16_64E (0x8150), USB_AIO12_64A (0x8151), USB_AIO12_64 (0x8152), USB_AIO12_64E (0x8153), USB_AIO16_96A (0x8154), USB_AIO16_96E (0x8155), USB_AIO12_96A (0x8156), USB_AIO12_96 (0x8157), USB_AIO12_96E (0x8158), USB_AIO16_128A (0x8159), USB_AIO16_128E (0x815A), USB_AIO12_128A (0x815B), USB_AIO12_128 (0x815C), USB_AIO12_128E (0x815D)</p>
</details>

For more information on supported devices, how to build/install the driver, and how to communicate with the device, see the [README](https://github.com/accesio/linux-drivers/blob/master/acces/usb/README.md) of the USB folder.

## The C API

The file [api.h](https://github.com/accesio/linux-drivers/blob/master/acces/api.h), contains the C API to communicate with the current line of PCI and USB* cards.

This is the ACCES API that you would use to communicate on a lower-level with the devices.

For more information and how to use it, please see the [HOWTO-API](https://github.com/accesio/linux-drivers/blob/master/acces/HOWTO-API.md) readme.

*Note: until the USB driver is completed, the current API only has support for communication with our PCI devices.

## The C wrapper library

The file [libacces.c](https://github.com/accesio/linux-drivers/blob/master/acces/libacces.c), is a simple C wrapper that exposes a few function for external use in other languages; this C file does not reference any of the ACCES source and is completely self contained and portable.

For more information and how to use it, please see the [HOWTO-LIB](https://github.com/accesio/linux-drivers/blob/master/acces/HOWTO-LIB.md) readme.

## The license

The drivers and source within this repository have a permissive free license that allows you to make derivative works or use the source how you see fit without worry of license issues - see the [LICENSE.md](https://github.com/accesio/linux-drivers/blob/master/LICENSE.md) file for details.

## The make system

This Makefile can be used ot make and install the drivers as well as make the C wrapper library (`libacces.so`). The following is a list of what can be made with this Makefile:

make          | what
--------------| --------
(default)     | lib
all           | lib, drivers
lib           | compiles libacces.c to ../bin/libacces.so
lib-optimized | compiles libacces.c to ../bin/libacces.so with -O2
drivers       | pci-driver, serial-driver, usb-driver
install       | calls 'make install' in each driver directory
pci-driver    | cd pci && $(MAKE)
serial-driver | cd serial && $(MAKE)
usb-driver    | cd usb && $(MAKE)
clean         | calls 'make clean' in each driver directory and removes binary files

## This readme file

You're reading it ;)
