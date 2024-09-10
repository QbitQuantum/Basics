void slide_stamps(void)
{
	int i;
	bitmap *b = thePort->portBMap;

	if (stamp_err)
	{
		stamp_err = 0;
		return;
	}

	HideCursor();
	for (i = 2; i > 0; i--)
	{
		CopyBits(b, b, &stampingR[i - 1], &stampingR[i], &stampingR[i], zREPz);
		PenColor(WHITE);
		FrameRect(&stampingR[i]);
	}

	CopyBits(b, b, &stampR, &stampingR[0], &stampingR[0], zREPz);
	FrameRect(&stampingR[0]);
	ShowCursor();
}