/**
 * Mirrors an image either horizontally, vertically, or both.
 */
void mirror(int directions, struct IMAGE* image) {
    int x;
    int y;

    const bool horizontal = !!((directions & 1<<HORIZONTAL) != 0);
    const bool vertical = !!((directions & 1<<VERTICAL) != 0);
    int untilX = ((horizontal==true)&&(vertical==false)) ? ((image->width - 1) >> 1) : (image->width - 1);  // w>>1 == (int)(w-0.5)/2
    int untilY = (vertical==true) ? ((image->height - 1) >> 1) : image->height - 1;

    for (y = 0; y <= untilY; y++) {
        const int yy = (vertical==true) ? (image->height - y - 1) : y;
        if ((vertical==true) && (horizontal==true) && (y == yy)) { // last middle line in odd-lined image mirrored both h and v
            untilX = ((image->width - 1) >> 1);
        }
        for (x = 0; x <= untilX; x++) {
            const int xx = (horizontal==true) ? (image->width - x - 1) : x;
            const int pixel1 = getPixel(x, y, image);
            const int pixel2 = getPixel(xx, yy, image);
            setPixel(pixel2, x, y, image);
            setPixel(pixel1, xx, yy, image);
        }
    }