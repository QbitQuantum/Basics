int _winstart(void)
{
	char *szCmd; STARTUPINFO startinfo;

	__set_app_type(__GUI_APP);
	_controlfp(0x10000, 0x30000);

	szCmd = GetCommandLine();
	if (szCmd)
	{
		while (' ' == *szCmd) szCmd++;
		if ('\"' == *szCmd)
		{
			while (*++szCmd)
				if ('\"' == *szCmd) { szCmd++; break; }
		}
		else
		{
			while (*szCmd && ' ' != *szCmd) szCmd++;
		}
		while (' ' == *szCmd) szCmd++;
	}

	GetStartupInfo(&startinfo);
	exit(WinMain(GetModuleHandle(NULL), NULL, szCmd,
		(startinfo.dwFlags & STARTF_USESHOWWINDOW) ?
			startinfo.wShowWindow : SW_SHOWDEFAULT));
}