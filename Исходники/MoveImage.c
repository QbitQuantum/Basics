Global void
MoveImage(XImage      *image,
	  XImage      *new_image,
	  unsigned int width,
	  unsigned int height,
	  ColormapPtr  cmap,
	  Direction    dir)
{
	int x, y;
     
	if (cmap == NULL || (image->depth == 1 && new_image->depth == 1)) {
		CopyImage(image, new_image, width, height);
		return;
	}
     
	for (x=0; x < width; x++)
		for (y=0; y < height; y++)
			XPutPixel(new_image, x, y,
				  MapColorCell(XGetPixel(image, x, y), cmap, dir));
}