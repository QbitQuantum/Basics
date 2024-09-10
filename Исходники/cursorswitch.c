void
cursorswitch(Cursor *c)
{
	if(c == 0)
		c = &arrow;
	if(c->id == 0){
		if(bsrc == 0){
			bsrc = balloc(crect, 0);
			bmask = balloc(crect, 0);
		}
		/*
		 * Cursor should have fg where "set" is 1,
		 * and bg where "clr" is 1 and "set" is 0,
		 * and should leave places alone where "set" and "clr" are both 0
		 */
		wrbitmap(bsrc, 0, 16, c->set);
#ifdef CURSORBUG
		/*
		 * Some X servers (e.g., Sun X-on-news for some color
		 * monitors) don't do XCreatePixmapCursor properly:
		 * only the mask gets displayed, all black
		 */
		wrbitmap(bmask, 0, 16, c->set);
#else
		wrbitmap(bmask, 0, 16, c->clr);
		bitblt(bmask, Pt(0,0), bsrc, crect, S|D);
#endif
		c->id = (int) XCreatePixmapCursor(_dpy, (Pixmap)bsrc->id, (Pixmap)bmask->id,
			&_fgcolor, &_bgcolor, -c->offset.x, -c->offset.y);
	}
	XDefineCursor(_dpy, (Window)screen.id, (xCursor)c->id);
}