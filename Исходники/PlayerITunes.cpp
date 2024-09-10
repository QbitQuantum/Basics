/*
** Destructor.
**
*/
PlayerITunes::~PlayerITunes()
{
	c_Player = nullptr;

	DestroyWindow(m_CallbackWindow);
	UnregisterClass(L"NowPlayingITunesClass", g_Instance);

	Uninitialize();
}