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

typedef struct accesio_usb_endpoint_info {
    unsigned char address;    // endpoint address
    unsigned char* buffer;  // i/o buffer
    size_t buffer_size;     // i/o buffer size
    size_t filled;          // bytes in buffer
    size_t copied;          // already copied to user space
    struct urb* urb;        // urb of the endpoint
} accesio_usb_endpoint_info;

typedef struct accesio_usb_endpoint {
    accesio_usb_endpoint_info in;
    accesio_usb_endpoint_info out;
} accesio_usb_endpoint;

typedef struct accesio_usb_endpoints {
    accesio_usb_endpoint bulk;
    accesio_usb_endpoint control;
    accesio_usb_endpoint interrupt;   // future devices
    accesio_usb_endpoint isochronous; // future devices
} accesio_usb_endpoints;

typedef struct accesio_usb_device_info {
    struct usb_device* udev;         /* the usb kernel device for this device */
    struct usb_interface* interface; /* the interface for this device */
    struct semaphore limit_sem;      /* limiting the number of writes in progress */
    struct usb_anchor submitted;     /* in case we need to retract our submissions */
    accesio_usb_endpoints endpoints;
    int errors;                      /* the last request tanked */
    bool ongoing_read;               /* a read is going on */
    spinlock_t err_lock;             /* lock for errors */
    struct kref kref;                /* kernel reference object */
    struct mutex io_mutex;           /* synchronize I/O with disconnect */
    wait_queue_head_t io_wait;       /* to wait for an ongoing read */
    
    bool ctrl_msg;                    /* true if currently sending a urb */
    uint32_t device_index;            /* the device index of the dev tree */
    uint32_t product_id;              /* the devices product id */
} accesio_usb_device_info;

#endif // ACCESIO_DRIVER_BUILD

#endif // ACCESIO_LINUX_TYPES_H