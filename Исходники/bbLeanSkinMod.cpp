void setTTC(int f)
{
	const int NCOLORS = 2;
	static int C_ID[NCOLORS] =
	{
		// tooltips bk + txt
		COLOR_INFOBK,
		COLOR_INFOTEXT
	};
	static COLORREF C_SAVE[NCOLORS];
	static bool changed;

	if (SAVE_3DC == f)
	{
		int n = 0;
		do C_SAVE[n] = GetSysColor(C_ID[n]);
		while (++n<NCOLORS);
		changed = false;
		return;
	}

	if (RESTORE_3DC == f || false == setTTColor)
	{
		if (changed)
		{
			SetSysColors(NCOLORS, C_ID, C_SAVE);
			changed = false;
		}
		return;
	}

	if (APPLY_3DC == f)
	{
		COLORREF C_CR[NCOLORS];
		GradientItem *S1, *S2;
		S1 = S2 = &mSkin.windowLabelFocus;

		if (S1->parentRelative)
			S1 = &mSkin.windowTitleFocus;

		if (B_SOLID == S1->type)
			C_CR[0] = S1->Color;
		else
			C_CR[0] = mixcolors(S1->Color, S1->ColorTo);

		C_CR[1] = S2->TextColor;

		SetSysColors(NCOLORS, C_ID, C_CR);
		changed = true;
	}
}