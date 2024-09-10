/*******************************************************************
   KF 6/14/90
   write_pixmap_file(display, filename, pm, width, height)
        and
   write_pixmap_file_xy(display, filename, pm, x, y, width, height)
   has been merged into one function.

   INPUT: display dsp, screen s, file name fn to write the file in,
          window id wid where pixmap is,
          upper left corner x, y of original pixmap,
          width and height of pixmap
   OUTPUT: binary file with data
   PURPOSE: write_pixmap_file gets the image structure of the input
          pixmap, convert the image data with the permutation color
          vector, writes the image structure out to filename.

   Note that writing out a Z pixmap is 8x faster than XY pixmap.
   This is because XY writes out each pixel value per plane, thus
   number of bits; Z writes out each pixel, or 8 bits at a time.

   The XY format may have been chosen for a reason -- I don't know.

********************************************************************/
void
write_pixmap_file(Display *dsp, int scr, char  *fn, 
                  Window wid, int x, int y, int width,int height)
{
    XImage *xi;
    FILE *file;
    int *permVector;
    int num;
    int num_colors;

    /* get color map and permutation vector */
    if ((num_colors = makePermVector(dsp, scr,(unsigned long **)&permVector)) < 0) {
        printf("num_colors < 0!!\n");
        exit(-1);
    }

    /* reads image structure in ZPixmap format */
    xi = XGetImage(dsp, wid, x, y, width, height, AllPlanes, ZPixmap);
    file = fopen(fn, "wb");
    if (file == NULL) {
        perror("opening pixmap file for write");
        exit(-1);
    }

#define PUTW(a,b) putw(htonl(a),b)


    PUTW(xi->width, file);
    PUTW(xi->height, file);
    PUTW(xi->xoffset, file);
    PUTW(xi->format, file);
    PUTW(xi->byte_order, file);
    PUTW(xi->bitmap_unit, file);
    PUTW(xi->bitmap_bit_order, file);
    PUTW(xi->bitmap_pad, file);
    PUTW(xi->depth, file);
    PUTW(xi->bytes_per_line, file);
    PUTW(xi->bits_per_pixel, file);
    PUTW(xi->red_mask, file);
    PUTW(xi->green_mask, file);
    PUTW(xi->blue_mask, file);

    num = xi->bytes_per_line * height;  /* total number of pixels in pixmap */

    /* store value from permutation */
    {
        int ii, jj;

        for (ii = 0; ii < width; ii++)
            for (jj = 0; jj < height; jj++) {
                XPutPixel(xi, ii, jj, permVector[(int) XGetPixel(xi, ii, jj)]);
            }
    }
    fwrite(xi->data, 1, num, file);
    fclose(file);
}