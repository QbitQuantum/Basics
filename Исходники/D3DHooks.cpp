void D3DHooks::DelayedUnload()
{
	Logger::GetInstance()->LogEvent("Event", "Delay unloading the dll...detach event should come next in 500ms");

	// Unload this dll fully from the process
	// Give enough time for the hooked function to complete and return
	Sleep(500);
	FreeLibraryAndExitThread(GlobalHook::GetInstance()->GetHInstance(), 0);
}