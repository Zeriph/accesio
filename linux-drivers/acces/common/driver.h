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
#ifndef ACCESIO_LINUX_DRIVER_COMMON_H
#define ACCESIO_LINUX_DRIVER_COMMON_H

#define ACCESIO_DRIVER_BUILD

#include "linux.h"
#include "declarations.h"
#include "ioctl.h"

#define DRIVER_CLASS_NAME "accesio"
#define DRIVER_DEVICE_FMT DRIVER_CLASS_NAME"/%s_%d"

#if !defined(ACCESIO_NO_CLASS_INIT)

static int accesio_found_devices;
static int accesio_major_num;
static dev_t accesio_first_dev = MKDEV(ACCESIO_MAJOR,0);

#if defined(ACCESIO_CLASS_INIT_FN)
static struct class* accesio_class;

static void accesio_class_destroy(unsigned max_cards)
{
    unregister_chrdev_region(MKDEV(accesio_major_num, 0), max_cards);
    class_destroy(accesio_class);
    accesio_major_num = 0;
}

static int accesio_class_init(unsigned max_cards, const char* driver_name)
{
    int ret = alloc_chrdev_region(&accesio_first_dev, 0, max_cards, driver_name);
    if (ret) {
        printk(KERN_INFO KBUILD_MODNAME ": unable to allocate device region (error %d)\n", ret);
        return ret;
    }
    accesio_major_num = MAJOR(accesio_first_dev);
	accesio_class = class_create(THIS_MODULE, DRIVER_CLASS_NAME);
	if (IS_ERR(&accesio_class)) {
        void* perr = &accesio_class;
        printk(KERN_INFO KBUILD_MODNAME ": could not create class (error %ld)\n", PTR_ERR(perr));
        accesio_class_destroy(max_cards);
	    return PTR_ERR(perr);
    }
    return ACCESIO_SUCCESS;
}
#endif

#endif

#endif // ACCESIO_LINUX_DRIVER_COMMON_H
