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
#ifndef ACCESIO_LINUX_H
#define ACCESIO_LINUX_H

#include <stddef.h>
#include "os.h"

#if defined(ACCESIO_DRIVER_BUILD)
    #if defined(ACCESIO_OS_LINUX) || defined(ACCESIO_OS_GNU_LINUX) || defined(ACCESIO_OS_ANDROID)
        #include <linux/types.h>
        #include <linux/errno.h>
        #include <linux/kernel.h>
        #include <linux/module.h>
        #include <linux/init.h>
        #include <linux/interrupt.h>
        #include <linux/string.h>
        #include <linux/atomic.h>
        #if defined(ACCESIO_LINUX_USE_ASM_IO)
            #include <asm/io.h>
            #include <asm/ioctl.h>
            #include <asm/uaccess.h>
        #else
            #include <linux/io.h>
            #include <linux/ioctl.h>
            #include <linux/uaccess.h>
        #endif
        #include <asm/byteorder.h>
        #include <linux/bitops.h>
        #include <linux/fs.h>
        #include <linux/tty.h>
        #include <linux/tty_flip.h>
        #include <linux/cdev.h>
        #include <linux/ioport.h>
        #include <linux/idr.h>
        #include <linux/slab.h>
        #include <linux/jiffies.h>
        #include <linux/sched.h>
        #include <linux/version.h>
        #include <linux/module.h>
        #include <linux/pci.h>
        // serial includes
        #include <linux/delay.h>
        #include <linux/serial_reg.h>
        #include <linux/serial_core.h>
        #include <linux/8250_pci.h>
        // usb includes
        #include <linux/serial.h>
        #include <linux/usb.h>
        #include <linux/usb/ch9.h>
        #include <linux/firmware.h>
        #include <linux/usb/serial.h>
        #include <linux/kref.h>
        #include <linux/mutex.h>

        #if LINUX_VERSION_CODE < KERNEL_VERSION(5,0,0)
            #define ACCES_AOK(v,a,s) access_ok(v, a, s)
        #else
            #define ACCES_AOK(v,a,s) access_ok(a, s)
        #endif
    //#elif defined(ACCESIO_OS_APPLE)
        
    #else
        #error "Unsupported OS detected in preprocessor."
    #endif
#else
    #include <fcntl.h>
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include <errno.h>
    #include <sys/fcntl.h>
    #include <sys/stat.h>
    #include <sys/ioctl.h>
    #include <stdio.h>
    #if defined(ACCESIO_OS_LINUX) || defined(ACCESIO_OS_GNU_LINUX) || defined(ACCESIO_OS_ANDROID)
        #include <linux/types.h>
        #include <linux/string.h>
        #include <linux/errno.h>
        #include <linux/sched.h>
    #endif
#endif // ACCESIO_DRIVER_BUILD

#endif // ACCESIO_LINUX_H
