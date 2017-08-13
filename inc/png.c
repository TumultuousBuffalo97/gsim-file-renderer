#include <stdlib.h>
#include <stdint.h>
#include <png.h>
void writeRGBpixel(struct RGBpixel *pixel, char r, char g, char b) {
	pixel->red=r;
	pixel->green=g;
	pixel->blue=b;
}
void setRGBpixel(png_byte *pixel, struct RGBpixel *colors) {
	pixel[0]=colors->red;
	pixel[1]=colors->green;
	pixel[2]=colors->blue;
}
int writePNGimage(char *path, char *title, struct RGBpixel *pixels, int width, int height) {
	int code=0;
	FILE *fp=fopen(path,"wb");
	png_structp pngptr=png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
	png_infop infoptr = png_create_info_struct(pngptr);
	png_init_io(pngptr, fp);
	png_set_IHDR(pngptr, infoptr, width, height, 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	if (title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = title;
		png_set_text(pngptr, infoptr, &title_text, 1);
	}
	png_write_info(pngptr, infoptr);
	png_bytep row = (png_bytep) malloc(3 * width * sizeof(png_byte));
	int x,y;
	for(y=0;y<height;++y) {
		for(x=0;x<width;++x) {
			setRGBpixel(&(row[x*3]), &pixels[y*width + x]);
		}
		png_write_row(pngptr, row);
	}
	png_write_end(pngptr, NULL);
	if (fp != NULL) fclose(fp);
	if (infoptr != NULL) png_free_data(pngptr, infoptr, PNG_FREE_ALL, -1);
	if (pngptr != NULL) png_destroy_write_struct(&pngptr, (png_infopp)NULL);
	if (row != NULL) free(row);
	return code;
}
