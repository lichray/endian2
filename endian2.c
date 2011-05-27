#include "endian2.h"

static __inline int
__endian2(const char *__restrict fmt, void *p)
{
	const char *i;
	for (i = fmt; *i != '\0'; i++) {
#define fmtInt(x, T) \
	case x: { \
		__uint##T##_t *n = p; \
		*n = bswap##T(*n); \
		p += sizeof(__uint##T##_t); \
		break; \
	}
#define fmtSkip(x, n) \
	case x: { \
		p += n; \
		break; \
	}
		switch (*i) {
			fmtInt('h', 16);
			fmtInt('l', 32);
			fmtInt('q', 64);
			fmtSkip('.', 1);
		default : return -1;
		}
#undef fmtInt
#undef fmtSkip
	}
	return i - fmt;
}

/*
 * Reference:
 * http://stackoverflow.com/questions/1001307/detecting-endianness-programmatically-in-a-c-program
 */
static __inline int
is_big_endian(void)
{
	union {
		uint32_t i;
		char c[4];
	} bint = {0x01020304};
	return bint.c[0] == 1;
}

/*
 * converts any endianness to host
 * returns -1 when the format is wrong,
 *          0 when no conversion is needed,
 *          positive value == len(fmt) - 1 (w/o the leading '>'/'<').
 *
 * h2endian() is identical to this, except that
 * it's interpreted as "converts host endianness to any"
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
 * reverses any endianness
 * returns -1 when the format is wrong,
 *		  other value == len(fmt).
 */
int
r_endian(const char *__restrict fmt, void *p)
{
	return __endian2(fmt, p);
}

