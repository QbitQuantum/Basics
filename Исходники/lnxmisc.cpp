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
				if (hide)
					MCscreen->closewindow(sptr->getw());
				else
					sptr -> openwindow(False);
			}

		tptr = tptr->next();
	}
	while (tptr != stacks);
}