/*
Copyright (c) 2021 Pavlos Georgiou

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef BITMAP_H
#define BITMAP_H

#if defined(__cplusplus) || __STDC_VERSION__ >= 199901L
#define BITMAP_INLINE static inline
#else
#define BITMAP_INLINE static
#endif

#define BITMAP_SIZE(w, h) (((3L * (w) + 3L) & -4UL) * (h) + 54L)

BITMAP_INLINE void bitmap_init(void *buf, long width, long height)
{
	unsigned char *p;
	unsigned long n;
	long size;
	size = BITMAP_SIZE(width, height);
	p = (unsigned char *) buf;
	/* signature (BM) */
	*p++ = 66;
	*p++ = 77;
	/* file size */
	n = size;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	/* reserved */
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	/* offset to pixel array */
	*p++ = 54;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	/* DIB header size */
	*p++ = 40;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	/* image width */
	n = width;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	/* image height */
	n = height;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	/* planes */
	*p++ = 1;
	*p++ = 0;
	/* bits per pixel */
	*p++ = 24;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	/* compression */
	*p++ = 0;
	*p++ = 0;
	/* image size */
	n = size - 54;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	n >>= 8;
	*p++ = n;
	/* x pixels per meter */
	*p++ = 19;
	*p++ = 11;
	/* y pixels per meter */
	*p++ = 19;
	*p++ = 11;
	/* palette colors */
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	/* important colors */
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
	*p++ = 0;
}

BITMAP_INLINE void bitmap_set(void *buf, long x, long y, int r, int g, int b)
{
	unsigned char *p;
	unsigned long line_size;
	p = (unsigned char *) buf;
	line_size = p[21];
	line_size <<= 8;
	line_size |= p[20];
	line_size <<= 8;
	line_size |= p[19];
	line_size <<= 8;
	line_size |= p[18];
	line_size = (line_size * 3 + 3) & -4UL;
	p += line_size * y + x * 3 + 54;
	p[0] = b;
	p[1] = g;
	p[2] = r;
}

#endif
