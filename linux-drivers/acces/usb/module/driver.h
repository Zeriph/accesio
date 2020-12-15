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

#define DRIVER_NAME "accesio_usb"
#define DRIVER_VERSION "2.0"
#define DRIVER_AUTHOR "Zach Perez <zach.perez@accesio.com>"
#define DRIVER_DESC "ACCES I/O Products, Inc. USB driver"
#define DRIVER_LICENSE "Dual MIT/GPL"

static char* accesio_usb_get_devnode(struct device* dev, umode_t* mode);
static int accesio_usb_probe(struct usb_interface* interface, const struct usb_device_id* id);
static void accesio_usb_disconnect(struct usb_interface* interface);
static void accesio_usb_draw_down(accesio_usb_device_info* dev);
#if defined(CONFIG_PM) || defined(ACCESIO_USB_AUTOSUSPEND)
    static int accesio_usb_suspend(struct usb_interface* intf, pm_message_t message);
    static int accesio_usb_resume(struct usb_interface* intf);
#endif
static int accesio_usb_pre_reset(struct usb_interface* intf);
static int accesio_usb_post_reset(struct usb_interface* intf);
static void accesio_usb_draw_down(accesio_usb_device_info* dev);
static void accesio_usb_delete(struct kref* kref);
static int accesio_usb_open(struct inode* inode, struct file* file);
static int accesio_usb_release(struct inode* inode, struct file* file);
static int accesio_usb_flush(struct file* file, fl_owner_t id);
static void accesio_usb_read_bulk_callback(struct urb* urb);
static int accesio_usb_do_read_io(accesio_usb_device_info* dev, size_t count);
static ssize_t accesio_usb_read(struct file* file, char* buffer, size_t count, loff_t* ppos);
static void accesio_usb_write_bulk_callback(struct urb* urb);
static ssize_t accesio_usb_write(struct file* file, const char* user_buffer, size_t count, loff_t* ppos);
static loff_t accesio_usb_seek(struct file* filp, loff_t off, int origin);
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
static int accesio_usb_ioctl(struct inode* inode, struct file* filp, unsigned int cmd, unsigned long arg);
#else 
static long accesio_usb_ioctl(struct file* filp, unsigned int cmd, unsigned long arg);
#endif

static struct usb_driver accesio_usb_driver = {
    .name = DRIVER_NAME,
    .id_table = accesio_usb_ids,
    .probe = accesio_usb_probe,
    .disconnect = accesio_usb_disconnect,
#if defined(CONFIG_PM) || defined(ACCESIO_USB_AUTOSUSPEND)
    .suspend = accesio_usb_suspend,
    .resume = accesio_usb_resume,
    .supports_autosuspend = 1,
#endif
    .pre_reset = accesio_usb_pre_reset,
    .post_reset = accesio_usb_post_reset,
    .no_dynamic_id = 1,
};

static const struct file_operations accesio_usb_file_ops = {
    .owner = THIS_MODULE,
    .read = accesio_usb_read,
    .write = accesio_usb_write,
    .open = accesio_usb_open,
    .release = accesio_usb_release,
    .flush = accesio_usb_flush,
    .llseek = accesio_usb_seek,
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39)
    .ioctl          = accesio_usb_ioctl,
#else
    .unlocked_ioctl = accesio_usb_ioctl,
#endif
};

/*
 * usb class driver info in order to get a minor number from the usb core,
 * and to have the device registered with the driver core
 */
static struct usb_class_driver accesio_usb_class = {
    .name = DRIVER_CLASS_NAME,
    .fops = &accesio_usb_file_ops,
    .devnode = &accesio_usb_get_devnode,
    .minor_base = ACCESIO_USB_MINOR,
};

#endif // ACCESIO_LINUX_DRIVER_H