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
#ifndef ACCESIO_COMMON_DEC_H
#define ACCESIO_COMMON_DEC_H

#define ACCESIO_SUCCESS 0
#if !defined(ACCESIO_MAJOR)
    #define ACCESIO_MAJOR  98
#endif
#define ACCESIO_MAX_REGIONS 6

#if !defined(ACCESIO_PCI_CHANNELS)
    #define ACCESIO_PCI_CHANNELS 8 
#endif
#if !defined(ACCESIO_PCI_CARDS)
    #define ACCESIO_PCI_CARDS 8
#endif
#if !defined(ACCESIO_PCI_MAX_CARDS)
    #define ACCESIO_PCI_MAX_CARDS (ACCESIO_PCI_CHANNELS * ACCESIO_PCI_CARDS)
#endif

#define ACCES_FILE_OP_FLAG_SET(v, f) (((v) & (f)) == (f))

#endif // ACCESIO_COMMON_DEC_H