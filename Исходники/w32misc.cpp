void MCStacklist::hidepalettes(Boolean hide)
{
	active = !hide;
	if (stacks == NULL)
		return;
	MCStacknode *tptr = stacks;
	// only hide palettes if a non-palette is open
	Boolean dohide = False;
	do
	{
		MCStack *sptr = tptr->getstack();
		if (sptr->getrealmode() < WM_PALETTE)
		{
			dohide = True;
			break;
		}
		tptr = tptr->next();
	}
	while (tptr != stacks);
	if (!dohide)
		return;

	restart = False;
	tptr = stacks;
	do
	{
		MCStack *sptr = tptr->getstack();
		if (sptr->getrealmode() == WM_PALETTE && sptr->getflag(F_VISIBLE))
			if (MChidepalettes)
			{
				// Show the window non-active (to avoid messing with the focus),
				// then send a synthetic activate event to force a title-bar redraw
				ShowWindow((HWND)sptr->getw()->handle.window, hide ? SW_HIDE : SW_SHOWNA);
				PostMessageA((HWND)sptr->getw()->handle.window, WM_NCACTIVATE, 1, 0);
				// When closing or opening a window, Win32 delivers messages that can
				// change stack list, and we need to start over if this happened
				if (restart)
				{
					hidepalettes(hide);
					return;
				}

			}
			else if (sptr->getw() != NULL)
			{
				// OK-2007-04-19: Bug 4728, When hiding a palette with a windowShape
				// sptr->getw() can return null, causing crash here.
				PostMessageA((HWND)sptr->getw()->handle.window, WM_NCACTIVATE, !hide, 0);
			}
				
		tptr = tptr->next();
	}
	while (tptr != stacks);
}