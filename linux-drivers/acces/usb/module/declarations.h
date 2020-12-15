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
#ifndef ACCESIO_LINUX_DECLARATIONS_H
#define ACCESIO_LINUX_DECLARATIONS_H

#define ACCESIO_USB_CARDS 255

// Minor range for your devices from the usb maintainer
#define ACCESIO_USB_MINOR	192

/* ACCESIO_USB_MAX_XFR is chosen so that the VM is not stressed by
allocations > PAGE_SIZE and the number of packets in a page
is an integer 512 is the largest possible packet on EHCI */
#define ACCESIO_USB_MAX_XFR (PAGE_SIZE - 512)

// arbitrarily chosen (writes in flight)
#define ACCESIO_USB_WIF	8

#define ACCESIO_USB_ANCHOR_TIMEOUT 1000

/*
 * These are the requests (bRequest) that the bootstrap loader is expected
 * to recognize.  The codes are reserved by Cypress, and these values match
 * what EZ-USB hardware, or "Vend_Ax" firmware (2nd stage loader) uses.
 * Cypress' "a3load" is nice because it supports both FX and FX2, although
 * it doesn't have the EEPROM support (subset of "Vend_Ax").
 */
#define ACCESIO_USB_REQ_INT 0xA0  // hardware implements this one
#define ACCESIO_USB_REQ_MEM 0xA3
#define ACCESIO_USB_WRITE_RETRY 5
#define ACCESIO_USB_RAM_REG 0xE600

#endif // ACCESIO_LINUX_DECLARATIONS_H