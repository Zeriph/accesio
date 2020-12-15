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
#ifndef ACCESIO_API_TYPES_H
#define ACCESIO_API_TYPES_H

#include "../common/declarations.h"
#include "../common/ioctl.h"
#include "../common/pcidev.h"
#include "../common/usbdev.h"

/**
 * @brief Defines a basic structure that can be used to communicate
 *        with a device registered by the PCI driver. Most values
 *        within this structure need not be touched by user code,
 *        as the rest of the API provides methods to manipulate the
 *        underlying values; however, if you have read the other
 *        areas of this code and are aware of the implications, user
 *        code can easily modify the underlying values.
 */
typedef struct accesio_pci_device {
    /**
     * @brief The device information retrieved when opening a PCI device.
     */
    accesio_pci_info device_info;
    /**
     * @brief The underlying data structure utilized when communicating
     *        via ioctl functions. This structure can be manipulated by
     *        user code and affect the output of driver functions.
     */
    accesio_pci_ioctl_packet io_data;
    /**
     * @brief The underlying file handle used by read/write operations.
     *        This value should not be touched by user code.
     */
    int file_descriptor;
} accesio_pci_device;

/**
 * @brief Defines a basic structure that can be used to communicate
 *        with a device registered by the USB driver. Most values
 *        within this structure need not be touched by user code,
 *        as the rest of the API provides methods to manipulate the
 *        underlying values; however, if you have read the other
 *        areas of this code and are aware of the implications, user
 *        code can easily modify the underlying values.
 */
typedef struct accesio_usb_device {
    /**
     * @brief The device information retrieved when opening a USB device.
     */
    accesio_usb_info device_info;
    /**
     * @brief The underlying data structure utilized when communicating
     *        via ioctl functions. This structure can be manipulated by
     *        user code and affect the output of driver functions.
     */
    accesio_usb_ioctl_packet io_data;
    /**
     * @brief The underlying file handle used by read/write operations.
     *        This value should not be touched by user code.
     */
    int file_descriptor;
} accesio_usb_device;

#endif // ACCESIO_API_TYPES_H
