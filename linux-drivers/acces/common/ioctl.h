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
#ifndef ACCESIO_IOCTL_H
#define ACCESIO_IOCTL_H
#include "linux.h"

#define ACCESIO_MAGIC_NUM 0xE0

#define ACCESIO_IOCTL_GET_TOTAL_DEVICE_COUNT        _IO(ACCESIO_MAGIC_NUM,  1)
#define ACCESIO_IOCTL_GET_DEVICE_INFO               _IOR(ACCESIO_MAGIC_NUM, 2, void*) // need to deprecate
#define ACCESIO_IOCTL_GET_PCI_INFO                  _IOR(ACCESIO_MAGIC_NUM, 15, accesio_pci_info*)
#define ACCESIO_IOCTL_GET_USB_INFO                  _IOR(ACCESIO_MAGIC_NUM, 16, accesio_usb_info*)

#define ACCESIO_IOCTL_GET_DEVICE_IRQ_CAPABLE        _IOR(ACCESIO_MAGIC_NUM, 8, bool)
#define ACCESIO_IOCTL_GET_DEVICE_IS_USB             _IOR(ACCESIO_MAGIC_NUM, 14, bool)
#define ACCESIO_IOCTL_GET_DEVICE_IS_PCI             _IOR(ACCESIO_MAGIC_NUM, 13, bool)
#define ACCESIO_IOCTL_GET_DEVICE_IS_PCIE            _IOR(ACCESIO_MAGIC_NUM, 7, bool)

#define ACCESIO_IOCTL_WRITE                         _IOW(ACCESIO_MAGIC_NUM, 3, void*)
#define ACCESIO_IOCTL_READ                          _IOR(ACCESIO_MAGIC_NUM, 4, void*)

// PCI-only functions (USB will return -ENOSYS)
#define ACCESIO_IOCTL_WAIT                          _IO(ACCESIO_MAGIC_NUM, 5)
#define ACCESIO_IOCTL_CANCEL_WAIT                   _IO(ACCESIO_MAGIC_NUM, 6)
#define ACCESIO_IOCTL_GET_DEVICE_WAITING_FOR_IRQ    _IOR(ACCESIO_MAGIC_NUM, 9, bool)
#define ACCESIO_IOCTL_GET_DEVICE_IRQ_CANCELLED      _IOR(ACCESIO_MAGIC_NUM, 10, bool)
#define ACCESIO_IOCTL_GET_DEVICE_PLX_START          _IOR(ACCESIO_MAGIC_NUM, 11, uint32_t)
#define ACCESIO_IOCTL_GET_DEVICE_PLX_END            _IOR(ACCESIO_MAGIC_NUM, 12, uint32_t)
#define ACCESIO_IOCTL_PCI_WRITE                     _IOW(ACCESIO_MAGIC_NUM, 17, accesio_pci_ioctl_packet*)
#define ACCESIO_IOCTL_PCI_READ                      _IOR(ACCESIO_MAGIC_NUM, 18, accesio_pci_ioctl_packet*)

// USB-only functions (PCI will return -ENOSYS)
#define ACCESIO_IOCTL_USB_WRITE                     _IOW(ACCESIO_MAGIC_NUM, 19, accesio_usb_ioctl_packet*)
#define ACCESIO_IOCTL_USB_READ                      _IOR(ACCESIO_MAGIC_NUM, 20, accesio_usb_ioctl_packet*)
#define ACCESIO_IOCTL_GET_USB_IS_READING            _IOR(ACCESIO_MAGIC_NUM, 21, bool)
#define ACCESIO_IOCTL_GET_USB_IS_WRITING            _IOR(ACCESIO_MAGIC_NUM, 22, bool)
#define ACCESIO_IOCTL_GET_USB_IS_IO                 _IOR(ACCESIO_MAGIC_NUM, 23, bool)

/**
 * @brief Defines a size type that is used when reading/writing
 *        through any ioctl functions.
 */
enum accesio_pci_ioctl_size {
    /**
     * @brief The data read/written will be 8-bits.
     */
    ACCESIO_BYTE  = sizeof(uint8_t),
    /**
     * @brief The data read/written will be 16-bits.
     */
    ACCESIO_WORD  = sizeof(uint16_t),
    /**
     * @brief The data read/written will be 32-bits.
     */
    ACCESIO_DWORD = sizeof(uint32_t)
};

enum accesio_usb_ioctl_message_type {
    ACCESIO_USB_IOCTL_BULK_MSG,
    ACCESIO_USB_IOCTL_CTRL_MSG
};

/**
 * Defines a basic packet of information utilized in communication
 * through ioctl.
 */
typedef struct accesio_pci_ioctl_packet {
    /**
     * The device index given to the device by the driver.
     * This is not something the user should modify.
     */
    uint32_t device_index;
    /**
     * The data to send to the device, or the data returned
     * from the device on a read operation.
     */
    uint32_t data;
    /**
     * The base address register of the device to read/write to.
     * This value is set by the driver, but can be modified by
     * user code before a read or write operation.
     * 
     * Valid values are 0 to ACCESIO_MAX_REGIONS-1
     */
    uint8_t bar;
    /**
     * The register offset to read from or write to. This value
     * must be set by the user before a read or write operation.
     * 
     * Valid values are device dependant and you will need to
     * refer to the hardware documentation, as well, you can
     * view the output of a kernel dmesg to grep for the valid
     * ranges reported by the driver.
     */
    uint8_t offset;
    /**
     * This determines the size of `data` read from or written to
     * the device for ioctl functions. Though the `data` member is
     * a 32-bit field, if `size` is ACCESIO_BYTE, `data` is casted
     * to an 8-bit field, and if `size` is ACCESIO_WORD, `data` is
     * casted to a 16-bit field.
     */
    enum accesio_pci_ioctl_size size;
} accesio_pci_ioctl_packet;

typedef struct accesio_usb_ioctl_packet {
    void* data;
    uint16_t data_len;
    enum accesio_usb_ioctl_message_type msg_type;
    uint8_t request; // only valid when msg_type == CTRL
    uint16_t value; // only valid when msg_type == CTRL
    uint16_t index; // only valid when msg_type == CTRL
} accesio_usb_ioctl_packet;


#endif // ACCESIO_IOCTL_H
