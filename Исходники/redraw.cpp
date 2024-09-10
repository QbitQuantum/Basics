void MCControl::layer_setrect(const MCRectangle& p_new_rect, bool p_redraw_all)
{
	if (!opened)
	{
		setrect(p_new_rect);
		return;
	}
	
	// Check the visibility state of the object.
	bool t_is_visible;
	t_is_visible = isvisible() || MCshowinvisibles;
	
	// If we are not a sprite, and are invisible there is nothing to do; otherwise
	// we must at least try to dump cached updated parts of the sprite.
	if (!layer_issprite() && !t_is_visible)
	{
		setrect(p_new_rect);
		return;
	}

	MCRectangle t_old_effectiverect;
	t_old_effectiverect = geteffectiverect();

	// If the rect has changed size and we aren't a scrolling layer, then we
	// redraw all.
	if (!layer_isscrolling() && 
		(rect . width != p_new_rect . width || rect . height != p_new_rect . height))
		p_redraw_all = true;
		
	setrect(p_new_rect);

	layer_changeeffectiverect(t_old_effectiverect, p_redraw_all, t_is_visible);
}