int WACIrctell::ccb_notify(int msg, int param1, int param2)
{
	if (msg==TITLECHANGE && dotell)
	{
		const wchar_t *title = (const wchar_t *)param1;
		const wchar_t *cur=core->core_getCurrent(0);

		wchar_t msg[256];
		StringCchPrintfW(msg, 256, L"/describe #winamp is now listening to \"%s\"", title);
		DdeCom::sendCommand(L"mIRC", msg, 1000);
	}
	return 0;
}