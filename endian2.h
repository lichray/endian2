#ifndef _ENDIAN2_H
#define _ENDIAN2_H

#include <sys/types.h>

int
endian2h(const char *__restrict __fmt, void *__src);

int
h2endian(const char *__restrict __fmt, void *__src);

int
r_endian(const char *__restrict __fmt, void *__src);

/* Reference: LLVM compiler-rt/trunk/lib/endianness.h */

#if defined(__SVR4) && defined(__sun)
#include <sys/byteorder.h>
#define is_big_endian() (_BYTE_ORDER == _BIG_ENDIAN)
#endif /* Solaris and AuroraUX. */

#if defined(__FreeBSD__) || defined(__NetBSD__) || \
	defined(__OpenBSD__) || defined(__DragonFly__)
#include <sys/endian.h>
#define is_big_endian() (_BYTE_ORDER == _BIG_ENDIAN)
#endif /* *BSD */

#if defined(__APPLE__) && defined(__MACH__) || defined(__ellcc__ )
#define is_big_endian() (defined(__BIG_ENDIAN__) && __BIG_ENDIAN__)
#endif /* Mac OSX */

#if defined(__linux__)
#include <endian.h>
#define is_big_endian() (__BYTE_ORDER == __BIG_ENDIAN)
#endif /* GNU/Linux */

/* Reference: FreeBSD /usr/include/sys/endian.h */

#ifndef bswap16

#define __bswap64(x) \
__extension__ ({ register __uint64_t __X = (x); \
   __asm ("bswap %0" : "+r" (__X)); \
   __X; })

#define __bswap32(x) \
__extension__ ({ register __uint32_t __X = (x); \
   __asm ("bswap %0" : "+r" (__X)); \
   __X; })

static __inline __uint64_t
bswap64(__uint64_t _x) { return (__bswap64(_x)); }

static __inline __uint32_t
bswap32(__uint32_t _x) { return (__bswap32(_x)); }

static __inline __uint16_t
bswap16(__uint16_t _x) { return (_x << 8 | _x >> 8); }

#endif

#endif
