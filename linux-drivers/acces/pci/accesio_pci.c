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
#define MODULE_NAME "ACCESIO_PCI"
#define MODULE_PREFIX MODULE_NAME": "
#define ACCESIO_CLASS_INIT_FN

#include "../common/driver.h"
#include "../common/ioctl.h"
#include "../common/pcidev.h"
#include "module/ids.h"
#include "module/declarations.h"
#include "module/types.h"
#include "module/driver.h"

static inline const char* accesio_parse_address_type(enum accesio_device_address type)
{
    switch (type) {
        case ACCESIO_ADDR_INVALID: return "INVALID";
        case ACCESIO_ADDR_IO: return "IO";
        case ACCESIO_ADDR_MEM: return "MEM";
        default: break;
    }
    return "UNKNOWN";
}

static void accesio_pci_free_driver(struct pci_dev* pdev)
{
    int count = 0;
    accesio_pci_device_info* ddata = pci_get_drvdata(pdev);
    release_region(ddata->plx_region.start, ddata->plx_region.length);
    for (count = 0; count < ACCESIO_MAX_REGIONS; ++count) {
        if (ddata->regions[count].start == 0) { continue; } // invalid region
        if (ddata->regions[count].flags & IORESOURCE_IO) {
            release_region(ddata->regions[count].start, ddata->regions[count].length);
        } else {
            if (ddata->regions[count].mapped_address != NULL) {
                iounmap(ddata->regions[count].mapped_address);
            }
            release_mem_region(ddata->regions[count].start, ddata->regions[count].length);
        }
    }
    kfree(ddata);
}

static void accesio_pci_device_set_irq_data(accesio_pci_device_info* ddata, uint32_t irq)
{
    switch (ddata->product_id) {
        case ACCESIO_PCIE_DIO_24: case ACCESIO_PCIE_DIO_24D: case ACCESIO_PCIE_DIO_24S:
        case ACCESIO_MPCIE_DIO_24S: case ACCESIO_PCIE_DIO_24DS: case ACCESIO_PCIE_DIO_24DC: case ACCESIO_PCIE_DIO_24DCS:
        case ACCESIO_PCIE_DIO_48: case ACCESIO_PCIE_DIO_48S: case ACCESIO_PCIE_IIRO_8: case ACCESIO_PCIE_IIRO_16:
        case ACCESIO_PCI_DIO_24H: case ACCESIO_PCI_DIO_24D: case ACCESIO_PCI_DIO_24H_C: case ACCESIO_PCI_DIO_24D_C:
        case ACCESIO_PCI_DIO_24S: case ACCESIO_PCI_DIO_48: case ACCESIO_PCI_DIO_48S: case ACCESIO_P104_DIO_48S:
        case ACCESIO_PCI_DIO_72: case ACCESIO_PCI_DIO_96: case ACCESIO_PCI_DIO_96C3: case ACCESIO_PCI_DIO_120:
        case ACCESIO_PCI_AI12_16: case ACCESIO_PCI_AI12_16A: case ACCESIO_PCI_A12_16A: case ACCESIO_LPCI_IIRO_8:
        case ACCESIO_PCI_IIRO_8: case ACCESIO_PCI_IIRO_16: case ACCESIO_PCI_IDI_48: case ACCESIO_PCI_IDIO_16:
        case ACCESIO_LPCI_A16_16A: case ACCESIO_PCI_DA12_16: case ACCESIO_PCI_DA12_8:
            ddata->irq_capable = true;
            ddata->irq = irq;
            break;
        default: break;
    }
}

static void accesio_pci_device_set_regions(struct pci_dev* pdev, uint32_t product_id, accesio_pci_region* region2)
{
    region2->start = pci_resource_start(pdev, 2);
    region2->end = pci_resource_end(pdev, 2);
    region2->flags = pci_resource_flags(pdev, 2);
    region2->length = region2->end - region2->start + 1;
    switch (product_id) {
        case ACCESIO_LPCI_A16_16A: case ACCESIO_PCI_DA12_16: case ACCESIO_PCI_DA12_8:
        case ACCESIO_PCI_DA12_6: case ACCESIO_PCI_DA12_4: case ACCESIO_PCI_DA12_2:
            (region2+1)->start = pci_resource_start(pdev, 3);
            (region2+1)->end = pci_resource_end(pdev, 3);
            (region2+1)->flags = pci_resource_flags(pdev, 3);
            (region2+1)->length = (region2+1)->end - (region2+1)->start + 1;
            break;
    }
}

static bool accesio_pci_device_info_init(struct pci_dev* pdev, accesio_pci_device_info* ddata)
{
    int plx_bar = 0;
    spin_lock_init(&(ddata->irq_lock));
    plx_bar = (pci_resource_flags(pdev, 0) & IORESOURCE_IO) ? 0 : 1;
    ddata->plx_region.start	= pci_resource_start(pdev, plx_bar);
    if (!ddata->plx_region.start) {
        printk(KERN_INFO KBUILD_MODNAME ": invalid bar %d on start\n", plx_bar);
        return false;
    }
    ddata->plx_region.end = pci_resource_end(pdev, plx_bar);
    if (!ddata->plx_region.start) {
        printk(KERN_INFO KBUILD_MODNAME ": invalid bar %d on end", plx_bar);
        return false;   
    }
    ddata->plx_region.length = ddata->plx_region.end - ddata->plx_region.start + 1;
    if (request_region(ddata->plx_region.start, ddata->plx_region.length, DRIVER_NAME) == NULL) {
        printk(KERN_INFO KBUILD_MODNAME ": unable to request region of %d starting at %d for '%s'.\n", ddata->plx_region.length, ddata->plx_region.start, DRIVER_NAME);
        return false;
    }
    // TODO: request and remap the region for plx <- note from old code
    accesio_pci_device_set_regions(pdev, ddata->product_id, &ddata->regions[2]);
    accesio_pci_device_set_irq_data(ddata, pdev->irq);
    // request regions
    for (plx_bar = 0; plx_bar < ACCESIO_MAX_REGIONS; ++plx_bar) {
        if (ddata->regions[plx_bar].start == 0) {
            ddata->regions[plx_bar].address_type = ACCESIO_ADDR_INVALID;
            continue;
        }
        if (ddata->regions[plx_bar].flags & IORESOURCE_IO) {
            if (request_region(ddata->regions[plx_bar].start, ddata->regions[plx_bar].length, DRIVER_NAME) == NULL) {
                printk(KERN_INFO KBUILD_MODNAME ": could not request region for %d.\n", plx_bar);
                while (--plx_bar >= 0) { // release prior regions acquired on failure
                    if (ddata->regions[plx_bar].start != 0) {
                        release_region(ddata->regions[plx_bar].start, ddata->regions[plx_bar].length);
                    }
                }
                return false;
            }
            ddata->regions[plx_bar].address_type = ACCESIO_ADDR_IO;
        } else {
            if (request_mem_region(ddata->regions[plx_bar].start, ddata->regions[plx_bar].length, DRIVER_NAME) == NULL) {
                printk(KERN_INFO KBUILD_MODNAME ": could not request memory region for %d.\n", plx_bar);
                while (--plx_bar >= 0) {
                    if (ddata->regions[plx_bar].start != 0) {
                        release_region(ddata->regions[plx_bar].start, ddata->regions[plx_bar].length);
                    }
                    if (ddata->regions[plx_bar].mapped_address != NULL) {
                        iounmap(ddata->regions[plx_bar].mapped_address);
                    }
                }
                return false;
            }
            ddata->regions[plx_bar].address_type = ACCESIO_ADDR_MEM;
            ddata->regions[plx_bar].mapped_address = ioremap(ddata->regions[plx_bar].start, ddata->regions[plx_bar].length);
        }
    }
    return true;
}

static int accesio_pci_alloc_driver(accesio_pci_device_info** device, struct pci_dev* pdev, const struct pci_device_id* id) 
{
    *device = (accesio_pci_device_info*)kzalloc(sizeof(accesio_pci_device_info), GFP_KERNEL);
    if (!*device) {
        printk(KERN_INFO KBUILD_MODNAME ": could not allocate memory for PCI device.\n");
        return -ENOMEM;
    }
    (*device)->product_id = id->device;
    if (!accesio_pci_device_info_init(pdev, *device)) {
        kfree(*device);
        *device = NULL;
        printk(KERN_INFO KBUILD_MODNAME ": could not initialize PCI device info.\n");
        return -ENODEV;
    }
    (*device)->num_channels = ACCESIO_PCI_CHANNELS;
    (*device)->pci_device = pdev;
    (*device)->pci_id = id;

    (*device)->is_pcie = ((*device)->plx_region.length >= 0x100);
    // TODO: bar 2 

    atomic_set(&((*device)->open_count), 0);
    return ACCESIO_SUCCESS;
}

static bool accesio_pci_interrupt_main(accesio_pci_device_info* device)
{
    return (device->is_pcie ?
            ((inb(device->plx_region.start + ACCESIO_PCI_INB) & ACCESIO_PCI_IRQ) != 0) :
            ((inb(device->plx_region.start + ACCESIO_PCIE_INB) & ACCESIO_PCIE_IRQ) != 0));
}

static void accesio_pci_interrupt_irq_lock(accesio_pci_device_info* device)
{
    /* Check to see if we were actually waiting for an IRQ. If we were
     * then we need to wake the queue associated with this device.
     * Right now it is not possible for any other code sections that access
     * the critical data to interrupt us so we won't disable other IRQs. */
    spin_lock(&(device->irq_lock));
    if (device->waiting_for_irq) {
        device->waiting_for_irq = false;
        spin_unlock(&(device->irq_lock));
        wake_up_interruptible(&(device->wait_queue));
    } else {
        spin_unlock(&(device->irq_lock));
    }
}

static irqreturn_t accesio_pci_interrupt_1(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    outb(0, ddata->regions[2].start + 0x0F);
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static irqreturn_t accesio_pci_interrupt_2(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    // These cards don't have the IRQ simply "Cleared", it must be disabled then re-enabled.
    outb(0, ddata->regions[2].start + 0x1E);
    outb(0, ddata->regions[2].start + 0x1F);
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static irqreturn_t accesio_pci_interrupt_3(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    inb(ddata->regions[2].start + 0xC);
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static irqreturn_t accesio_pci_interrupt_4(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    outb(0, ddata->regions[2].start + 0x9);
    outb(0, ddata->regions[2].start + 0x4);
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static irqreturn_t accesio_pci_interrupt_5(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    //apci_devel("Interrupt for PCIe_IIRO_8");
    outb(0, ddata->regions[2].start + 0x1);
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static irqreturn_t accesio_pci_interrupt_6(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    inb(ddata->regions[2].start + 0x7);
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static irqreturn_t accesio_pci_interrupt_7(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    //uint8_t byte;
    /* Clear the FIFO interrupt enable bits, but leave
    * the counter enabled.  Otherwise the IRQ will not
    * go away and user code will never run as the machine
    * will hang in a never-ending IRQ loop. The userland
    * irq routine must re-enable the interrupts if desired. */
    outb(0x01, ddata->regions[2].start + 0x04);
    inb(ddata->regions[2].start + 0x04);
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static irqreturn_t accesio_pci_interrupt_8(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    outb(0, ddata->regions[2].start + 0x0C);
    outb(0x10, ddata->regions[2].start + 0x0C);
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static irqreturn_t accesio_pci_interrupt_9(int irq, void* dev_id)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)dev_id;
    if (!accesio_pci_interrupt_main(ddata)) { return IRQ_NONE; }
    // see note below
    accesio_pci_interrupt_irq_lock(ddata);
    return IRQ_HANDLED;
}

static int accesio_pci_set_irq_handlers(accesio_pci_device_info* device)
{
    if (device == NULL) { return -ENODEV; }
    if (device->irq_capable) {
        // request IRQ
        int ret = 0;
        switch (device->product_id) {
            case ACCESIO_PCIE_DIO_24: case ACCESIO_PCIE_DIO_24D: case ACCESIO_PCIE_DIO_24S: case ACCESIO_PCIE_DIO_24DS:
            case ACCESIO_PCIE_DIO_24DC: case ACCESIO_PCIE_DIO_24DCS: case ACCESIO_PCIE_DIO_48: case ACCESIO_PCIE_DIO_48S:
            case ACCESIO_PCI_DIO_24H: case ACCESIO_PCI_DIO_24D: case ACCESIO_PCI_DIO_24H_C: case ACCESIO_PCI_DIO_24D_C:
            case ACCESIO_PCI_DIO_24S: case ACCESIO_PCI_DIO_48: case ACCESIO_PCI_DIO_48S:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_1, IRQF_SHARED, DRIVER_NAME, device);
                break;
            case ACCESIO_PCI_DIO_72: case ACCESIO_PCI_DIO_96: case ACCESIO_PCI_DIO_96CT: case ACCESIO_PCI_DIO_96C3: case ACCESIO_PCI_DIO_120:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_2, IRQF_SHARED, DRIVER_NAME, device);
                break;
            case ACCESIO_PCI_DA12_16: case ACCESIO_PCI_DA12_8: case ACCESIO_PCI_DA12_6: case ACCESIO_PCI_DA12_4:
            case ACCESIO_PCI_DA12_2: case ACCESIO_PCI_DA12_16V: case ACCESIO_PCI_DA12_8V:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_3, IRQF_SHARED, DRIVER_NAME, device);
                break;
            case ACCESIO_PCI_WDG_CSM:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_4, IRQF_SHARED, DRIVER_NAME, device);
                break;
            case ACCESIO_PCIE_IIRO_8: case ACCESIO_PCIE_IIRO_16: case ACCESIO_PCI_IIRO_8:
            case ACCESIO_PCI_IIRO_16: case ACCESIO_PCI_IDIO_16: case ACCESIO_LPCI_IIRO_8:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_5, IRQF_SHARED, DRIVER_NAME, device);
                break;
            case ACCESIO_PCI_IDI_48:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_6, IRQF_SHARED, DRIVER_NAME, device);
                break;
            case ACCESIO_PCI_AI12_16: case ACCESIO_PCI_AI12_16A: case ACCESIO_PCI_AIO12_16: case ACCESIO_PCI_A12_16A:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_7, IRQF_SHARED, DRIVER_NAME, device);
                break;
            case ACCESIO_LPCI_A16_16A:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_8, IRQF_SHARED, DRIVER_NAME, device);
                break;
            // unknown at this time 6-FEB-2007
            case ACCESIO_P104_DIO_96: case ACCESIO_P104_DIO_48S:
                ret = request_irq((unsigned int)device->irq, accesio_pci_interrupt_9, IRQF_SHARED, DRIVER_NAME, device);
                break;
        };
        if (ret != 0) {
            printk(KERN_INFO KBUILD_MODNAME ": error requesting IRQ %u.\n", device->irq);
            return -EIO;
        }
        init_waitqueue_head(&(device->wait_queue));
    }
    return ACCESIO_SUCCESS;
}

static void accesio_pci_class_device_unregister(accesio_pci_device_info* ddata)
{
    if (ddata != NULL && ddata->dev != NULL) {
        decrement_device_id(ddata->product_id);
        device_unregister(ddata->dev);
        --accesio_found_devices;
        printk(KERN_INFO KBUILD_MODNAME ": unregistered device %d=%s_%d, total registered=%d\n", ddata->product_id, get_name_from_id(ddata->product_id), ddata->device_index, accesio_found_devices);
    }
}

static uint8_t accesio_get_bar(uint32_t product_id)
{
    // TODO: switch (product_id) { case default: break; }
    return 2;
}

static int accesio_pci_class_device_register(accesio_pci_device_info* ddata)
{
    int tmp = 0;
    int bar = 0;
    if (ddata == NULL) { return -EINVAL; }
    tmp = increment_device_id(ddata->product_id);
    ddata->dev = device_create(accesio_class,
                               &(ddata->pci_device->dev),
                               accesio_first_dev + accesio_found_devices,
                               NULL,
                               DRIVER_DEVICE_FMT,
                               get_name_from_id(ddata->product_id),
                               tmp);
    if (IS_ERR(ddata->dev)) {
        tmp = PTR_ERR(ddata->dev);
        decrement_device_id(ddata->product_id);
        printk(KERN_INFO KBUILD_MODNAME ": error creating the device: %d\n", tmp);
        ddata->dev = NULL;
        return tmp;
    }
    ++accesio_found_devices;
    bar = accesio_get_bar(ddata->product_id);
    printk(KERN_INFO KBUILD_MODNAME ": registered device 0x%04X=%s_%d,bar=%d,index=%d,start=0x%04X,end=0x%04X,len=%d,pcie=%c,irq=%c,addr=%s\n",
           ddata->product_id,
           get_name_from_id(ddata->product_id),
           tmp,
           bar,
           ddata->device_index,
           ddata->regions[bar].start,
           ddata->regions[bar].end,
           ddata->regions[bar].length,
           (ddata->is_pcie ? 't' : 'f'),
           (ddata->irq_capable ? 't' : 'f'),
           accesio_parse_address_type(ddata->regions[bar].address_type));
    return ACCESIO_SUCCESS;
}

static inline int accesio_pci_ioctl_internal_get_device_info(accesio_pci_device_info* ddata, unsigned long arg)
{
    int tmp = 0;
    accesio_pci_info info;
    if (ACCES_AOK(VERIFY_WRITE, arg, sizeof(accesio_pci_info)) == 0) { return -EACCES; }
    info.product_id = ddata->product_id;
    info.bar = accesio_get_bar(info.product_id);
    info.base_address_type = ddata->regions[info.bar].address_type;
    info.base_end = ddata->regions[info.bar].end;
    info.base_length = ddata->regions[info.bar].length;
    info.base_start = ddata->regions[info.bar].start;
    info.device_index = ddata->device_index;
    for (tmp = 0; tmp < ACCESIO_MAX_REGIONS; ++tmp) {
        info.regions[tmp].address_type = ddata->regions[tmp].address_type;
        info.regions[tmp].end = ddata->regions[tmp].end;
        info.regions[tmp].length = ddata->regions[tmp].length;
        info.regions[tmp].start = ddata->regions[tmp].start;
    }
    if (copy_to_user((accesio_pci_info*)arg, &info, sizeof(accesio_pci_info)) != 0) { return -EIO; };
    return ACCESIO_SUCCESS;
}

static inline int accesio_pci_ioctl_internal_write(accesio_pci_device_info* ddata, unsigned long arg)
{
    int tmp = 0;
    accesio_pci_ioctl_packet iodata;
    if (ACCES_AOK(VERIFY_READ, arg, sizeof(accesio_pci_ioctl_packet)) == 0) { return -EACCES; }
    tmp = copy_from_user(&iodata, (accesio_pci_ioctl_packet*)arg, sizeof(accesio_pci_ioctl_packet));
    if (ddata->regions[iodata.bar].address_type == ACCESIO_ADDR_INVALID) { return -ENXIO; }
    if (iodata.offset > ddata->regions[iodata.bar].length) { return -EFAULT; }
    if (ddata->regions[iodata.bar].address_type == ACCESIO_ADDR_IO) {
        tmp = ddata->regions[iodata.bar].start + iodata.offset;
        switch (iodata.size) {
            case ACCESIO_BYTE:  outb(iodata.data, tmp); break;
            case ACCESIO_WORD:  outw(iodata.data, tmp); break;
            case ACCESIO_DWORD: outl(iodata.data, tmp); break;
        };
    } else { // MEM
        void* tadd = ddata->regions[iodata.bar].mapped_address + iodata.offset;
        switch(iodata.size) {
            case ACCESIO_BYTE:  iowrite8(iodata.data, tadd); break;
            case ACCESIO_WORD:  iowrite16(iodata.data, tadd); break;
            case ACCESIO_DWORD: iowrite32(iodata.data, tadd); break;
        };
    }
    return ACCESIO_SUCCESS;
}

static inline int accesio_pci_ioctl_internal_read(accesio_pci_device_info* ddata, unsigned long arg)
{
    int tmp = 0;
    accesio_pci_ioctl_packet iodata;
    if (ACCES_AOK(VERIFY_READ, arg, sizeof(accesio_pci_ioctl_packet)) == 0) { return -EACCES; }
    tmp = copy_from_user(&iodata, (accesio_pci_ioctl_packet*)arg, sizeof(accesio_pci_ioctl_packet));
    if (ddata->regions[iodata.bar].address_type == ACCESIO_ADDR_INVALID) { return -ENXIO; }
    if (iodata.offset > ddata->regions[iodata.bar].length) { return -EFAULT; }
    if (ddata->regions[iodata.bar].address_type == ACCESIO_ADDR_IO) {
        tmp = ddata->regions[iodata.bar].start + iodata.offset;
        switch (iodata.size) {
            case ACCESIO_BYTE:  iodata.data = inb(tmp); break;
            case ACCESIO_WORD:  iodata.data = inw(tmp); break;
            case ACCESIO_DWORD: iodata.data = inl(tmp); break;
        };
    } else { // MEM
        void* tadd = ddata->regions[iodata.bar].mapped_address + iodata.offset;
        switch(iodata.size) {
            case ACCESIO_BYTE:  iodata.data = ioread8(tadd); break;
            case ACCESIO_WORD:  iodata.data = ioread16(tadd); break;
            case ACCESIO_DWORD: iodata.data = ioread32(tadd); break;
        };
    }
    if (copy_to_user((accesio_pci_ioctl_packet*)arg, &iodata, sizeof(accesio_pci_ioctl_packet)) != 0) { return -EIO; }
    return ACCESIO_SUCCESS;
}

static int accesio_pci_ioctl_internal(struct file* filp, unsigned int cmd, unsigned long arg)
{
    unsigned long flags = 0;
    accesio_pci_device_info* ddata = filp->private_data;
    if (!ddata) { return -EINVAL; }
    switch (cmd) {
        case ACCESIO_IOCTL_GET_TOTAL_DEVICE_COUNT:
            return accesio_found_devices;
            
        case ACCESIO_IOCTL_GET_DEVICE_INFO: case ACCESIO_IOCTL_GET_PCI_INFO:
            return accesio_pci_ioctl_internal_get_device_info(ddata, arg);

        case ACCESIO_IOCTL_WRITE: case ACCESIO_IOCTL_PCI_WRITE:
            return accesio_pci_ioctl_internal_write(ddata, arg);

        case ACCESIO_IOCTL_READ: case ACCESIO_IOCTL_PCI_READ:
            return accesio_pci_ioctl_internal_read(ddata, arg);

        case ACCESIO_IOCTL_WAIT:
            spin_lock_irqsave(&(ddata->irq_lock), flags);
            if (ddata->waiting_for_irq) {
                spin_unlock_irqrestore(&(ddata->irq_lock), flags);
                return -EALREADY;
            } else {
                ddata->waiting_for_irq = true;
                ddata->irq_cancelled = false;
            }
            spin_unlock_irqrestore(&(ddata->irq_lock), flags);
            wait_event_interruptible(ddata->wait_queue, !ddata->waiting_for_irq);
            if (ddata->irq_cancelled) { return -ECANCELED; }
            return ACCESIO_SUCCESS;

        case ACCESIO_IOCTL_CANCEL_WAIT:
            spin_lock_irqsave(&(ddata->irq_lock), flags);
            if (ddata->waiting_for_irq) {
                spin_unlock_irqrestore(&(ddata->irq_lock), flags);
                return -EALREADY;
            }
            ddata->irq_cancelled = true;
            ddata->waiting_for_irq = false;
            spin_unlock_irqrestore(&(ddata->irq_lock), flags);
            wake_up_interruptible(&(ddata->wait_queue));
            return ACCESIO_SUCCESS;

        case ACCESIO_IOCTL_GET_DEVICE_IS_PCIE:
            return ddata->is_pcie;
        
        case ACCESIO_IOCTL_GET_DEVICE_IS_PCI:
            return 1;

        case ACCESIO_IOCTL_GET_DEVICE_IS_USB:
            return 0;
        
        case ACCESIO_IOCTL_GET_DEVICE_IRQ_CAPABLE:
            return ddata->irq_capable;

        case ACCESIO_IOCTL_GET_DEVICE_WAITING_FOR_IRQ:
            return ddata->waiting_for_irq;

        case ACCESIO_IOCTL_GET_DEVICE_IRQ_CANCELLED:
            return ddata->irq_cancelled;

        case ACCESIO_IOCTL_GET_DEVICE_PLX_START:
            return ddata->plx_region.start;

        case ACCESIO_IOCTL_GET_DEVICE_PLX_END:
            return ddata->plx_region.end;
    };
    return -ENOSYS;
}

// kernel driver functions (defined in driver.h)

static int accesio_pci_probe(struct pci_dev* pdev, const struct pci_device_id* id)
{
    accesio_pci_device_info* ddata = NULL;
    int ret = 0;
    if (pci_enable_device(pdev)) {
        printk(KERN_INFO KBUILD_MODNAME ": could not enable the pci device\n");
        return -ENODEV;
    }
    ret = accesio_pci_alloc_driver(&ddata, pdev, id);
    if (ret != ACCESIO_SUCCESS) {
        printk(KERN_INFO KBUILD_MODNAME ": error allocating driver, error: %d.\n", ret);
        return ret;
    }
    if (ddata == NULL) {
        printk(KERN_INFO KBUILD_MODNAME ": device data is null.\n");
        return -ENOMEM;
    }
    ret = accesio_pci_set_irq_handlers(ddata);
    if (ret != ACCESIO_SUCCESS) {
        printk(KERN_INFO KBUILD_MODNAME ": error allocating IRQ handlers, error: %d.\n", ret);
        return ret;
    }
    // add to sysfs
    cdev_init(&ddata->cdev, &accesio_pci_file_ops);
    ddata->cdev.owner = THIS_MODULE;
    if (cdev_add(&ddata->cdev, accesio_first_dev + accesio_found_devices, 1)) {
        printk(KERN_INFO KBUILD_MODNAME ": error registering device index: %d\n", accesio_found_devices);
        goto irq_error;
    }
    ddata->device_index = accesio_found_devices;
    pci_set_drvdata(pdev, ddata);
    if (accesio_pci_class_device_register(ddata) != ACCESIO_SUCCESS) {
        printk(KERN_INFO KBUILD_MODNAME ": could not register the device class.\n");
        pci_set_drvdata(pdev, NULL);
        cdev_del(&ddata->cdev);
        goto irq_error;
    }
    return ACCESIO_SUCCESS;

    irq_error:
        if (ddata->irq_capable) { free_irq(pdev->irq, ddata); }
        accesio_pci_free_driver(pdev);
        return -ENODEV;
}

static void accesio_pci_remove(struct pci_dev* pdev)
{
    accesio_pci_device_info* ddata = pci_get_drvdata(pdev);
    spin_lock(&(ddata->irq_lock));
    if (ddata->irq_capable) { free_irq(pdev->irq, ddata); }
    spin_unlock(&(ddata->irq_lock));
    accesio_pci_class_device_unregister(ddata);
    cdev_del(&ddata->cdev);
    accesio_pci_free_driver(pdev);
}

static int accesio_pci_open(struct inode* inode, struct file* filp)
{
    accesio_pci_device_info* ddata = container_of(inode->i_cdev, accesio_pci_device_info, cdev);
    // TODO: should support the following:
    /*
    ACCES_FILE_OP_FLAG_SET(filp->f_flags, O_OP)

    typedef accesio_pci_device_info_flags {
        bool read;
        bool write;
    } accesio_pci_device_info;

    this won't work .. think static instance .. e.g. multiple opens could still have .read == true
    
    if (ACCES_FLAG_SET(filp->f_flags, O_RDONLY)) { // read only
        ddata->flags.read = true;
    } else if (ACCES_FLAG_SET(filp->f_flags, O_RDONLY)) { // write only
        ddata->flags.write = true;
    } else if (ACCES_FLAG_SET(filp->f_flags, O_RDWR)) { // read/write
        ddata->flags.read = true;
        ddata->flags.write = true;
    }
    ACCES_FLAG_SET(filp->f_flags, O_NONBLOCK)

    O_NONBLOCK <-:
        When opening a FIFO with O_RDONLY or O_WRONLY set: 
            * If O_NONBLOCK is set:
              An open() for reading-only shall return without delay.
              An open() for writing-only shall return an error if no process currently has the file open for reading. 
            * If O_NONBLOCK is clear:
              An open() for reading-only shall block the calling thread until a thread opens the file for writing.
              An open() for writing-only shall block the calling thread until a thread opens the file for reading.
        When opening a block special or character special file that supports non-blocking opens:
            * If O_NONBLOCK is set, the open() function shall return without blocking for the device to be ready or available. Subsequent behavior of the device is device-specific. 
            * If O_NONBLOCK is clear, the open() function shall block the calling thread until the device is ready or available before returning.
        Otherwise, the behavior of O_NONBLOCK is unspecified.
    
    */
    if (atomic_read(&(ddata->open_count)) > 0) { return -EBUSY; }
    atomic_inc(&(ddata->open_count));
    #if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
        MOD_INC_USE_COUNT;
    #endif
    filp->private_data = ddata;
    return ACCESIO_SUCCESS;
}

static int accesio_pci_close(struct inode* inode, struct file* filp)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)filp->private_data;
    if (atomic_read(&(ddata->open_count)) > 0) {
        #if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
            MOD_DEC_USE_COUNT;
        #endif
        atomic_dec(&(ddata->open_count));
    }
    return ACCESIO_SUCCESS;
}

static ssize_t accesio_pci_read(struct file* filp, char *__user buf, size_t len, loff_t* offset)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)filp->private_data;
    uint8_t bar = accesio_get_bar(ddata->product_id);
    uint8_t data = 0;
    size_t wrote = 0;
    if (len == 0) { return 0; }
    if (ddata->regions[bar].address_type == ACCESIO_ADDR_INVALID) { return 0; }
    if (filp->f_pos > ddata->regions[bar].length) { return 0; }
    if (buf == NULL) { return 0; }
    while (len-- > 0) {
        if (ddata->regions[bar].address_type == ACCESIO_ADDR_IO) {
            data = inb((ddata->regions[bar].start + filp->f_pos));
        } else { // MEM
            data = ioread8((void*)(ddata->regions[bar].mapped_address + filp->f_pos));
        }
        if (copy_to_user(buf++, &data, sizeof(uint8_t)) == 0) {
            ++wrote;
        }
    }
    return wrote;
}

static ssize_t accesio_pci_write(struct file* filp, const char *__user buf, size_t len, loff_t* offset)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)filp->private_data;
    uint8_t bar = accesio_get_bar(ddata->product_id);
    uint8_t data = 0;
    size_t wrote = 0;
    if (len == 0) { return 0; }
    if (ddata->regions[bar].address_type == ACCESIO_ADDR_INVALID) { return 0; }
    if (filp->f_pos > ddata->regions[bar].length) { return 0; }
    if (buf == NULL) { return 0; }
    while (len-- > 0) {
        if (copy_from_user(&data, buf++, sizeof(uint8_t)) != 0) { break; }
        if (ddata->regions[bar].address_type == ACCESIO_ADDR_IO) {
            outb(data, (ddata->regions[bar].start + filp->f_pos));
        } else { // MEM
            iowrite8(data, (void*)(ddata->regions[bar].mapped_address + filp->f_pos));
        }
        ++wrote;
    }
    return wrote;
}

static loff_t accesio_pci_seek(struct file* filp, loff_t offset, int origin)
{
    accesio_pci_device_info* ddata = (accesio_pci_device_info*)filp->private_data;
    uint8_t bar = accesio_get_bar(ddata->product_id);
    // origin doesn't matter, since we can't go back or forward
    if (offset < 0 || offset >= ddata->regions[bar].length) { return -ESPIPE; }
    filp->f_pos = offset;
    return filp->f_pos;
}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
    int accesio_pci_ioctl(struct inode* inode, struct file* filp, unsigned int cmd, unsigned long arg)
    { (void*)inode; return accesio_pci_ioctl_internal(filp, cmd, arg); }
#else 
    long accesio_pci_ioctl(struct file* filp, unsigned int cmd, unsigned long arg)
    { return accesio_pci_ioctl_internal(filp, cmd, arg); }
#endif

#if defined(CONFIG_PM) || defined(ACCESIO_PCI_AUTOSUSPEND)
    int accesio_pci_suspend(struct pci_dev* pdev, pm_message_t message)
    {
        return ACCESIO_SUCCESS;
    }

    int accesio_pci_resume(struct pci_dev* pdev)
    {
        return ACCESIO_SUCCESS;
    }
#endif

// functions used by new pci code.
int __init accesio_pci_init(void)
{
    dev_t dev = MKDEV(0,0);
    int ret = accesio_class_init(ACCESIO_PCI_MAX_CARDS, DRIVER_NAME);
    if (ret == ACCESIO_SUCCESS) {
        cdev_init(&accesio_pci_cdev, &accesio_pci_file_ops);
        accesio_pci_cdev.owner = THIS_MODULE;
        accesio_pci_cdev.ops = &accesio_pci_file_ops;
        ret = cdev_add(&accesio_pci_cdev, dev, 1);
        if (ret < 0) {
            printk(KERN_INFO KBUILD_MODNAME ": could not add cdev: %d\n", ret);
            accesio_class_destroy(ACCESIO_PCI_MAX_CARDS);
        } else {
            ret = pci_register_driver(&accesio_pci_driver);
            printk(KERN_INFO KBUILD_MODNAME ": " DRIVER_VERSION ": " DRIVER_DESC "\n");
        }
    }
    return ret;
}

void __exit accesio_pci_exit(void)
{
    pci_unregister_driver(&accesio_pci_driver);
    cdev_del(&accesio_pci_cdev);
    accesio_class_destroy(ACCESIO_PCI_MAX_CARDS);
    printk(KERN_INFO KBUILD_MODNAME ": exited PCI module\n");
}

module_init(accesio_pci_init);
module_exit(accesio_pci_exit);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_VERSION(DRIVER_VERSION);
MODULE_LICENSE(DRIVER_LICENSE);
