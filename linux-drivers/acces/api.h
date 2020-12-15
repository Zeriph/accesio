/*
 * Copyright (c), ACCES I/O Products, Inc.
 * All rights reserved.
 * 
 * Contributor(s):
 * Zach Perez, zach.perez@accesio.com
 * 
 * PERMISSION TO USE, COPY, MODIFY, AND/OR DISTRIBUTE THIS SOFTWARE FOR ANY
 * PURPOSE WITH OR WITHOUT FEE IS HEREBY GRANTED, PROVIDED THAT THE ABOVE
 * COPYRIGHT NOTICE AND THIS PERMISSION NOTICE APPEAR IN ALL COPIES.
 * 
 * THIS SOFTWARE IS PROVIDED BY ACCES I/O AND CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL ACCES I/O AND CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef ACCESIO_API_H
#define ACCESIO_API_H

#include "api/types.h"

/**
 * @brief           Retrieves the device information and stores it in
 *                  the `device` parameter passed in.
 * 
 * @param   device  A reference to an `accesio_pci_device` type where information
 *                  about the opened device is stored.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on failure the error
 *                  code is returned.
 */
static int accesio_get_device_info(accesio_pci_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_GET_PCI_INFO, &(device->device_info)) == -1) {
        return -errno;
    }
    device->io_data.bar = device->device_info.bar;
    device->io_data.device_index = device->device_info.device_index;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Retrieves the device information and stores it in
 *                  the `device` parameter passed in.
 * 
 * @param   device  A reference to an `accesio_usb_device` type where information
 *                  about the opened device is stored.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on failure the error
 *                  code is returned.
 */
static int accesio_get_usb_device_info(accesio_usb_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_GET_USB_INFO, &(device->device_info)) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Opens a device handle to the path specified. If the device
 *                  is opened successfully, the device information will be stored
 *                  in the `device` parameter, otherwise it will be zero'd out.
 * 
 * @param   path    The path to the device to open for communication.
 * @param   device  A reference to an `accesio_pci_device` type where information
 *                  about the opened device is stored.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on failure the error
 *                  code is returned.
 */
static int accesio_open_device(const char* path, accesio_pci_device* device)
{
    if (path == NULL || device == NULL) { return -EINVAL; }
    device->file_descriptor = open(path, O_RDWR);
    if (device->file_descriptor > 0) {
        if (ioctl(device->file_descriptor, ACCESIO_IOCTL_GET_PCI_INFO, &(device->device_info)) == -1) { 
            return -errno;
        }
        device->io_data.bar = device->device_info.bar;
        device->io_data.device_index = device->device_info.device_index;
        return ACCESIO_SUCCESS;
    }
    memset(device, 0, sizeof(accesio_pci_device));
    return -ENODEV;
}

/**
 * @brief           Opens a device handle to the path specified. If the device
 *                  is opened successfully, the device information will be stored
 *                  in the `device` parameter, otherwise it will be zero'd out.
 * 
 * @param   path    The path to the device to open for communication.
 * @param   device  A reference to an `accesio_usb_device` type where information
 *                  about the opened device is stored.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on failure the error
 *                  code is returned.
 */
static int accesio_open_usb_device(const char* path, accesio_usb_device* device)
{
    if (path == NULL || device == NULL) { return -EINVAL; }
    device->file_descriptor = open(path, O_RDWR);
    if (device->file_descriptor > 0) {
        if (ioctl(device->file_descriptor, ACCESIO_IOCTL_GET_USB_INFO, &(device->device_info)) == -1) { 
            return -errno;
        }
        return ACCESIO_SUCCESS;
    }
    memset(device, 0, sizeof(accesio_usb_device));
    return -ENODEV;
}

/**
 * @brief           Opens a device handle to the path specified. If the device
 *                  is opened successfully, the device information will be stored
 *                  in the parameters passed in, otherwise they will be zero'd out.
 * 
 * @param   path                The path to the device to open for communication.
 * @param   file_descriptor     A reference where the opened file handle is stored.
 * @param   device_index        A reference where the device index is stored.
 * @param   product_id          A reference where the product ID of the device is stored.
 * @param   bar                 A reference where the main BAR of the device is stored.
 * @param   base_start          A reference where the main region start is stored.
 * @param   base_end            A reference where the main region end is stored.
 * @param   base_length         A reference where the main region length is stored.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on failure the error
 *                  code is returned.
 */
static int accesio_open_path(const char* path,
                             int* file_descriptor,
                             uint32_t* device_index,
                             uint32_t* product_id,
                             uint8_t* bar,
                             uint32_t* base_start,
                             uint32_t* base_end,
                             uint32_t* base_length)
{
    if (path == NULL || file_descriptor == NULL || bar == NULL || device_index == NULL ||
        product_id == NULL || base_start == NULL || base_end == NULL || base_length == NULL)
    { return -EINVAL; }
    *file_descriptor = open(path, O_RDWR);
    if (*file_descriptor > 0) {
        accesio_pci_info device_info;
        if (ioctl(*file_descriptor, ACCESIO_IOCTL_GET_PCI_INFO, &device_info) == -1) {
            return -errno;
        }
        *device_index = device_info.device_index;
        *product_id = device_info.product_id;
        *bar = device_info.bar;
        *base_start = device_info.base_start;
        *base_end = device_info.base_end;
        *base_length = device_info.base_length;
        return ACCESIO_SUCCESS;
    }
    *file_descriptor = 0;
    *device_index = 0;
    *product_id = 0;
    *bar = 0;
    *base_start = 0;
    *base_end = 0;
    *base_length = 0;
    return -ENODEV;
}

/**
 * @brief           Opens a device handle to the path specified. If the device
 *                  is opened successfully, the device information will be stored
 *                  in the parameters passed in, otherwise they will be zero'd out.
 * 
 * @param   path                The path to the device to open for communication.
 * @param   file_descriptor     A reference where the opened file handle is stored.
 * @param   device_index        A reference where the device index is stored.
 * @param   product_id          A reference where the product ID of the device is stored.
 * @param   in_bulk_addr        A reference where the bulk endpoint in-address of the device is stored.
 * @param   out_bulk_addr       A reference where the bulk endpoint out-address of the device is stored.
 * @param   in_ctrl_addr        A reference where the control endpoint in-address of the device is stored.
 * @param   out_ctrl_addr       A reference where the control endpoint out-address of the device is stored.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on failure the error
 *                  code is returned.
 */
static int accesio_open_usb_path(const char* path,
                                 int* file_descriptor,
                                 uint32_t* device_index,
                                 uint32_t* product_id,
                                 uint16_t* in_bulk_addr,
                                 uint16_t* out_bulk_addr,
                                 uint16_t* in_ctrl_addr,
                                 uint16_t* out_ctrl_addr)
{
    if (path == NULL || file_descriptor == NULL || device_index == NULL || product_id == NULL ||
        in_bulk_addr == NULL || out_bulk_addr == NULL || in_ctrl_addr == NULL || out_ctrl_addr == NULL)
    { return -EINVAL; }
    *file_descriptor = open(path, O_RDWR);
    if (*file_descriptor > 0) {
        accesio_usb_info device_info;
        if (ioctl(*file_descriptor, ACCESIO_IOCTL_GET_USB_INFO, &device_info) == -1) {
            return -errno;
        }
        *device_index = device_info.device_index;
        *product_id = device_info.product_id;
        *in_bulk_addr = device_info.endpoints[ACCESIO_USB_BULK_EP].in_address;
        *out_bulk_addr = device_info.endpoints[ACCESIO_USB_BULK_EP].out_address;;
        *in_ctrl_addr = device_info.endpoints[ACCESIO_USB_CTRL_EP].in_address;;
        *out_ctrl_addr = device_info.endpoints[ACCESIO_USB_CTRL_EP].out_address;;
        return ACCESIO_SUCCESS;
    }
    *file_descriptor = 0;
    *device_index = 0;
    *product_id = 0;
    *in_bulk_addr = 0;
    *out_bulk_addr = 0;
    *in_ctrl_addr = 0;
    *out_ctrl_addr = 0;
    return -ENODEV;
}

/**
 * @brief           Closes a system character device that has been opened
 *                  with `accesio_open_device`.
 * 
 * @param   device  A reference to the device opened.
 * 
 * @return  int     On success, the device structure is zero'd out and
 *                  ACCESIO_SUCCESS is returned, on failure the error
 *                  code is returned.
 */
static int accesio_close_device(accesio_pci_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (close(device->file_descriptor) != 0) {
        return -errno;
    }
    memset(device, 0, sizeof(accesio_pci_device));
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Closes a system character device that has been opened
 *                  with `accesio_open_usb_device`.
 * 
 * @param   device  A reference to the device opened.
 * 
 * @return  int     On success, the device structure is zero'd out and
 *                  ACCESIO_SUCCESS is returned, on failure the error
 *                  code is returned.
 */
static int accesio_close_usb_device(accesio_usb_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (close(device->file_descriptor) != 0) {
        return -errno;
    }
    memset(device, 0, sizeof(accesio_usb_device));
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Closes the handle of an opened device.
 * 
 * @param   file_descriptor     The file descriptor to close
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_close_path(int file_descriptor)
{
    if (file_descriptor == 0) { return -EINVAL; }
    if (close(file_descriptor) != 0) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Cancels an interrupt wait request on the specified device.
 * 
 * @param   device  A reference to the device opened.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_cancel_wait_irq(accesio_pci_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_CANCEL_WAIT) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Waits for an interrupt request on the device.
 * 
 * @param   device  A reference to the device opened.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_wait_for_irq(accesio_pci_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
	if (ioctl(device->file_descriptor, ACCESIO_IOCTL_WAIT) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Sets the register offset to read/write to of the device.
 * 
 * @param   device              A reference to the device opened.
 * @param   register_offset     The register offset to assign to the device
 *                              to read from and write to.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_set_offset(accesio_pci_device* device, uint8_t register_offset)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    device->io_data.offset = register_offset;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Sets the device to send byte size data.
 * 
 * @param   device  A reference to the device opened.
 * @param   data    The 8-bit data to set.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_set_byte(accesio_pci_device* device, uint8_t data)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    device->io_data.size = ACCESIO_BYTE;
    device->io_data.data = data;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Sets the device to send word size data.
 * 
 * @param   device  A reference to the device opened.
 * @param   data    The 16-bit data to set.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_set_word(accesio_pci_device* device, uint16_t data)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    device->io_data.size = ACCESIO_WORD;
    device->io_data.data = data;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Sets the device to send double word (dword) size data.
 * 
 * @param   device  A reference to the device opened.
 * @param   data    The 32-bit data to set.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_set_dword(accesio_pci_device* device, uint32_t data)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    device->io_data.size = ACCESIO_DWORD;
    device->io_data.data = data;
    return ACCESIO_SUCCESS;
}

/*** READ FUNCTIONS ***/

/**
 * @brief           Reads a byte of data from the device and stores the
 *                  the value in the `data` referenced passed in.
 * 
 * @param   device              A reference to the device opened.
 * @param   register_offset     The register offset to read from
 * @param   data                A reference to the 8-bit data that will
 *                              be set on a successful device read. 
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_read8(accesio_pci_device* device, uint8_t register_offset, uint8_t* data)
{
    if (device == NULL || device->file_descriptor == 0 || data == NULL) { return -EINVAL; }
    device->io_data.offset = register_offset;
    device->io_data.size = ACCESIO_BYTE;
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_PCI_READ, &(device->io_data)) == -1) {
        return -errno;
    }
    *data = (uint8_t)device->io_data.data;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Reads a word of data from the device and stores the
 *                  the value in the `data` referenced passed in.
 * 
 * @param   device              A reference to the device opened.
 * @param   register_offset     The register offset to read from
 * @param   data                A reference to the 16-bit data that will
 *                              be set on a successful device read. 
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_read16(accesio_pci_device* device, uint8_t register_offset, uint16_t* data)
{
    if (device == NULL || device->file_descriptor == 0 || data == NULL) { return -EINVAL; }
    device->io_data.offset = register_offset;
    device->io_data.size = ACCESIO_WORD;
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_PCI_READ, &(device->io_data)) == -1) {
        return -errno;
    }
    *data = (uint16_t)device->io_data.data;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Reads a dword of data from the device and stores the
 *                  the value in the `data` referenced passed in.
 * 
 * @param   device              A reference to the device opened.
 * @param   register_offset     The register offset to read from
 * @param   data                A reference to the 32-bit data that will
 *                              be set on a successful device read. 
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_read32(accesio_pci_device* device, uint8_t register_offset, uint32_t* data)
{
    if (device == NULL || device->file_descriptor == 0 || data == NULL) { return -EINVAL; }
    device->io_data.offset = register_offset;
    device->io_data.size = ACCESIO_DWORD;
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_PCI_READ, &(device->io_data)) == -1) {
        return -errno;
    }
    *data = (uint32_t)device->io_data.data;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           A synonym for `accesio_read8`.
 */
static int accesio_read_byte(accesio_pci_device* device, uint8_t register_offset, uint8_t* data)
{
    return accesio_read8(device, register_offset, &(*data));
}

/**
 * @brief           A synonym for `accesio_read16`.
 */
static int accesio_read_word(accesio_pci_device* device, uint8_t register_offset, uint16_t* data)
{
    return accesio_read16(device, register_offset, &(*data));
}

/**
 * @brief           A synonym for `accesio_read32`.
 */
static int accesio_read_dword(accesio_pci_device* device, uint8_t register_offset, uint32_t* data)
{
    return accesio_read32(device, register_offset, &(*data));
}

/**
 * @brief           Reads from the device specified in the structure. This function assumes
 *                  you are familiar with the inner structure of `accesio_pci_device` and
 *                  have set all of the values appropriately.
 * 
 * @param   device  A reference to the device opened.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_read(accesio_pci_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_PCI_READ, &(device->io_data)) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Reads from the device specified in the structure. This function assumes
 *                  you are familiar with the inner structure of `accesio_usb_device` and
 *                  have set all of the values appropriately.
 * 
 * @param   device  A reference to the device opened.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_read_usb(accesio_usb_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_USB_READ, &(device->io_data)) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Read from a device specified by the parameters passed in.
 *                  This procedure is functionally equivalent to creating
 *                  a temporary `accesio_pci_device` and calling the function
 *                  `accesio_get_device_info`.
 * 
 * @param   file_descriptor     A file descriptor to an opened device.
 * @param   register_offset     The register offset to read from.
 * @param   data_size           The size (byte/word/dword) of `data`.
 * @param   data                Though a 32-bit value, only 16 or 8
 *                              will be read if that size is specified.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_read_unchecked(int file_descriptor,
                                  uint8_t register_offset,
                                  enum accesio_pci_ioctl_size data_size,
                                  uint32_t* data)
{
    if (file_descriptor == 0 || data == NULL) { return -EINVAL; }
    accesio_pci_device device;
    device.file_descriptor = file_descriptor;
    device.io_data.offset = register_offset;
    device.io_data.size = data_size;
    if (ioctl(file_descriptor, ACCESIO_IOCTL_PCI_READ, &device.io_data) == -1) {
        return -errno;
    }
    *data = (uint32_t)device.io_data.data;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Read from a device specified by the parameters passed in.
 *                  This procedure is functionally equivalent to creating
 *                  a temporary `accesio_usb_device` and calling the function
 *                  `accesio_read_usb`.
 * 
 * @param   file_descriptor     A file descriptor to an opened device.
 * @param   data                The data to read to.
 * @param   data_len            The length of the data to read to.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_read_usb_unchecked(int file_descriptor, void* data, uint16_t data_len)
{
    if (file_descriptor == 0 || data == NULL || data_len == 0) { return -EINVAL; }
    accesio_usb_device device;
    device.file_descriptor = file_descriptor;
    device.io_data.msg_type = ACCESIO_USB_IOCTL_BULK_MSG;
    device.io_data.data = data;
    device.io_data.data_len = data_len;
    if (ioctl(file_descriptor, ACCESIO_IOCTL_USB_READ, &device.io_data) == -1) {
        return -errno;
    }
    data = device.io_data.data;
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Read from a device specified by the parameters passed in.
 *                  This procedure is functionally equivalent to creating
 *                  a temporary `accesio_usb_device` and calling the function
 *                  `accesio_read_usb`.
 * 
 * @param   file_descriptor     A file descriptor to an opened device.
 * @param   request             The vendor specific request value to send.
 * @param   value               The vendor specific value to send.
 * @param   index               The vendor specific index to send.
 * @param   data                The data to read to.
 * @param   data_len            The length of the data to read to.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_read_usb_control(int file_descriptor, uint16_t request, uint16_t value, uint16_t index, void* data, uint16_t data_len)
{
    if (file_descriptor == 0 || data == NULL || data_len == 0) { return -EINVAL; }
    accesio_usb_device device;
    device.file_descriptor = file_descriptor;
    device.io_data.msg_type = ACCESIO_USB_IOCTL_CTRL_MSG;
    device.io_data.data = data;
    device.io_data.data_len = data_len;
    device.io_data.request = request;
    device.io_data.value = value;
    device.io_data.index = index;
    if (ioctl(file_descriptor, ACCESIO_IOCTL_USB_READ, &device.io_data) == -1) {
        return -errno;
    }
    data = device.io_data.data;
    return ACCESIO_SUCCESS;
}

/*** WRITE FUNCTIONS ***/

/**
 * @brief           Writes a byte of data to the device.
 * 
 * @param   device              A reference to the device opened.
 * @param   register_offset     The register offset to read from
 * @param   data                The 8-bit data that will sent.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_write8(accesio_pci_device* device, uint8_t register_offset, uint8_t data)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    device->io_data.offset = register_offset;
    device->io_data.size = ACCESIO_BYTE;
    device->io_data.data = data;
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_PCI_WRITE, &(device->io_data)) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Writes a word of data to the device.
 * 
 * @param   device              A reference to the device opened.
 * @param   register_offset     The register offset to read from
 * @param   data                The 16-bit data that will sent.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_write16(accesio_pci_device* device, uint8_t register_offset, uint16_t data)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    device->io_data.offset = register_offset;
    device->io_data.size = ACCESIO_WORD;
    device->io_data.data = data;
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_PCI_WRITE, &(device->io_data)) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Writes a dword of data to the device.
 * 
 * @param   device              A reference to the device opened.
 * @param   register_offset     The register offset to read from
 * @param   data                The 32-bit data that will sent.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_write32(accesio_pci_device* device, uint8_t register_offset, uint32_t data)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    device->io_data.offset = register_offset;
    device->io_data.size = ACCESIO_DWORD;
    device->io_data.data = data;
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_PCI_WRITE, &(device->io_data)) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           A synonym for `accesio_write8`.
 */
static int accesio_write_byte(accesio_pci_device* device, uint8_t register_offset, uint8_t data)
{
    return accesio_write8(device, register_offset, data);
}

/**
 * @brief           A synonym for `accesio_write16`.
 */
static int accesio_write_word(accesio_pci_device* device, uint8_t register_offset, uint16_t data)
{
    return accesio_write16(device, register_offset, data);
}

/**
 * @brief           A synonym for `accesio_write32`.
 */
static int accesio_write_dword(accesio_pci_device* device, uint8_t register_offset, uint32_t data)
{
    return accesio_write32(device, register_offset, data);
}

/**
 * @brief           Writes to the device specified in the structure. This function assumes
 *                  you are familiar with the inner structure of `accesio_pci_device` and
 *                  have set all of the values appropriately.
 * 
 * @param   device  A reference to the device opened.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_write(accesio_pci_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_PCI_WRITE, &(device->io_data)) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Writes to the device specified in the structure. This function assumes
 *                  you are familiar with the inner structure of `accesio_usb_device` and
 *                  have set all of the values appropriately.
 * 
 * @param   device  A reference to the device opened.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_write_usb(accesio_usb_device* device)
{
    if (device == NULL || device->file_descriptor == 0) { return -EINVAL; }
    if (ioctl(device->file_descriptor, ACCESIO_IOCTL_USB_WRITE, &(device->io_data)) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Writes from a device specified by the parameters passed in.
 *                  This procedure is functionally equivalent to creating
 *                  a temporary `accesio_pci_device` setting the appropriate
 *                  structure values then calling `accesio_io_write`.
 * 
 * @param   file_descriptor     A file descriptor to an opened device.
 * @param   register_offset     The register offset to write to.
 * @param   data_size           The size (byte/word/dword) of `data`.
 * @param   data                Though a 32-bit value, only 16 or 8
 *                              will be written if that size is specified.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_write_unchecked(int file_descriptor, uint8_t register_offset, enum accesio_pci_ioctl_size data_size, uint32_t data)
{
    if (file_descriptor == 0) { return -EINVAL; }
    accesio_pci_device device;
    device.file_descriptor = file_descriptor;
    device.io_data.offset = register_offset;
    device.io_data.size = data_size;
    device.io_data.data = data;
    if (ioctl(file_descriptor, ACCESIO_IOCTL_PCI_WRITE, &device.io_data) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Writes from a device specified by the parameters passed in.
 *                  This procedure is functionally equivalent to creating
 *                  a temporary `accesio_usb_device` setting the appropriate
 *                  structure values then calling `accesio_write_usb`.
 * 
 * @param   file_descriptor     A file descriptor to an opened device.
 * @param   data                The data to write.
 * @param   data_len            The length of the data to write.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_write_usb_unchecked(int file_descriptor, void* data, uint16_t data_len)
{
    if (file_descriptor == 0) { return -EINVAL; }
    accesio_usb_device device;
    device.file_descriptor = file_descriptor;
    device.io_data.msg_type = ACCESIO_USB_IOCTL_BULK_MSG;
    device.io_data.data = data;
    device.io_data.data_len = data_len;
    if (ioctl(file_descriptor, ACCESIO_IOCTL_USB_WRITE, &device.io_data) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Write to the a device specified by the parameters passed in.
 *                  This procedure is functionally equivalent to creating
 *                  a temporary `accesio_usb_device` and calling the function
 *                  `accesio_write_usb`.
 * 
 * @param   file_descriptor     A file descriptor to an opened device.
 * @param   request             The vendor specific request value to send.
 * @param   value               The vendor specific value to send.
 * @param   index               The vendor specific index to send.
 * @param   data                The data to write.
 * @param   data_len            The length of the data to write.
 * 
 * @return  int     On success, ACCESIO_SUCCESS is returned, on
 *                  failure, the error code is returned.
 */
static int accesio_write_usb_control(int file_descriptor, uint16_t request, uint16_t value, uint16_t index, void* data, uint16_t data_len)
{
    if (file_descriptor == 0 || data == NULL || data_len == 0) { return -EINVAL; }
    accesio_usb_device device;
    device.file_descriptor = file_descriptor;
    device.io_data.msg_type = ACCESIO_USB_IOCTL_CTRL_MSG;
    device.io_data.data = data;
    device.io_data.data_len = data_len;
    device.io_data.request = request;
    device.io_data.value = value;
    device.io_data.index = index;
    if (ioctl(file_descriptor, ACCESIO_IOCTL_USB_WRITE, &device.io_data) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

#endif // ACCESIO_API_H
