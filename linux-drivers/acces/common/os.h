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
#if !defined(ACCESIO_OS_H)
#define ACCESIO_OS_H 1

#if defined(ACCESIO_OS_IGNORE)
    /*
    This file was part of the Omni Framework (https://zeriph.com/omni/), and has been modified
    to reference ACCES I/O products.
    */
#else
    // http://sourceforge.net/p/predef/wiki/Home/
    // Windows
    #if defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || \
        defined(__WINDOWS__) || defined(_WIN32_WCE) || defined(__WIN64__) || defined(_MSC_VER) || defined(MSDOS) || \
        defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
        #define ACCESIO_OS_WIN
    #endif
    
    /*#if defined(__CYGWIN__) || defined(__MINGW32__)
        #if defined(ACCESIO_OS_WIN)
            #define ACCESIO_OS_CYGWIN
        #else
            #error "ACCESIO_OS_WIN in Cygwin environment" 
        #endif
    #endif*/
    
    // UNIX Environment
    #if defined(__unix__) || defined(__unix)
        #define ACCESIO_OS_UNIX
    #endif
    // MacOS
    #if defined(macintosh) || ((defined(__APPLE__) || defined(__APPLE_CC__)) && defined(__MACH__))
        #define ACCESIO_OS_APPLE
        #include <AvailabilityMacros.h>
        #if MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_7
            #define ACCESIO_OS_MACOS
        #endif
    #endif
    // BSD Environment
    #if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__) || defined(__DragonFly__)
        #define ACCESIO_OS_BSD
    #endif
    // Linux kernel
    #if defined(__linux__)
        #define ACCESIO_OS_LINUX
    #endif
    // Solaris
    #if defined(sun) || defined(__sun)
        #define ACCESIO_OS_SOLARIS
    #endif
    // SVR4 Environment
    #if defined(__sysv__) || defined(__SVR4) || defined(__svr4__) || defined(_SYSTYPE_SVR4)
        #define ACCESIO_OS_SVR
    #endif
    #if defined(ACCESIO_OS_SOLARIS)
        //Use the SVR4 macros to distinguish between Solaris and SunOS.
        # if defined(__SVR4) || defined(__svr4__)
            /* Solaris */
            // #define ACCESIO_OS_SOLARIS
        # else
            /* SunOS */
            #define ACCESIO_OS_SUNOS
        # endif
    #endif
    // start OS specific defines
    // DragonFly
    #if defined(__DragonFly__)
        #define ACCESIO_OS_DRAGONFLYBSD
    #endif
    // FreeBSD
    #if defined(__FreeBSD__)
        #define ACCESIO_OS_FREEBSD
    #endif
    // GNU aka GNU/Hurd
    #if defined(__GNU__) || defined(__gnu_hurd__)
        #define ACCESIO_OS_GNU_HURD
    #endif
    // GNU/kFreeBSD
    #if defined(__FreeBSD_kernel__) && defined(__GLIBC__)
        #define ACCESIO_OS_GNU_FREEBSD
    #endif
    // GNU/Linux
    #if defined(__gnu_linux__)
        #define ACCESIO_OS_GNU_LINUX
    #endif
    // MSDOS
    #if defined(MSDOS) || defined(__MSDOS__) || defined(_MSDOS) || defined(__DOS__)
        #define ACCESIO_OS_MSDOS
    #endif
    // Windows CE
    #if defined(_WIN32_WCE)
        #define ACCESIO_OS_WINCE
    #endif
    // OS/2
    #if defined(OS2) || defined(_OS2) || defined(__OS2__) || defined(__TOS_OS2__)
        #define ACCESIO_OS_OS2
    #endif
    // OpenBSD
    #if defined(__OpenBSD__)
        #define ACCESIO_OS_OPENBSD
    #endif
    // NetBSD
    #if defined(__NetBSD__)
        #define ACCESIO_OS_NETBSD
    #endif
    // AIX
    #if defined(_AIX) || defined(__TOS_AIX__)
        #define ACCESIO_OS_AIX
    #endif
    // Android
    #if defined(__ANDROID__)
        #define ACCESIO_OS_ANDROID
    #endif
    // Amdahl UTS
    #if defined(UTS)
        #define ACCESIO_OS_UTS
    #endif
    // AmigaOS
    #if defined(AMIGA) || defined(__amigaos__)
        #define ACCESIO_OS_AMIGA
    #endif
    // Apollo AEGIS
    #if defined(aegis)
        #define ACCESIO_OS_AEGIS
    #endif
    // Apollo Domain/OS
    #if defined(apollo)
        #define ACCESIO_OS_APPOLO
    #endif
    // BeOS
    #if defined(__BEOS__)
        #define ACCESIO_OS_BEOS
    #endif
    // Blue Gene
    #if defined(__bg__)
        #define ACCESIO_OS_BLUEGENE
    #endif
    // BSD/OS
    #if defined(__bsdi__)
        #define ACCESIO_OS_BSDI
    #endif
    // Cygwin
    #if defined(__CYGWIN__)
        #define ACCESIO_OS_CYGWIN
    #endif
    // ConvexOS
    #if defined(__convex__)
        #define ACCESIO_OS_CONVEX
    #endif
    // DG/UX
    #if defined(DGUX) || defined(__DGUX__) || defined(__dgux__)
        #define ACCESIO_OS_DGUX
    #endif
    // DYNIX/ptx
    #if defined(_SEQUENT_) || defined(sequent)
        #define ACCESIO_OS_DYNIX
    #endif
    // eCos
    #if defined(__ECOS)
        #define ACCESIO_OS_ECOS
    #endif
    // EMX Environment
    #if defined(__EMX__)
        #define ACCESIO_OS_EMX
    #endif
    // HI-UX MPP
    #if defined(__hiuxmpp)
        #define ACCESIO_OS_HIUXMPP
    #endif
    // HP-UX
    #if defined(_hpux) || defined(hpux) || defined(__hpux)
        #define ACCESIO_OS_HPUX
    #endif
    // IBM OS/400
    #if defined(__OS400__)
        #define ACCESIO_OS_OS400
    #endif
    // INTEGRITY
    #if defined(__INTEGRITY)
        #define ACCESIO_OS_INTEGRITY
    #endif
    // Interix Environment
    #if defined(__INTERIX)
        #define ACCESIO_OS_INTERIX
    #endif
    // IRIX
    #if defined(sgi) || defined(__sgi)
        #define ACCESIO_OS_IRIX
    #endif
    // LynxOS
    #if defined(__Lynx__)
        #define ACCESIO_OS_LYNXOS
    #endif
    // Microware OS-9
    #if defined(__OS9000) || defined(_OSK)
        #define ACCESIO_OS_MICROWARE_OS9
    #endif
    // MSYS/MinGW32 Environment
    #if defined(__MINGW32__)
        #define ACCESIO_OS_MINGW
    #endif
    // MINIX
    #if defined(__minix)
        #define ACCESIO_OS_MINIX
    #endif
    // MorphOS
    #if defined(__MORPHOS__)
        #define ACCESIO_OS_MORPHOS
    #endif
    // MPE/iX
    #if defined(mpeix) || defined(__mpexl)
        #define ACCESIO_OS_MPEIX
    #endif
    // NonStop
    #if defined(__TANDEM)
        #define ACCESIO_OS_NONSTOP
    #endif
    // Nucleus RTOS
    #if defined(__nucleus__)
        #define ACCESIO_OS_NUCLEUS
    #endif
    // Palm OS
    #if defined(__palmos__)
        #define ACCESIO_OS_PALMOS
    #endif
    // Pyramid DC/OSx
    #if defined(pyr)
        #define ACCESIO_OS_PYRAMID
    #endif
    // QNX
    #if defined(__QNX__) || defined(__QNXNTO__)
        #define ACCESIO_OS_QNX
    #endif
    // Reliant UNIX
    #if defined(sinux)
        #define ACCESIO_OS_RELIANT_UNIX
    #endif
    // SCO OpenServer
    #if defined(M_I386) || defined(M_XENIX) || defined(_SCO_DS)
        #define ACCESIO_OS_SCO_OPENSERVER
    #endif
    // Stratus VOS
    #if defined(__VOS__)
        #define ACCESIO_OS_VOS
    #endif
    // Syllable
    #if defined(__SYLLABLE__)
        #define ACCESIO_OS_SYLLABLE
    #endif
    // Symbian OS
    #if defined(__SYMBIAN32__)
        #define ACCESIO_OS_SYMBIAN
    #endif
    // Tru64 (OSF/1)
    #if defined(__osf__) || defined(__osf)
        #define ACCESIO_OS_OSF1
    #endif
    // Ultrix
    #if defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || (defined(unix) && defined(vax))
        #define ACCESIO_OS_ULTRIX
    #endif
    // UNICOS
    #if defined(_UNICOS)
        #define ACCESIO_OS_UNICOS
    #endif
    // UNICOS/mp
    #if defined(_CRAY) || defined(__crayx1)
        #define ACCESIO_OS_CRAY
    #endif
    // UnixWare
    #if defined(sco) || defined(_UNIXWARE7)
        #define ACCESIO_OS_UNIXWARE
    #endif
    // U/Win Environment
    #if defined(_UWIN)
        #define ACCESIO_OS_UWIN
    #endif
    // VMS
    #if defined(__VMS)
        #define ACCESIO_OS_VMS
    #endif
    // Wind/U Environment
    #if defined(_WINDU_SOURCE)
        #define ACCESIO_OS_WINDU
    #endif
    // z/OS
    #if defined(__MVS__) || defined(__HOS_MVS__) || defined(__TOS_MVS__)
        #define ACCESIO_OS_ZOS
    #endif
#endif // ACCESIO_OS_IGNORE

#endif // ACCESIO_OS_H
