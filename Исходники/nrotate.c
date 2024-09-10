static void
reverse(Image *img, Image *tmp, int axis)
{
	Image *mask;
	Rectangle r;
	int i, d;

	/*
	 * We start by swapping large chunks at a time.
	 * The chunk size should be the largest power of
	 * two that fits in the dimension.
	 */
	d = axis==Xaxis ? Dx(img) : Dy(img);
	for(i = 1; i*2 <= d; i *= 2)
		;

	r = axis==Xaxis ? Rect(0,0, i,100) : Rect(0,0, 100,i);
	mask = xallocimage(display, r, GREY1, 1, DTransparent);
	mtmp = xallocimage(display, r, GREY1, 1, DTransparent);

	/*
	 * Now color the bottom (or left) half of the mask opaque.
	 */
	if(axis==Xaxis)
		r.max.x /= 2;
	else
		r.max.y /= 2;

	draw(mask, r, display->opaque, nil, ZP);
	writefile("mask", mask, i);

	/*
	 * Shuffle will recur, shuffling the pieces as necessary
	 * and making the mask a finer and finer grating.
	 */
	shuffle(img, tmp, axis, d, mask, i, 0);

	freeimage(mask);
}