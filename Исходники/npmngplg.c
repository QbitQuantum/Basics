static void find_window_size(PluginInstance *This)
{
	RECT r;
	if(This->scrolling) {  // make sure scrollbars exist if needed
		ShowScrollBar(This->fhWnd,SB_BOTH,TRUE);
	}
	GetClientRect(This->fhWnd, &r);
	This->windowwidth=r.right;
	This->windowheight=r.bottom;
}