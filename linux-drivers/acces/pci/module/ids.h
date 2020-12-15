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
#ifndef ACCESIO_LINUX_IDS_H
#define ACCESIO_LINUX_IDS_H

// don't include directly, this is included in module.h

// VENDOR ID
#define ACCESIO_PCI_VID 0x494F

// DEVICE ID'S
#define ACCESIO_PCIE_DIO_24	        0x0C52
#define ACCESIO_PCIE_DIO_24D	    0x0C53
#define ACCESIO_PCIE_DIO_24S	    0x0E53
#define ACCESIO_PCIE_DIO_24DS	    0x0E54
#define ACCESIO_PCIE_DIO_24DC	    0x0E55
#define ACCESIO_PCIE_DIO_24DCS	    0x0E56
#define ACCESIO_PCIE_DIO_48	        0x0C61
#define ACCESIO_PCIE_DIO_48S	    0x0E61
#define ACCESIO_PCIE_DIO_72         0x0C6A 
#define ACCESIO_PCIE_DIO_96         0x0C71
#define ACCESIO_PCIE_DIO_120        0x0C79
#define ACCESIO_PCIE_IIRO_8	        0x0F02
#define ACCESIO_PCIE_IIRO_16	    0x0F09

#define ACCESIO_PCI_DIO_24H	        0x0C50
#define ACCESIO_PCI_DIO_24D	        0x0C51
#define ACCESIO_PCI_DIO_24H_C	    0x0E51
#define ACCESIO_PCI_DIO_24D_C	    0x0E52
#define ACCESIO_PCI_DIO_24S	        0x0E50
#define ACCESIO_PCI_DIO_48	        0x0C60
#define ACCESIO_PCI_DIO_48H	        0x0C60
#define ACCESIO_PCI_DIO_48S	        0x0E60
#define ACCESIO_PCI_DIO_48HS	    0x0E60
#define ACCESIO_PCI_DIO_72	        0x0C68
#define ACCESIO_PCI_DIO_96	        0x0C70
#define ACCESIO_PCI_DIO_96CT	    0x2C50
#define ACCESIO_PCI_DIO_96C3	    0x2C58
#define ACCESIO_PCI_DIO_120	        0x0C78

#define ACCESIO_P104_DIO_48S	    0x0E62
#define ACCESIO_P104_DIO_96	        0x0C69

#define ACCESIO_PCI_AI12_16	        0xACA8
#define ACCESIO_PCI_AI12_16A	    0xACA9
#define ACCESIO_PCI_AIO12_16	    0xECA8
#define ACCESIO_PCI_A12_16A	        0xECAA
#define ACCESIO_PCI_DA12_16	        0x6CB0
#define ACCESIO_PCI_DA12_8	        0x6CA8
#define ACCESIO_PCI_DA12_6	        0x6CA0
#define ACCESIO_PCI_DA12_4	        0x6C98
#define ACCESIO_PCI_DA12_2	        0x6C90
#define ACCESIO_PCI_DA12_16V  	    0x6CB1
#define ACCESIO_PCI_DA12_8V	        0x6CA9
#define ACCESIO_PCI_IIRO_8	        0x0F00
#define ACCESIO_PCI_IIRO_16	        0x0F08
#define ACCESIO_PCI_IDI_48	        0x0920
#define ACCESIO_PCI_IDO_48	        0x0520
#define ACCESIO_PCI_IDIO_16	        0x0DC8

#define ACCESIO_LPCI_A16_16A	    0xECE8
#define ACCESIO_LPCI_IIRO_8	        0x0F01

// watchdog
#define ACCESIO_PCI_WDG_2S	        0x1250
#define ACCESIO_PCI_WDG_CSM	        0x22C0
#define ACCESIO_PCI_WDG_IMPAC	    0x12D0

// mPCIe
#define ACCESIO_MPCIE_DIO_24S       0x0100

// WHEN ADDING NEW PCI DEVICE
// 1.) ADD NEW PCI DEVICE PID
// 2.) INCREASE CARD COUNT
// 3.) ADD TO TABLE accesio_pci_ids
// 4.) ADD TO NAME FUNCTION get_name_from_id
// 5.) ADD TO COUNTER FUNCTION get_counter_from_id

#define ACCESIO_PCI_CARD_COUNT 51

// PCI PID table
static struct pci_device_id accesio_pci_ids[] = {
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_24) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_24D) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_24S) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_24DS) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_24DC) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_24DCS) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_48) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_48S) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_72) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_96) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_DIO_120) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_IIRO_8) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCIE_IIRO_16) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_24H) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_24D) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_24H_C) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_24D_C) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_24S) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_48) },
    //{ PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_48H) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_48S) },
    //{ PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_48HS) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_72) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_96) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_96CT) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_96C3) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DIO_120) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_P104_DIO_48S) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_P104_DIO_96) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_AI12_16) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_AI12_16A) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_AIO12_16) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_A12_16A) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DA12_16) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DA12_8) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DA12_6) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DA12_4) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DA12_2) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DA12_16V ) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_DA12_8V) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_IIRO_8) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_IIRO_16) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_IDI_48) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_IDO_48) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_IDIO_16) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_LPCI_A16_16A) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_LPCI_IIRO_8) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_WDG_2S) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_WDG_CSM) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_PCI_WDG_IMPAC) },
    { PCI_DEVICE(ACCESIO_PCI_VID, ACCESIO_MPCIE_DIO_24S) },
    { } // terminating entry
};
MODULE_DEVICE_TABLE(pci, accesio_pci_ids);

static uint8_t device_counters[ACCESIO_PCI_CARD_COUNT+1];

// These functions are here to map names and device counters
// without utilizing a table or map that would use up kernel
// memory. These functions are only called in a few spots and
// don't need to take up memory just to resolve a name and id

static const char* get_name_from_id(unsigned int id) {
    switch (id) {
        case ACCESIO_PCIE_DIO_24:     return "pcie_dio_24";
        case ACCESIO_PCIE_DIO_24D:    return "pcie_dio_24d";
        case ACCESIO_PCIE_DIO_24S:    return "pcie_dio_24s";
        case ACCESIO_PCIE_DIO_24DS:   return "pcie_dio_24ds";
        case ACCESIO_PCIE_DIO_24DC:   return "pcie_dio_24dc";
        case ACCESIO_PCIE_DIO_24DCS:  return "pcie_dio_24dcs";
        case ACCESIO_PCIE_DIO_48:     return "pcie_dio_48";
        case ACCESIO_PCIE_DIO_48S:    return "pcie_dio_48s";
        case ACCESIO_PCIE_DIO_72:     return "pcie_dio_72";
        case ACCESIO_PCIE_DIO_96:     return "pcie_dio_96";
        case ACCESIO_PCIE_DIO_120:    return "pcie_dio_120";
        case ACCESIO_PCIE_IIRO_8:     return "pcie_iiro_8";
        case ACCESIO_PCIE_IIRO_16:    return "pcie_iiro_16";
        case ACCESIO_PCI_DIO_24H:     return "pci_dio_24h";
        case ACCESIO_PCI_DIO_24D:     return "pci_dio_24d";
        case ACCESIO_PCI_DIO_24H_C:   return "pci_dio_24h_c";
        case ACCESIO_PCI_DIO_24D_C:   return "pci_dio_24d_c";
        case ACCESIO_PCI_DIO_24S:     return "pci_dio_24s";
        case ACCESIO_PCI_DIO_48:      return "pci_dio_48";
        case ACCESIO_PCI_DIO_48S:     return "pci_dio_48s";
        //case ACCESIO_PCI_DIO_48H:   return "pci_dio_48h"; // duplicate
        //case ACCESIO_PCI_DIO_48HS:  return "pci_dio_48hs"; // duplicate
        case ACCESIO_PCI_DIO_72:      return "pci_dio_72";
        case ACCESIO_PCI_DIO_96:      return "pci_dio_96";
        case ACCESIO_PCI_DIO_96CT:    return "pci_dio_96ct";
        case ACCESIO_PCI_DIO_96C3:    return "pci_dio_96c3";
        case ACCESIO_PCI_DIO_120:     return "pci_dio_120";
        case ACCESIO_P104_DIO_48S:    return "p104_dio_48s";
        case ACCESIO_P104_DIO_96:     return "p104_dio_96";
        case ACCESIO_PCI_AI12_16:     return "pci_ai12_16";
        case ACCESIO_PCI_AI12_16A:    return "pci_ai12_16a";
        case ACCESIO_PCI_AIO12_16:    return "pci_aio12_16";
        case ACCESIO_PCI_A12_16A:     return "pci_a12_16a";
        case ACCESIO_PCI_DA12_16:     return "pci_da12_16a";
        case ACCESIO_PCI_DA12_8:      return "pci_da12_8";
        case ACCESIO_PCI_DA12_6:      return "pci_da12_6";
        case ACCESIO_PCI_DA12_4:      return "pci_da12_4";
        case ACCESIO_PCI_DA12_2:      return "pci_da12_2";
        case ACCESIO_PCI_DA12_16V:    return "pci_da12_16v";
        case ACCESIO_PCI_DA12_8V:     return "pci_da12_8v";
        case ACCESIO_PCI_IIRO_8:      return "pci_iiro_8";
        case ACCESIO_PCI_IIRO_16:     return "pci_iiro_16";
        case ACCESIO_PCI_IDI_48:      return "pci_idi_48";
        case ACCESIO_PCI_IDO_48:      return "pci_ido_48";
        case ACCESIO_PCI_IDIO_16:     return "pci_idio_16";
        case ACCESIO_LPCI_A16_16A:    return "lpci_a16_16a";
        case ACCESIO_LPCI_IIRO_8:     return "lpci_iiro_8";
        case ACCESIO_PCI_WDG_2S:      return "pci_wdg_2s";
        case ACCESIO_PCI_WDG_CSM:     return "pci_wdg_csm";
        case ACCESIO_PCI_WDG_IMPAC:   return "pci_wdg_impac";
        case ACCESIO_MPCIE_DIO_24S:   return "mpcie_dio_24s";
        default: break;
    }
    return "unknown_pci";
}

static inline int get_counter_from_id(unsigned int id) {
    switch (id) {
        case ACCESIO_PCIE_DIO_24:     return 1;
        case ACCESIO_PCIE_DIO_24D:    return 2;
        case ACCESIO_PCIE_DIO_24S:    return 3;
        case ACCESIO_PCIE_DIO_24DS:   return 4;
        case ACCESIO_PCIE_DIO_24DC:   return 5;
        case ACCESIO_PCIE_DIO_24DCS:  return 6;
        case ACCESIO_PCIE_DIO_48:     return 7;
        case ACCESIO_PCIE_DIO_48S:    return 8;
        case ACCESIO_PCIE_DIO_72:     return 9;
        case ACCESIO_PCIE_DIO_96:     return 10;
        case ACCESIO_PCIE_DIO_120:    return 11;
        case ACCESIO_PCIE_IIRO_8:     return 12;
        case ACCESIO_PCIE_IIRO_16:    return 13;
        case ACCESIO_PCI_DIO_24H:     return 14;
        case ACCESIO_PCI_DIO_24D:     return 15;
        case ACCESIO_PCI_DIO_24H_C:   return 16;
        case ACCESIO_PCI_DIO_24D_C:   return 17;
        case ACCESIO_PCI_DIO_24S:     return 18;
        case ACCESIO_PCI_DIO_48:      return 19;
        case ACCESIO_PCI_DIO_48S:     return 20;
        //case ACCESIO_PCI_DIO_48H:   return 0; // duplicate
        //case ACCESIO_PCI_DIO_48HS:  return 0; // duplicate
        case ACCESIO_PCI_DIO_72:      return 21;
        case ACCESIO_PCI_DIO_96:      return 22;
        case ACCESIO_PCI_DIO_96CT:    return 23;
        case ACCESIO_PCI_DIO_96C3:    return 24;
        case ACCESIO_PCI_DIO_120:     return 25;
        case ACCESIO_P104_DIO_48S:    return 26;
        case ACCESIO_P104_DIO_96:     return 27;
        case ACCESIO_PCI_AI12_16:     return 28;
        case ACCESIO_PCI_AI12_16A:    return 29;
        case ACCESIO_PCI_AIO12_16:    return 30;
        case ACCESIO_PCI_A12_16A:     return 31;
        case ACCESIO_PCI_DA12_16:     return 32;
        case ACCESIO_PCI_DA12_8:      return 33;
        case ACCESIO_PCI_DA12_6:      return 34;
        case ACCESIO_PCI_DA12_4:      return 35;
        case ACCESIO_PCI_DA12_2:      return 36;
        case ACCESIO_PCI_DA12_16V:    return 37;
        case ACCESIO_PCI_DA12_8V:     return 38;
        case ACCESIO_PCI_IIRO_8:      return 39;
        case ACCESIO_PCI_IIRO_16:     return 40;
        case ACCESIO_PCI_IDI_48:      return 41;
        case ACCESIO_PCI_IDO_48:      return 42;
        case ACCESIO_PCI_IDIO_16:     return 43;
        case ACCESIO_LPCI_A16_16A:    return 44;
        case ACCESIO_LPCI_IIRO_8:     return 45;
        case ACCESIO_PCI_WDG_2S:      return 46;
        case ACCESIO_PCI_WDG_CSM:     return 47;
        case ACCESIO_PCI_WDG_IMPAC:   return 48;
        case ACCESIO_MPCIE_DIO_24S:   return 49;
        default: break;
    }
    return 0;
}

static inline int get_device_counter(unsigned int id) {
    return device_counters[get_counter_from_id(id)];
}

static inline int decrement_device_id(unsigned int id) {
    return --device_counters[get_counter_from_id(id)];
}

static inline int increment_device_id(unsigned int id) {
    return device_counters[get_counter_from_id(id)]++;
}

#endif // ACCESIO_LINUX_IDS_H