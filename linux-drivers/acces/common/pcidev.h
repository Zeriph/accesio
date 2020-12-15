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
#ifndef ACCESIO_PCIDEV_H
#define ACCESIO_PCIDEV_H

#include "declarations.h"

#define ACCESIO_DEV_ADDR_INVALID 0
#define ACCESIO_DEV_ADDR_IO 1
#define ACCESIO_DEV_ADDR_MEM 2

/**
 * @brief Describes the PCI device address access type.
 */
enum accesio_device_address {
    /**
     * @brief The device does not have a valid address associated.
     */
    ACCESIO_ADDR_INVALID = 0,
    /**
     * @brief The device is utilizing IO mapped address space.
     */
    ACCESIO_ADDR_IO = 1,
    /**
     * @brief The device is utilizing memory mapped address space.
     */
    ACCESIO_ADDR_MEM = 2
};

/**
 * @brief Describes a device region layout; the length
 *        of an IO region determines the valid range of
 *        offsets that can be read from or written to.
 */
typedef struct accesio_io_region {
    /**
     * @brief The address type of this region.
     */
    enum accesio_device_address address_type;
    /**
     * @brief The ending address of this mapped region.
     */
    uint32_t end;
    /**
     * @brief The length of this mapped region. This
     *        determines the valid range of offsets
     *        that can be read from and written to.
     */
    uint32_t length;
    /**
     * @brief The start address of this mapped region.
     */
    uint32_t start;
} accesio_io_region;

/**
 * @brief Defines a structure containing information about
 *        the device that can be read from user space.
 */
typedef struct accesio_pci_info {
    /**
     * @brief The devices base address register. This is
     *        determined by the driver, but can be modifed
     *        in user code before a device operation.
     */
    uint8_t bar;
    /**
     * @brief This is set by the driver to regions[bar].address_type.
     */
    enum accesio_device_address base_address_type;
    /**
     * @brief This is set by the driver to regions[bar].end.
     */
    uint32_t base_end;
    /**
     * @brief This is set by the driver to regions[bar].length.
     */
    uint32_t base_length;
    /**
     * @brief This is set by the driver to regions[bar].start.
     */
    uint32_t base_start;
    /**
     * @brief This is set by the driver and represents this
     *        devices index within the driver. If this device
     *        was the 3rd device registered by the driver, this
     *        value will be 2 (n-1).
     */
    uint32_t device_index;
    /**
     * @brief This is the product ID of the device as
     *        detected by the kernel/driver.
     */
    uint32_t product_id;
    /**
     * @brief This is an array of the regions mapped for
     *        communication over the bus. The region at
     *        `bar` (e.g. .regions[.bar]) is the main
     *        region that should be utilized to communicate
     *        with the device.
     */
    accesio_io_region regions[ACCESIO_MAX_REGIONS];
} accesio_pci_info;

#endif // ACCESIO_PCIDEV_H
