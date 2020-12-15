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
#ifndef ACCESIO_LINUX_TYPES_H
#define ACCESIO_LINUX_TYPES_H

// don't include directly, this is included in module.h

#if defined(ACCESIO_DRIVER_BUILD)

// internal driver structures

typedef struct accesio_pci_region {
    void* mapped_address;
    uint32_t flags;
    uint32_t start;
    uint32_t end;
    uint32_t length;
    enum accesio_device_address address_type;
} accesio_pci_region;

typedef struct accesio_pci_device_info {
    uint32_t device_index;
    uint32_t product_id;
    atomic_t open_count; // is the device is opened
    bool is_pcie; // is the card on a pcie bus
    bool irq_capable; // is the card even able to generate irqs?
    bool waiting_for_irq; // boolean for if the user has requested an IRQ
    bool irq_cancelled; // boolean for if the user has cancelled the wait
    accesio_pci_region plx_region;
    accesio_pci_region regions[ACCESIO_MAX_REGIONS];
    wait_queue_head_t wait_queue;
    spinlock_t irq_lock;
    int irq;
    struct cdev cdev;
    struct pci_dev* pci_device;
    struct device* dev;
    unsigned int num_channels;
    const struct pci_device_id* pci_id;
} accesio_pci_device_info;

#endif // ACCESIO_DRIVER_BUILD

#endif // ACCESIO_LINUX_TYPES_H