DWORD __stdcall ThreadEntry(LPVOID) {
	Log::Log("Initializing API\n");
	if (!GW::Initialize()){
		MessageBoxA(0, "Initialize Failed at finding all addresses, contact Developers about this.", "GWToolbox++ API Error", 0);
		FreeLibraryAndExitThread(dllmodule, EXIT_SUCCESS);
		return EXIT_SUCCESS;
	}

	Log::Log("Installing dx hooks\n");
	GW::Render::SetRenderCallback([](IDirect3DDevice9* device) {
		GWToolbox::Instance().Draw(device);
	});
	GW::Render::SetResetCallback([](IDirect3DDevice9* device) {
		ImGui_ImplDX9_InvalidateDeviceObjects();
	});

	Log::Log("Installed dx hooks\n");

	Log::InitializeChat();

	Log::Log("Installed chat hooks\n");

	while (!tb_destroyed) { // wait until destruction
		Sleep(100);

#ifdef _DEBUG
		if (GetAsyncKeyState(VK_END) & 1) {
			GWToolbox::Instance().StartSelfDestruct();
			break;
		}
#endif
	}
	
	Sleep(100);

	Sleep(100);
	Log::Log("Closing log/console, bye!\n");
	Log::Terminate();
	Sleep(100);
	FreeLibraryAndExitThread(dllmodule, EXIT_SUCCESS);
}