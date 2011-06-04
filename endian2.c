#include "endian2.h"

static __inline int
__endian2(const char *__restrict fmt, void *p)
{
	const char *i;
	for (i = fmt; *i != '\0'; i++) {
#define _swpint(T) { \
		__uint##T##_t *n = p; \
		*n = bswap##T(*n); \
		p += sizeof(__uint##T##_t); \
		break; \
	}
#define _noswp(n) { \
		p += n; \
		break; \
	}
		switch (*i) {
		case 'h':
			_swpint(16);
		case 'l':
		case 'f':
			_swpint(32);
		case 'q':
		case 'd':
			_swpint(64);
		case '.':
		case 'c':
			_noswp(1);
		default : return -1;
		}
#undef _swpint
#undef _noswp
	}
	return i - fmt;
}

/*
 * Reference:
 * http://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program
 */
#ifndef is_big_endian

static __inline int
is_big_endian(void)
{
	union {
		__uint32_t i;
		char c[4];
	} bint = {0x01020304};
	return bint.c[0] == 1;
}

#endif

/*
 * converts any endianness to host
 * returns -1 when the format is wrong,
 *          0 when no conversion is needed,
 *          positive value == len(fmt) - 1 (w/o the leading '>'/'<').
 */
int
endian2h(const char *__restrict fmt, void *p)
{
	if (is_big_endian()) {
		if (fmt[0] == '>') return 0;
		if (fmt[0] != '<') return -1;
	} else {
		if (fmt[0] == '<') return 0;
		if (fmt[0] != '>') return -1;
	}
	return __endian2(fmt + 1, p);
}

/*
 * converts host endianness to any
 * yes, it's identical to endian2h
 */
int
h2endian(const char *__restrict, void *)
	__attribute__((alias("endian2h")));

/*
 * reverses any endianness
 * returns -1 when the format is wrong,
 *		  other value == len(fmt).
 */
int
r_endian(const char *__restrict fmt, void *p)
{
	return __endian2(fmt, p);
}

