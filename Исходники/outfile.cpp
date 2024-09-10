void TERMWINDOWMEMBER dputWord(const uchar *st, FILE *file)
	{
	register const uchar *s;
	register int newColumn;

	if (!OC.Formatting)
		{
		for (; *st; st++)
			{
			doChar(*st, file);
			}

		return;
		}

	if (prevChar == '\n' && ISBLANK(*st))
		{
		ddoCR(file);
		}

	for (newColumn = OC.CrtColumn, s = st; *s; s++)
		{
		if (*s == '\b')
			{
			newColumn--;
			}
		else if (*s == BELL)
			{
			// beeps do nothing to column
			}
		else if (*s != TAB)
			{
			++newColumn;
			}
		else
			{
			while (newColumn++ % 8);
			}
		}

	if (!(newColumn > CurrentUser->GetWidth()))
		{
		if (isspace(*st) && (((newColumn + medium_kludge) >
				CurrentUser->GetWidth()) || !medium_kludge))
			{
			OC.CrtColumn += medium_kludge;
			prevChar = *st;
			return;
			}
		}

	if (newColumn > CurrentUser->GetWidth())
		{
		ddoCR(file);

		if (isspace(*st))
			{
			return;
			}
		}

	for (; *st; st++)
		{
		if (OC.CrtColumn >= CurrentUser->GetWidth())
			{
			ddoCR(file);
			}
		doChar(*st, file);
		}
	}