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
#ifndef ACCESIO_LINUX_DRIVER_H
#define ACCESIO_LINUX_DRIVER_H

// don't include directly, this is included in module.h

#define DRIVER_NAME "accesio_pci"
#define DRIVER_VERSION "2.0"
#define DRIVER_AUTHOR "Zach Perez <zach.perez@accesio.com>"
#define DRIVER_DESC "ACCES I/O Products, Inc. PCI driver"
#define DRIVER_LICENSE "Dual MIT/GPL"

static int accesio_pci_probe(struct pci_dev* pdev, const struct pci_device_id* id);
static void accesio_pci_remove(struct pci_dev* pdev);
static int accesio_pci_open(struct inode* inode, struct file* filp);
static int accesio_pci_close(struct inode* inode, struct file* filp);
static ssize_t accesio_pci_read(struct file* filp, char *__user buf, size_t len, loff_t* off);
static ssize_t accesio_pci_write(struct file* filp, const char *__user buf, size_t len, loff_t *off);
static loff_t accesio_pci_seek(struct file* filp, loff_t off, int origin);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static int accesio_pci_ioctl(struct inode* inode, struct file* filp, unsigned int cmd, unsigned long arg);
#else 
static long accesio_pci_ioctl(struct file* filp, unsigned int cmd, unsigned long arg);
#endif
#if defined(CONFIG_PM) || defined(ACCESIO_PCI_AUTOSUSPEND)
static int accesio_pci_suspend(struct pci_dev* pdev, pm_message_t message);
static int accesio_pci_resume(struct pci_dev* pdev);
#endif

static struct pci_driver accesio_pci_driver = {
    .name       = DRIVER_NAME,
    .id_table   = accesio_pci_ids,
    .probe      = accesio_pci_probe,
#if defined(CONFIG_PM) || defined(ACCESIO_PCI_AUTOSUSPEND)
    .suspend    = accesio_pci_suspend,
    .resume     = accesio_pci_resume,
#endif
    .remove     = accesio_pci_remove
};

static struct file_operations accesio_pci_file_ops = { 
    .open           = accesio_pci_open,
    .release        = accesio_pci_close,
    .read           = accesio_pci_read,
    .write          = accesio_pci_write,
    .llseek         = accesio_pci_seek,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
    .ioctl          = accesio_pci_ioctl,
#else
    .unlocked_ioctl = accesio_pci_ioctl,
#endif
};

static struct cdev accesio_pci_cdev;

#endif // ACCESIO_LINUX_DRIVER_H