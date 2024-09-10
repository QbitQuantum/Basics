void iexSystem::OpenDebugWindow()
{
#ifdef _DEBUG
	AllocConsole();
	freopen_s( &DebugFP, "CON", "w", stdout);
#endif
}