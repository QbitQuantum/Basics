int
clientwin_validate_func(dlist *l, void *data) {
	ClientWin *cw = l->data;
	MainWin *mw = cw->mainwin;

	CARD32 desktop = (*(CARD32*)data),
		w_desktop = wm_get_window_desktop(mw->ps, cw->wid_client);
	
#ifdef CFG_XINERAMA
	if(mw->xin_active && ! INTERSECTS(cw->src.x, cw->src.y, cw->src.width, cw->src.height,
	                                           mw->xin_active->x_org, mw->xin_active->y_org,
	                                           mw->xin_active->width, mw->xin_active->height))
		return 0;
#endif
	
	return (w_desktop == (CARD32)-1 || desktop == w_desktop) &&
	       wm_validate_window(mw->ps, cw->wid_client);
}