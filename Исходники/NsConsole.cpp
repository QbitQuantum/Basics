void NsConsole::Show()
{
	AllocConsole();
	AttachConsole(GetCurrentProcessId());
	freopen("CON", "w", stdout);
	SetConsoleTitle(L"There Is No Spoon Console");
	_bShowing = true;

	for(int i = 0; i < _messages.Size(); ++i)
	{
		printf("%s\n", _messages[i].c_str());
	}
}