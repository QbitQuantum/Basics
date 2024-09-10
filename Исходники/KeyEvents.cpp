bool IsFullscreen()
{
	bool Result=false;
	DWORD ModeFlags=0;
	if(GetConsoleDisplayMode(&ModeFlags) && ModeFlags&CONSOLE_FULLSCREEN_HARDWARE)
	{
		Result=true;
	}
	return Result;
}