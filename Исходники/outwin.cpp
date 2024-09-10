Bool TERMWINDOWMEMBER WinStatCon(void)
	{
	if (TermWindowCollection.InFocus(this))
		{
		DWORD Number;

		if (GetNumberOfConsoleInputEvents(hConsoleInput, &Number))
			{
			return (!!Number);
			}
		}

	return (FALSE);
	}