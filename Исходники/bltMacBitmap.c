/*
 *---------------------------------------------------------------------------
 *
 * Blt_RotateBitmap --
 *
 *	Creates a new bitmap containing the rotated image of the given
 *	bitmap.  We also need a special GC of depth 1, so that we do
 *	not need to rotate more than one plane of the bitmap.
 *
 * Results:
 *	Returns a new bitmap containing the rotated image.
 *
 *---------------------------------------------------------------------------
 */
Pixmap
Blt_RotateBitmap(
    Tk_Window tkwin,
    Pixmap srcBitmap,		/* Source bitmap to be rotated */
    int srcWidth, int srcHeight, /* Width and height of the source bitmap */
    float angle,		/* # of degrees to rotate the bitmap. */
    int *destWidthPtr, 
    int *destHeightPtr)
{
    Display *display;		/* X display */
    GC bitmapGC;
    Pixmap destBitmap;
    Window root;		/* Root window drawable */
    XImage *srcImgPtr, *destImgPtr;
    double rotWidth, rotHeight;
    int destWidth, destHeight;

    display = Tk_Display(tkwin);
    root = Tk_RootWindow(tkwin);

#ifdef notdef
    /* Create a bitmap and image big enough to contain the rotated text */
    Blt_GetBoundingBox(srcWidth, srcHeight, angle, &rotWidth, &rotHeight,
	(Point2d *)NULL);
    destWidth = ROUND(rotWidth);
    destHeight = ROUND(rotHeight);
    destBitmap = Tk_GetPixmap(display, root, destWidth, destHeight, 1);
    bitmapGC = Blt_GetBitmapGC(tkwin);
    XSetForeground(display, bitmapGC, 0x0);
    XFillRectangle(display, destBitmap, bitmapGC, 0, 0, destWidth, destHeight);

    srcImgPtr = XGetImage(display, srcBitmap, 0, 0, srcWidth, srcHeight, 1, 
	ZPixmap);
    destImgPtr = XGetImage(display, destBitmap, 0, 0, destWidth, destHeight, 
	1, ZPixmap);
    angle = FMOD(angle, 360.0);
    if (FMOD(angle, 90.0) == 0.0) {
	int quadrant;
	int y;

	/* Handle right-angle rotations specifically */

	quadrant = (int)(angle / 90.0);
	switch (quadrant) {
	case ROTATE_270:	/* 270 degrees */
	    for (y = 0; y < destHeight; y++) {
		int x, sx;

		sx = y;
		for (x = 0; x < destWidth; x++) {
		    int sy;
		    unsigned long pixel;
		    
		    sy = destWidth - x - 1;
		    pixel = XGetPixel(srcImgPtr, sx, sy);
		    if (pixel) {
			XPutPixel(destImgPtr, x, y, pixel);
		    }
		}
	    }
	    break;

	case ROTATE_180:	/* 180 degrees */
	    for (y = 0; y < destHeight; y++) {
		int x, sy;

		sy = destHeight - y - 1;
		for (x = 0; x < destWidth; x++) {
		    int sx;
		    unsigned long pixel;

		    sx = destWidth - x - 1, 
		    pixel = XGetPixel(srcImgPtr, sx, sy);
		    if (pixel) {
			XPutPixel(destImgPtr, x, y, pixel);
		    }
		}
	    }
	    break;

	case ROTATE_90:		/* 90 degrees */
	    for (y = 0; y < destHeight; y++) {
		int x, sx;

		sx = destHeight - y - 1;
		for (x = 0; x < destWidth; x++) {
		    int sy;
		    unsigned long pixel;

		    sy = x;
		    pixel = XGetPixel(srcImgPtr, sx, sy);
		    if (pixel) {
			XPutPixel(destImgPtr, x, y, pixel);
		    }
		}
	    }
	    break;

	case ROTATE_0:		/* 0 degrees */
	    for (y = 0; y < destHeight; y++) {
		int x;

		for (x = 0; x < destWidth; x++) {
		    unsigned long pixel;

		    pixel = XGetPixel(srcImgPtr, x, y);
		    if (pixel) {
			XPutPixel(destImgPtr, x, y, pixel);
		    }
		}
	    }
	    break;

	default:
	    /* The calling routine should never let this happen. */
	    break;
	}
    } else {
	double radians, sinTheta, cosTheta;
	double sox, soy;	/* Offset from the center of
				 * the source rectangle. */
	double destCX, destCY;	/* Offset to the center of the destination
				 * rectangle. */
	int y;

	radians = (angle / 180.0) * M_PI;
	sinTheta = sin(radians), cosTheta = cos(radians);

	/*
	 * Coordinates of the centers of the source and destination rectangles
	 */
	sox = srcWidth * 0.5;
	soy = srcHeight * 0.5;
	destCX = destWidth * 0.5;
	destCY = destHeight * 0.5;

	/* For each pixel of the destination image, transform back to the
	 * associated pixel in the source image. */

	for (y = 0; y < destHeight; y++) {
	    double ty;
	    int x;

	    ty = y - destCY;
	    for (x = 0; x < destWidth; x++) {
		double tx, rx, ry, sx, sy;
		unsigned long pixel;

		/* Translate origin to center of destination image. */
		tx = x - destCX;

		/* Rotate the coordinates about the origin. */
		rx = (tx * cosTheta) - (ty * sinTheta);
		ry = (tx * sinTheta) + (ty * cosTheta);

		/* Translate back to the center of the source image. */
		rx += sox;
		ry += soy;

		sx = ROUND(rx);
		sy = ROUND(ry);

		/*
		 * Verify the coordinates, since the destination image can be
		 * bigger than the source.
		 */

		if ((sx >= srcWidth) || (sx < 0) || (sy >= srcHeight) ||
		    (sy < 0)) {
		    continue;
		}
		pixel = XGetPixel(srcImgPtr, sx, sy);
		if (pixel) {
		    XPutPixel(destImgPtr, x, y, pixel);
		}
	    }
	}
    }
    /* Write the rotated image into the destination bitmap. */
    XPutImage(display, destBitmap, bitmapGC, destImgPtr, 0, 0, 0, 0, 
	destWidth, destHeight);

    /* Clean up the temporary resources used. */
    XDestroyImage(srcImgPtr), XDestroyImage(destImgPtr);
    *destWidthPtr = destWidth;
    *destHeightPtr = destHeight;
#endif
    return destBitmap;
}