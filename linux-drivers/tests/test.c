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

/* This file is to demonstrate how to utilize both the ACCES I/O C API
as well as how to utilize normal C library functions to communicate
with the ACCES I/O PCI device. */
#include <acces/api.h>

static void parse_error(int err)
{
    printf("error = ");
    switch (err) {
        case -EACCES: printf("EACCES"); break;
        case -ENXIO: printf("ENXIO"); break;
        case -EIO: printf("EIO"); break;
        case -EINVAL: printf("EINVAL"); break;
        case -EFAULT: printf("EFAULT"); break;
        default: printf("unknown (%d)", err); break;
    }
    printf("\n");
}

static void do_api_usb_test(const char* dev_name)
{
    accesio_usb_device device;
    if (accesio_open_usb_device(dev_name, &device) == ACCESIO_SUCCESS) {
        printf("Device %s opened:\n", dev_name);
        printf("ep_bulk_in_addr: %d\n", device.device_info.endpoints[ACCESIO_USB_BULK_EP].in_address);
        printf("ep_bulk_in_buffer_size: %zu\n", device.device_info.endpoints[ACCESIO_USB_BULK_EP].in_buffer_size);
        printf("ep_bulk_out_addr: %d\n", device.device_info.endpoints[ACCESIO_USB_BULK_EP].out_address);
        printf("ep_bulk_out_buffer_size: %zu\n", device.device_info.endpoints[ACCESIO_USB_BULK_EP].out_buffer_size);
        printf("errors: %d\n",device.device_info.errors);
        printf("reading: %d\n",device.device_info.ongoing_read);
        printf("device index: %d\n",device.device_info.device_index);
        printf("product_id: 0x%04X\n",device.device_info.product_id);
        printf("kernel_devnum: %d\n",device.device_info.kernel_devnum);
        printf("kernel_route: %d\n",device.device_info.kernel_route);
        printf("kernel_usb_state: %d\n",device.device_info.kernel_usb_state);
        printf("kernel_usb_speed: %d\n",device.device_info.kernel_usb_speed);
        printf("kernel_usb_bus_mA: %d\n",device.device_info.kernel_usb_bus_mA);
        printf("kernel_usb_portnum: %d\n",device.device_info.kernel_usb_portnum);
        printf("kernel_usb_level: %d\n",device.device_info.kernel_usb_level);
        printf("kernel_usb_wusb: %d\n",device.device_info.kernel_usb_wusb);
        printf("kernel_usb_lpm_capable: %d\n",device.device_info.kernel_usb_lpm_capable);
        printf("kernel_usb_string_langid: %d\n",device.device_info.kernel_usb_string_langid);
        printf("kernel_usb_quirks: %d\n",device.device_info.kernel_usb_quirks);
        printf("kernel_usb_urbnum: %lu\n",device.device_info.kernel_usb_urbnum);
        printf("kernel_usb_active_duration: %lu\n",device.device_info.kernel_usb_active_duration);
        printf("kernel_usb_slot_id: %d\n",device.device_info.kernel_usb_slot_id);
        printf("kernel_usb_lpm_disable_count: %d\n\n",device.device_info.kernel_usb_lpm_disable_count);
        accesio_close_usb_device(&device);
    } else {
        printf("Could not open device '%s' (are you root?).\n", dev_name);
    }
}

static void do_api_test(const char* dev_name)
{
    accesio_pci_device device;
    if (accesio_open_device(dev_name, &device) == ACCESIO_SUCCESS) {
        int ret = 0;
        int tmp = 0;
        printf("Communicating with device %s\n", dev_name);
        for (; tmp < device.device_info.base_length; ++tmp) {
            uint8_t data = 0;
            printf("Reading from offset 0x%02X\n", tmp);
            ret = accesio_read_byte(&device, tmp, &data);
            if (ret == ACCESIO_SUCCESS) {
                printf("data read = 0x%02X\n", data);
            } else {
                parse_error(ret);
            }
        }
        for (tmp = 0; tmp < device.device_info.base_length; ++tmp) {
            printf("Writing 0x00 to offset 0x%02X\n", tmp);
            ret = accesio_write_byte(&device, tmp, 0x00);
            if (ret == ACCESIO_SUCCESS) {
                printf("wrote data\n");
            } else {
                parse_error(ret);
            }
        }
        accesio_close_device(&device);
    } else {
        printf("Could not open device '%s' (are you root?).\n", dev_name);
    }
}

static void do_stdlib_test(const char* dev_name)
{
    int fd = open(dev_name, O_RDWR);
    if (fd != -1) {
        int ret = 0;
        int tmp = 0;
        uint8_t data = 0;
        printf("Communicating with device %s\n", dev_name);
        for (; tmp < 16; ++tmp) {
            lseek(fd, tmp, 0);
            printf("Reading from offset 0x%02X\n", tmp);
            ret = read(fd, &data, 1);
            if (ret != -1) {
                printf("data read = 0x%02X\n", data);
            } else {
                parse_error(-errno);
            }
        }
        for (data = 0, tmp = 0; tmp < 16; ++tmp) {
            lseek(fd, tmp, 0);
            printf("Writing 0x00 to offset 0x%02X\n", tmp);
            ret = write(fd, &data, 1);
            if (ret != -1) {
                printf("wrote data\n");
            } else {
                parse_error(-errno);
            }
        }
        close(fd);
    } else {
        printf("Could not open device '%s', error %d (are you root?).\n", dev_name, errno);
    }
}

int main (int argc, char** argv)
{
    if (argc > 1) {
        const char* dev_name = argv[1];
        char* u = strstr(dev_name, "usb_");
        if (u != NULL) {
            do_api_usb_test(dev_name);
        } else {
            do_api_test(dev_name);
            do_stdlib_test(dev_name);
        }
    } else {
        printf("usage: test /dev/accesio/device\n");
    }
    return 0;
}
