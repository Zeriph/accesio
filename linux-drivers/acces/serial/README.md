# ACCES I/O Linux serial drivers

If you are utilizing an unmodified kernel since 2007, and the default serial module is running, you do not need any additional drivers.

## Serial driver install

The serial driver included with the base Linux kernel is usually enabled and built in by default; to verify it it's running you can do `lsmod | grep serial` and you should see an entry for `serial`.

To verify your products were recognized, you can do the following: `lspci | grep -v acces` and you should see entries for `ACCES I/O` with the device ID's of the products you have installed.

## Using the device

This serial driver utilizes the 8250 PCI driver in the Linux kernel; to that, there are a [few](https://www.tldp.org/HOWTO/Serial-HOWTO.html) [resources](https://www.cyberciti.biz/faq/find-out-linux-serial-ports-with-setserial/) that can [help](https://unix.stackexchange.com/questions/242778/what-is-the-easiest-way-to-configure-serial-port-on-linux) get the `ttyS` setup, and have more in-depth information than can be covered through a simple README.

If you cannot preform a loopback tests (e.g. `echo "test" > /dev/ttySX` in one terminal, then `cat /dev/ttySX` in another), refer to the hardware manual for your device to get the specifics, like baud-rate and divisor, to configure it properly before utilizing. You can set these values utilizing the `setserial` or `stty` tools in Linux.

## Supported devices

The following is a list of devices supported by this driver:

ACCES I/O Serial Vender ID (VID): `0x494F`

Device Product ID's (PID)

Product         | ID (HEX)
----------------| --------
PCIE_COM_2SDB   | 0x1051
MPCIE_COM_2S    | 0x1053
PCIE_COM_4SDB   | 0x105C
MPCIE_COM_4S    | 0x105E
PCIE_COM232_2DB | 0x1091
MPCIE_COM232_2  | 0x1093
PCIE_COM232_4DB | 0x1099
MPCIE_COM232_4  | 0x109B
PCIE_COM_2SMDB  | 0x10D1
MPCIE_COM_2SM   | 0x10D3
PCIE_COM_4SMDB  | 0x10DA
MPCIE_COM_4SM   | 0x10DC
MPCIE_ICM485_1  | 0x1108
MPCIE_ICM422_2  | 0x1110
MPCIE_ICM485_2  | 0x1111
MPCIE_ICM422_4  | 0x1118
MPCIE_ICM485_4  | 0x1119
PCIE_ICM_2S     | 0x1152
PCIE_ICM_4S     | 0x115A
PCIE_ICM232_2   | 0x1190
MPCIE_ICM232_2  | 0x1191
PCIE_ICM232_4   | 0x1198
MPCIE_ICM232_4  | 0x1199
PCIE_ICM_2SM    | 0x11D0
PCIE_COM422_4   | 0x105A
PCIE_COM485_4   | 0x105B
PCIE_COM422_8   | 0x106A
PCIE_COM485_8   | 0x106B
PCIE_COM232_4   | 0x1098
PCIE_COM232_8   | 0x10A9
PCIE_COM_4SM    | 0x10D9
PCIE_COM_8SM    | 0x10E9
PCIE_ICM_4SM    | 0x11D8
