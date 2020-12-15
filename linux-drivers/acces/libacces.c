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
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>

/**
 * these are defined in other source; we are redefing them here so that this
 * translation unit doesn't need to rely on anything other than standard C
 * library and kernel calls. If these change in the main drivers, these defines
 * need to be updated as well to stay in sync: in particular, the magic num
 * or the IO values to specify wait/cancel.
*/
#define ACCESIO_SUCCESS 0
#define ACCESIO_MAGIC_NUM 0xE0
#define ACCESIO_IOCTL_WAIT                          _IO(ACCESIO_MAGIC_NUM, 5)
#define ACCESIO_IOCTL_CANCEL_WAIT                   _IO(ACCESIO_MAGIC_NUM, 6)

/**
 * @brief           Closes the handle that was retrieved with open_device.
 * 
 * @param   fd      The file descriptor retrieved from open_device
 * 
 * @return  int     On success, 0 is returned, on failure the error
 *                  code is returned.
 */
int close_handle(int fd)
{
    if (fd == 0) { return -EINVAL; }
    if (close(fd) == -1) { return -errno; }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Cancels any IRQ wait requests issued to the file
 *                  descriptor specified.
 * 
 * @param   fd      The file descriptor retrieved from open_device
 * 
 * @return  int     On success, 0 is returned, on failure the error
 *                  code is returned.
 */
int cancel_wait_irq(int fd)
{
    if (fd == 0) { return -EINVAL; }
    if (ioctl(fd, ACCESIO_IOCTL_CANCEL_WAIT) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Open's a system character device specified by path,
 *                  returning the file descriptor handle to utilize in
 *                  other functions of this wrapper.
 * 
 * @param   device  The full path to the ACCES I/O character device,
 *                  usually under /dev/accesio/
 * 
 * @return  int     On success, the file descriptor is returned, on
 *                  failure, the error code is returned.
 */
int open_device(const char* device)
{
    int fd = 0;
    if (device == NULL) { return -EINVAL; }
    fd = open(device, O_RDWR);
    if (fd == -1) {
        return -errno;
    }
    return fd;
}

/**
 * @brief           Reads 1 byte of data from the device specified by
 *                  the file descriptor.
 * 
 * @param   fd      The file descriptor retrieved from open_device
 * 
 * @return  int     On success, the value read is returned (>0), on
 *                  failure the error code is returned.
 */
int read_handle(int fd)
{
    int data = 0;
    if (fd == 0) { return -EINVAL; }
    if (read(fd, &data, 1) == -1) {
        return -errno;
    }
    return data;
}

/**
 * @brief           Sets the underlying file pointer to the register
 *                  offset specified for future read/write calls.
 * 
 * @param   fd      The file descriptor retrieved from open_device
 * @param   offset  The register offset to set to read/write to
 * 
 * @return  int     On success, 0 is returned, on failure the error
 *                  code is returned.
 */
int set_register_offset(int fd, int offset)
{
    if (fd == 0) { return -EINVAL; }
    if (lseek(fd, offset, 0) == (off_t)-1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Reads 1 byte of data at the register offset specified,
 *                  from the device specified by the file descriptor.
 * 
 * @param   fd      The file descriptor retrieved from open_device
 * @param   offset  The register offset to read from
 * 
 * @return  int     On success, the value read is returned (>0), on
 *                  failure the error code is returned.
 */
int read_offset(int fd, int offset)
{
    set_register_offset(fd, offset);
    return read_handle(fd);
}

/**
 * @brief           Writes 1 byte of data to the device specified by
 *                  the file descriptor.
 * 
 * @param   fd      The file descriptor retrieved from open_device
 * @param   data    The 8-bit value to write to the card.
 * 
 * @return  int     On success, 0 is returned, on failure the error
 *                  code is returned.
 */
int write_handle(int fd, int data)
{
    if (fd == 0) { return -EINVAL; }
    if (write(fd, &data, 1) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}

/**
 * @brief           Writes 1 byte of data at the register offset specified,
 *                  from the device specified by the file descriptor.
 * 
 * @param   fd      The file descriptor retrieved from open_device
 * @param   offset  The register offset to write to
 * @param   data    The 8-bit value to write to the card.
 * 
 * @return  int     On success, 0 is returned, on failure the error
 *                  code is returned.
 */
int write_offset(int fd, int offset, int data)
{
    set_register_offset(fd, offset);
    return write_handle(fd, data);
}

/**
 * @brief           Waits for an interupt request from the device
 *                  specified by the file descriptor.
 * 
 * @param   fd      The file descriptor retrieved from open_device
 * 
 * @return  int     On success, 0 is returned, on failure the error
 *                  code is returned.
 */
int wait_for_irq(int fd)
{
    if (fd == 0) { return -EINVAL; }
	if (ioctl(fd, ACCESIO_IOCTL_WAIT) == -1) {
        return -errno;
    }
    return ACCESIO_SUCCESS;
}
