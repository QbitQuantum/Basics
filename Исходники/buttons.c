static void draw_image_button(button obj, rect r)
{
	image   img;
	bitmap	store = NULL;
	rect    ir;
	rgb     up, down;
	rgb     old = currentcolour();

	img = obj->img;
	if (has_transparent_pixels(img)) {
		store = newbitmap(r.width, r.height, 0);
		drawto(store);
		setcolour(getbackground(obj));
		fillrect(r);
	}

	if (img) {
		ir = insetr(r,2);
		if (ishighlighted(obj)) /* button is pressed */
			ir.x += 1, ir.y += 1;

		/* Draw the button image. */
		if (ischecked(obj))
			drawdarker(img, ir, getrect(img));
		else if (isenabled(obj))
			drawimage(img, ir, getrect(img));
		else
			drawgreyscale(img, ir, getrect(img));

		if (ishighlighted(obj)) { /* fill the gap */
			ir.x -= 1, ir.y -= 1;
			setcolour(getbackground(obj));
			drawline(topleft(ir),topright(ir));
			drawline(topleft(ir),bottomleft(ir));
		}
	}

	/* Draw button border. */
	setcolour(getforeground(obj));
	setlinewidth(1);
	drawrect(r);

	/* Draw button shadow. */
	up = White, down = Grey;
	if (ishighlighted(obj))
		up = Grey, down = LightGrey;
	draw_shadow(insetr(r,1), up, down, 1);

	if (store != NULL) {
		drawto(obj);
		copyrect(store, pt(0,0), getrect(store));
		del(store);
	}

	setcolour(old);
}