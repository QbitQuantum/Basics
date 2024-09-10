void
TkMacSetUpClippingRgn(
    Drawable drawable)		/* Drawable to update. */
{
    MacDrawable *macDraw = (MacDrawable *) drawable;

    if (macDraw->winPtr != NULL) {
	if (macDraw->flags & TK_CLIP_INVALID) {
	    TkMacUpdateClipRgn(macDraw->winPtr);
	}

	/*
	 * When a menu is up, the Mac does not expect drawing to occur and
	 * does not clip out the menu. We have to do it ourselves. This
	 * is pretty gross.
	 */

	if (macDraw->clipRgn != NULL) {
	    if (tkUseMenuCascadeRgn == 1) {
	    	Point scratch = {0, 0};
	    	GDHandle saveDevice;
	    	GWorldPtr saveWorld;
	    	
	    	GetGWorld(&saveWorld, &saveDevice);
	    	SetGWorld(TkMacGetDrawablePort(drawable), NULL);
	    	LocalToGlobal(&scratch);
	    	SetGWorld(saveWorld, saveDevice);
	    	if (tmpRgn == NULL) {
	    	    tmpRgn = NewRgn();
	    	}
	    	CopyRgn(tkMenuCascadeRgn, tmpRgn);
	    	OffsetRgn(tmpRgn, -scratch.h, -scratch.v);
	    	DiffRgn(macDraw->clipRgn, tmpRgn, tmpRgn);
	    	SetClip(tmpRgn);
	    	macDraw->toplevel->flags |= TK_DRAWN_UNDER_MENU;
	    } else {
	    	SetClip(macDraw->clipRgn);
	    }
	}
    }
}