#ifndef _ENDIAN2_H
#define _ENDIAN2_H

#include <sys/types.h>

int
endian2h(const char *__restrict __fmt, void *__src);

int
h2endian(const char *__restrict, void *)
	__attribute__((alias("endian2h")));

int
r_endian(const char *__restrict __fmt, void *__src);

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
