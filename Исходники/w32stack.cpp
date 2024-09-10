void MCStack::sethints()
{
	if (!opened || MCnoui || window == DNULL)
		return;
	if (flags & F_RESIZABLE)
	{
		rect.width = MCU_max(minwidth, rect.width);
		rect.width = MCU_min(maxwidth, rect.width);
		rect.height = MCU_max(minheight, rect.height);
		rect.height = MCU_min(maxheight, rect.height);
	}
	MCStack *sptr = MCdefaultstackptr == this ? MCtopstackptr : MCdefaultstackptr;
	if (sptr != NULL && sptr != this && sptr->getw() != DNULL
	        && GetWindowLongA((HWND)window->handle.window, 0) == 0)
		SetWindowLongA((HWND)window->handle.window, 0, (LONG)sptr->getw()->handle.window);
}