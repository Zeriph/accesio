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
#ifndef ACCESIO_USBDEV_H
#define ACCESIO_USBDEV_H

#include <linux/usb/ch9.h>
#include "declarations.h"

/**
 * @brief Describes the USB endpoint type.
 */
enum accesio_usb_endpoint_type {
    ACCESIO_USB_BULK_EP = 0,
    ACCESIO_USB_CTRL_EP = 1,
    ACCESIO_USB_INT_EP = 2,
    ACCESIO_USB_ISO_EP = 3
};

typedef struct accesio_usb_ep {
    enum accesio_usb_endpoint_type endpoint_type;

    unsigned char in_address;  // inbound-endpoint address
    size_t in_buffer_size;     // inbound-i/o buffer size
    size_t in_buffer_filled;   // inbound-bytes in buffer
    size_t in_buffer_copied;   // inbound-already copied to user space

    unsigned char out_address; // outbound-endpoint address
    size_t out_buffer_size;    // outbound-i/o buffer size
    size_t out_buffer_filled;  // outbound-bytes in buffer
    size_t out_buffer_copied;  // outbound-already copied to user space
} accesio_usb_ep;

typedef struct accesio_usb_info {
    /* the devices endpoint information */
    accesio_usb_ep endpoints[4];
    /* the last request tanked */
    int errors;
    /* a read is going on */
    bool ongoing_read;
    /* true if currently sending a urb */
    bool ctrl_msg;
    /* the device index of the dev tree */
    uint32_t device_index;
    /* the devices product id */
    uint32_t product_id;
    /* @devnum: device number; address on a USB bus*/
    int kernel_devnum;
    /* @devpath: device ID string for use in messages (e.g., /port/...)*/
    char kernel_devpath[16];
    /* @route: tree topology hex string for use with xHCI*/
    uint32_t kernel_route;
    /* @state: device state: configured, not attached, etc.*/
    enum usb_device_state kernel_usb_state;
    /* @speed: device speed: high/full/low (or error)*/
    enum usb_device_speed kernel_usb_speed;
    /* @bus_mA: Current available from the bus*/
    unsigned short kernel_usb_bus_mA;
    /* @portnum: parent port number (origin 1)*/
    uint8_t kernel_usb_portnum;
    /* @level: number of USB hub ancestors*/
    uint8_t kernel_usb_level;
    /* @can_submit: URBs may be submitted*/
    bool kernel_usb_can_submit;
    /* @persist_enabled:  USB_PERSIST enabled for this device*/
    bool kernel_usb_persist_enabled;
    /* @have_langid: whether string_langid is valid*/
    bool kernel_usb_have_langid;
    /* @authorized: policy has said we can use it;*/
    /*	(user space) policy determines if we authorize this device to be*/
    /*	used or not. By default, wired USB devices are authorized.*/
    /*	WUSB devices are not, until we authorize them from user space.*/
    bool kernel_usb_authorized;
    /* @authenticated: Crypto authentication passed*/
    bool kernel_usb_authenticated;
    /* @wusb: device is Wireless USB*/
    bool kernel_usb_wusb;
    /* @lpm_capable: device supports LPM*/
    bool kernel_usb_lpm_capable;
    /* @usb2_hw_lpm_capable: device can perform USB2 hardware LPM*/
    bool kernel_usb2_hw_lpm_capable;
    /* @usb2_hw_lpm_besl_capable: device can perform USB2 hardware BESL LPM*/
    bool kernel_usb2_hw_lpm_besl_capable;
    /* @usb2_hw_lpm_enabled: USB2 hardware LPM is enabled*/
    bool kernel_usb2_hw_lpm_enabled;
    /* @usb2_hw_lpm_allowed: Userspace allows USB 2.0 LPM to be enabled*/
    bool kernel_usb2_hw_lpm_allowed;
    /* @string_langid: language ID for strings*/
    int kernel_usb_string_langid;
    /* @quirks: quirks of the whole device*/
    uint32_t kernel_usb_quirks;
    /* @urbnum: number of URBs submitted for the whole device*/
    uint64_t kernel_usb_urbnum;
    /* @active_duration: total time device is not suspended*/
    unsigned long kernel_usb_active_duration;
    #if defined(CONFIG_PM) || defined(ACCESIO_USB_AUTOSUSPEND)
        /* @connect_time: time device was first connected*/
        unsigned long kernel_usb_connect_time;
        /* @do_remote_wakeup:  remote wakeup should be enabled*/
        bool kernel_usb_do_remote_wakeup;
        /* @reset_resume: needs reset instead of resume*/
        bool kernel_usb_reset_resume;
        /* @port_is_suspended: the upstream port is suspended (L2 or U3)*/
        bool kernel_usb_port_is_suspended;
    #endif
    /* @slot_id: Slot ID assigned by xHCI*/
    int kernel_usb_slot_id;
    /* @lpm_disable_count: Ref count used by usb_disable_lpm() and usb_enable_lpm()*/
    /*	to keep track of the number of functions that require USB 3.0 Link Power*/
    /*	Management to be disabled for this usb_device.  This count should only*/
    /*	be manipulated by those functions, with the bandwidth_mutex is held.*/
    unsigned kernel_usb_lpm_disable_count;
} accesio_usb_info;

#endif // ACCESIO_USBDEV_H
