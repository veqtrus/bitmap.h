#include <stdio.h>

#include "bitmap.h"

int main()
{
	FILE *file;
	int i, j, iter;
	double x0, y0, x, y, t;
	char buf[BITMAP_SIZE(350, 200)];
	bitmap_init(buf, 350, 200);
	for (j = 0; j < 200; ++j) {
		for (i = 0; i < 350; ++i) {
			x0 = (i - 250) / 100.0;
			y0 = (j - 100) / 100.0;
			x = 0.0;
			y = 0.0;
			for (iter = 0; x * x + y * y <= 4.0 && iter < 128; ++iter) {
				t = x * x - y * y + x0;
				y = 2.0 * x * y + y0;
				x = t;
			}
			if (iter < 128) {
				bitmap_set(buf, i, j, iter * 2, iter * 2, 64 + iter);
			} else {
				bitmap_set(buf, i, j, 0, 0, 0);
			}
		}
	}
	file = fopen("mandelbrot.bmp", "wb");
	if (!file) return 1;
	fwrite(buf, sizeof(buf), 1, file);
	return fclose(file);
}
