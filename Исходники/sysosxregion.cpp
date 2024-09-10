bool MCRegionCalculateMask(MCRegionRef self, int32_t w, int32_t h, MCBitmap*& r_mask)
{
	// Create a pixmap
	Pixmap t_image;
	t_image = MCscreen -> createpixmap(w, h, 1, False);
	
	// Draw into the pixmap's port
	CGrafPtr t_old_port;
	GDHandle t_old_device;
	GetGWorld(&t_old_port, &t_old_device);
	SetGWorld((CGrafPtr)t_image -> handle . pixmap, NULL);
	
	BackColor(whiteColor);
	ForeColor(blackColor);
	
	Rect t_rect;
	SetRect(&t_rect, 0, 0, w, h);
	EraseRect(&t_rect);
	
	PaintRgn((RgnHandle)self);
	
	SetGWorld(t_old_port, t_old_device);
	
	// Fetch the pixmap as a bitmap
	MCBitmap *t_bitmap;
	t_bitmap = MCscreen -> getimage(t_image, 0, 0, w, h, False);
	
	// Discard the pixmap
	MCscreen -> freepixmap(t_image);
	
	r_mask = t_bitmap;
	
	return true;
}