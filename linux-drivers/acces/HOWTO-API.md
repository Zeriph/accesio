# The `api.h` C API for ACCES I/O products.

## Table of Contents
1. What the API is and is not
2. How to build it
3. How to use it
4. Functions

## What the API is and is not

The API is a `C99` header-only API of static functions that allow you to read and
write to a device, on a lower level, more succinctly.

## How to build it

Since the API is a header file, there's nothing additional to build, simply
be sure to include the ACCES source directory in your build includes, for
example: `gcc my_file.c -I /my/src -I /usr/src/acces`

## How to use it

Make sure to include the ACCES source directory in your build includes, then
you can simply do the following in your C/C++ file:

```
#include <acces/api.h>
```

After you've included the header, you can now use the ACCES API and it's
structures.

The main structures to note are `accesio_pci_device` and `accesio_usb_device`.
This is the object that you will utilize to open, read from and write to an
attached card.

The structures themselves, can be included without the API functions by doing
the following:

```
#include <acces/api/types.h> // for accesio_pci_device
```

The separation is to allow you to have a static reference that can then be
used in other areas of code; the API is designed as a header
only API to give you more flexibility in building your applications.

The API's functions can be stripped out of the header and made `extern`
functions if you wish, but in this way, you'll need to modify your build system
to include the `api.c` file where the `extern` API function declarations now
reside.

Since there are more simplistic functions in this API, by keeping it a header
only API, you only need to include a few headers where needed in your source
and not muck up your build systems.

## Functions:

### NAME
```c
static int accesio_get_device_info(accesio_pci_device* device);
```

### DESCRIPTION
Retrieves the device information and stores it in the `device` parameter passed in.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to an `accesio_pci_device` type where information about the opened device is stored.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure the error code is returned.


### NAME
```c
static int accesio_get_usb_device_info(accesio_usb_device* device);
```

### DESCRIPTION
Retrieves the device information and stores it in the `device` parameter passed in.

### PARAMETER(S)
`accesio_usb_device* device` - A reference to an `accesio_usb_device` type where information about the opened device is stored.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure the error code is returned.


### NAME
```c
static int accesio_open_device(const char* path, accesio_pci_device* device);
```

### DESCRIPTION
Opens a device handle to the path specified. If the device is opened successfully, the device information will be stored in the `device` parameter, otherwise it will be zero'd out.

### PARAMETER(S)
`const char* path` - The path to the device to open for communication, (e.g. `"/dev/accesio/pcie_dio48s_0"`)
`accesio_pci_device* device` - A reference to an `accesio_pci_device` type where information about the opened device is stored.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure the error code is returned.


### NAME
```c
static int accesio_open_usb_device(const char* path, accesio_usb_device* device);
```

### DESCRIPTION
Opens a device handle to the path specified. If the device is opened successfully, the device information will be stored in the `device` parameter, otherwise it will be zero'd out.

### PARAMETER(S)
`const char* path` - The path to the device to open for communication, (e.g. `"/dev/accesio/usb_dio_48_0"`)
`accesio_usb_device* device` - A reference to an `accesio_usb_device` type where information about the opened device is stored.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure the error code is returned.


### NAME
```c
static int accesio_open_path(const char* path,
                             int* file_descriptor,
                             uint32_t* device_index,
                             uint32_t* product_id,
                             uint8_t* bar,
                             uint32_t* base_start,
                             uint32_t* base_end,
                             uint32_t* base_length);
```

### DESCRIPTION
Opens a device handle to the path specified. If the device is opened successfully, the device information will be stored in the parameters passed in, otherwise they will be zero'd out.

### PARAMETER(S)
`const char* path` - The path to the device to open for communication.
`int* file_descriptor` - A reference where the opened file handle is stored.
`uint32_t* device_index` - A reference where the device index is stored.
`uint32_t* product_id` - A reference where the product ID of the device is stored.
`uint8_t* bar` - A reference where the main BAR of the device is stored.
`uint32_t* base_start` - A reference where the main region start is stored.
`uint32_t* base_end` - A reference where the main region end is stored.
`uint32_t* base_length` - A reference where the main region length is stored.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure the error code is returned.


### NAME
```c
static int accesio_open_usb_path(const char* path,
                                 int* file_descriptor,
                                 uint32_t* device_index,
                                 uint32_t* product_id,
                                 uint16_t* in_bulk_addr,
                                 uint16_t* out_bulk_addr,
                                 uint16_t* in_ctrl_addr,
                                 uint16_t* out_ctrl_addr);
```

### DESCRIPTION
Opens a device handle to the path specified. If the device is opened successfully, the device information will be stored in the parameters passed in, otherwise they will be zero'd out.

### PARAMETER(S)
`const char* path` - The path to the device to open for communication.
`int* file_descriptor` - A reference where the opened file handle is stored.
`uint32_t* device_index` - A reference where the device index is stored.
`uint32_t* product_id` - A reference where the product ID of the device is stored.
`uint16_t* in_bulk_addr` - A reference where the bulk endpoint in-address of the device is stored.
`uint16_t* out_bulk_addr` - A reference where the bulk endpoint out-address of the device is stored.
`uint16_t* in_ctrl_addr` - A reference where the control endpoint in-address of the device is stored.
`uint16_t* out_ctrl_addr` - A reference where the control endpoint out-address of the device is stored.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure the error code is returned.


### NAME
```c
static int accesio_close_device(accesio_pci_device* device);
```

### DESCRIPTION
Closes a system character device that has been opened with `accesio_open_device`.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.

### RETURN VALUE
On success, the device structure is zero'd out and ACCESIO_SUCCESS is returned, on failure the error code is returned.


### NAME
```c
static int accesio_close_device(accesio_usb_device* device);
```

### DESCRIPTION
Closes a system character device that has been opened with `accesio_open_usb_device`.

### PARAMETER(S)
`accesio_usb_device* device` - A reference to the device opened.

### RETURN VALUE
On success, the device structure is zero'd out and ACCESIO_SUCCESS is returned, on failure the error code is returned.


### NAME
```c
static int accesio_close_path(int file_descriptor);
```

### DESCRIPTION
Closes the handle of an opened device.

### PARAMETER(S)
`int file_descriptor` - The file descriptor to close

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_cancel_wait_irq(accesio_pci_device* device);
```

### DESCRIPTION
Cancels an interupt wait request on the specified device.

### PARAMETER(S) 
`accesio_pci_device* device` - A reference to the device opened.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_wait_for_irq(accesio_pci_device* device);
```

### DESCRIPTION
Waits for an interrupt request on the device.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_set_offset(accesio_pci_device* device, uint8_t register_offset);
```

### DESCRIPTION
Sets the register offset to read/write to of the device.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.
`uint8_t register_offset` - The register offset to assign to the device to read from and write to.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_set_byte(accesio_pci_device* device, uint8_t data);
```

### DESCRIPTION
Sets the device to send byte size data.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.
`uint8_t data` - The 8-bit data to set.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_set_word(accesio_pci_device* device, uint16_t data);
```

### DESCRIPTION          Sets the device to send word size data.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.
`uint16_t data` - The 16-bit data to set.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_set_dword(accesio_pci_device* device, uint32_t data);
```

### DESCRIPTION
Sets the device to send double word (DwORD) size data.

### PARAMETER(S)
`accesio_pci_device* device` -   A reference to the device opened.
`uint32_t data` - The 32-bit data to set.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_read8(accesio_pci_device* device, uint8_t register_offset, uint8_t* data);
```

### DESCRIPTION Reads a byte of data from the device and stores the the value in the `data` referenced passed in.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.
`uint8_t register_offset` - The register offset to read from
`uint8_t* data` - A reference to the 8-bit data that will be set on a successful device read.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_read16(accesio_pci_device* device, uint8_t register_offset, uint16_t* data);
```

### DESCRIPTION
Reads a word of data from the device and stores the the value in the `data` referenced passed in.

### PARAMETER(S)
`accesio_pci_device* device` -               A reference to the device opened.
`uint8_t register_offset`     The register offset to read from
`uin16_t* data` - A reference to the 16-bit data that will be set on a successful device read. 

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_read32(accesio_pci_device* device, uint8_t register_offset, uint32_t* data);
```

### DESCRIPTION
Reads a DWORD of data from the device and stores the the value in the `data` referenced passed in.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.
`uint8_t register_offset` - The register offset to read from
`uint32_t* data` - A reference to the 32-bit data that will be set on a successful device read. 

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_read_byte(accesio_pci_device* device, uint8_t register_offset, uint8_t* data);
```

### DESCRIPTION
A synonym for `accesio_read8`.


### NAME
```c
static int accesio_read_word(accesio_pci_device* device, uint8_t register_offset, uint16_t* data);
```

### DESCRIPTION
A synonym for `accesio_read16`.


### NAME
```c
static int accesio_read_dword(accesio_pci_device* device, uint8_t register_offset, uint32_t* data);
```

### DESCRIPTION
A synonym for `accesio_read32`.


### NAME
```c
static int accesio_read(accesio_pci_device* device);
```

### DESCRIPTION
Reads from the device specified in the structure. This function assumes you are familiar with the inner structure of `accesio_pci_device` and have set all of the values appropriately.

### PARAMETER(S)
`accesio_pci_device* device` -   A reference to the device opened.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_read_usb(accesio_usb_device* device);
```

### DESCRIPTION
Reads from the device specified in the structure. This function assumes you are familiar with the inner structure of `accesio_usb_device` and have set all of the values appropriately.

### PARAMETER(S)
`accesio_usb_device* device` -   A reference to the device opened.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_read_unchecked(int file_descriptor,
                                  uint8_t register_offset,
                                  enum accesio_pci_ioctl_size data_size,
                                  uint32_t* data);
```

### DESCRIPTION
Read from a device specified by the parameters passed in. This procedure is functionally equivalent to creating a temporary `accesio_pci_device` and calling the function `accesio_get_device_info`.

### PARAMETER(S)
`int file_descriptor` -  A file descriptor to an opened device.
`uint8_t register_offset` - The register offset to read from.
`enum accesio_pci_ioctl_size data_size` - The size (byte/word/dword) of `data`.
`uint32_t* data` - Though a 32-bit value, only 16 or 8 will be read if that size is specified.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_read_usb_unchecked(int file_descriptor, void* data, uint16_t data_len);
```

### DESCRIPTION
Read from a device specified by the parameters passed in. This procedure is functionally equivalent to creating a temporary `accesio_usb_device` and calling the function `accesio_read_usb`.

### PARAMETER(S)
`int file_descriptor` - A file descriptor to an opened device.
`void* data` - The data to read to.
`uint16_t data_len` - The length of the data to read to.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_read_usb_control(int file_descriptor,
                                    uint16_t request,
                                    uint16_t value,
                                    uint16_t index,
                                    void* data,
                                    uint16_t data_len)
```

### DESCRIPTION
Read from a device specified by the parameters passed in. This procedure is functionally equivalent to creating a temporary `accesio_usb_device` and calling the function `accesio_read_usb`.

### PARAMETER(S)
`int file_descriptor` - A file descriptor to an opened device.
`uint16_t request` - The vendor specific request value to send.
`uint16_t value` - The vendor specific value to send.
`uint16_t index` - The vendor specific index to send.
`void* data` - The data to read to.
`uint16_t data_len` - The length of the data to read to.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_write8(accesio_pci_device* device, uint8_t register_offset, uint8_t data);
```

### DESCRIPTION Writes a byte of data to the device.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.
`uint8_t register_offset` - The register offset to read from
`uint8_t data` - The 8-bit data that will sent.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_write16(accesio_pci_device* device, uint8_t register_offset, uint16_t data);
```

### DESCRIPTION Writes a word of data to the device.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.
`uint8_t register_offset` - The register offset to read from
`uint16_t data` - The 16-bit data that will sent.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_write32(accesio_pci_device* device, uint8_t register_offset, uint32_t data);
```

### DESCRIPTION Writes a dword of data to the device.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.
`uint8_t register_offset` - The register offset to read from
`uint32_t data` - The 32-bit data that will sent.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_write_byte(accesio_pci_device* device, uint8_t register_offset, uint8_t data);
```

### DESCRIPTION
A synonym for `accesio_write8`.


### NAME
```c
static int accesio_write_word(accesio_pci_device* device, uint8_t register_offset, uint16_t data);
```

### DESCRIPTION
A synonym for `accesio_write16`.


### NAME
```c
static int accesio_write_dword(accesio_pci_device* device, uint8_t register_offset, uint32_t data);
```

### DESCRIPTION
A synonym for `accesio_write32`.


### NAME
```c
static int accesio_write(accesio_pci_device* device);
```
### DESCRIPTION
Writes to the device specified in the structure. This function assumes you are familiar with the inner structure of `accesio_pci_device` and have set all of the values appropriately.

### PARAMETER(S)
`accesio_pci_device* device` - A reference to the device opened.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_write_usb(accesio_usb_device* device);
```

### DESCRIPTION
Writes to the device specified in the structure. This function assumes you are familiar with the inner structure of `accesio_usb_device` and have set all of the values appropriately.

### PARAMETER(S)
`accesio_usb_device* device` -   A reference to the device opened.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_write_unchecked(int file_descriptor,
                                   uint8_t register_offset,
                                   enum accesio_pci_ioctl_size data_size, uint32_t data);
```

### DESCRIPTION
Writes from a device specified by the parameters passed in. This procedure is functionally equivalent to creating a temporary `accesio_pci_device` setting the appropriate structure values then calling `accesio_io_write`.

### PARAMETER(S)
`int file_descriptor` - A file descriptor to an opened device.
`uint8_t register_offset` - The register offset to write to.
`enum accesio_pci_ioctl_size data_size` - The size (byte/word/dword) of `data`.
`uint32_T data` - Though a 32-bit value, only 16 or 8 will be written if that size is specified.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.

### NAME
```c
static int accesio_write_usb_unchecked(int file_descriptor, void* data, uint16_t data_len);
```

### DESCRIPTION
Writes to the device specified by the parameters passed in. This procedure is functionally equivalent to creating a temporary `accesio_usb_device` and calling the function `accesio_write_usb`.

### PARAMETER(S)
`int file_descriptor` - A file descriptor to an opened device.
`void* data` - The data to write.
`uint16_t data_len` - The length of the data to write.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.


### NAME
```c
static int accesio_write_usb_control(int file_descriptor,
                                     uint16_t request,
                                     uint16_t value,
                                     uint16_t index,
                                     void* data,
                                     uint16_t data_len)
```

### DESCRIPTION
Writes to a device specified by the parameters passed in. This procedure is functionally equivalent to creating a temporary `accesio_usb_device` and calling the function `accesio_write_usb`.

### PARAMETER(S)
`int file_descriptor` - A file descriptor to an opened device.
`uint16_t request` - The vendor specific request value to send.
`uint16_t value` - The vendor specific value to send.
`uint16_t index` - The vendor specific index to send.
`void* data` - The data to read to.
`uint16_t data_len` - The length of the data to read to.

### RETURN VALUE
On success, ACCESIO_SUCCESS is returned, on failure, the error code is returned.
