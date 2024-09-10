void SKSE64_Initialize(void)
{
	if(isInit) return;
	isInit = true;

	gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Skyrim Special Edition\\SKSE\\skse64.log");

#ifndef _DEBUG
	__try {
#endif

		FILETIME	now;
		GetSystemTimeAsFileTime(&now);

		_MESSAGE("SKSE64 runtime: initialize (version = %d.%d.%d %08X %08X%08X, os = %s)",
			SKSE_VERSION_INTEGER, SKSE_VERSION_INTEGER_MINOR, SKSE_VERSION_INTEGER_BETA, RUNTIME_VERSION,
			now.dwHighDateTime, now.dwLowDateTime, GetOSInfoStr().c_str());

		_MESSAGE("imagebase = %016I64X", GetModuleHandle(NULL));
		_MESSAGE("reloc mgr imagebase = %016I64X", RelocationManager::s_baseAddr);

#ifdef _DEBUG
		SetPriorityClass(GetCurrentProcess(), IDLE_PRIORITY_CLASS);

		WaitForDebugger();
#endif

		if(!g_branchTrampoline.Create(1024 * 64))
		{
			_ERROR("couldn't create branch trampoline. this is fatal. skipping remainder of init process.");
			return;
		}

		if(!g_localTrampoline.Create(1024 * 64, g_moduleHandle))
		{
			_ERROR("couldn't create codegen buffer. this is fatal. skipping remainder of init process.");
			return;
		}

		// Add Hooks_XXX_Init calls here
		Hooks_Debug_Init();
		Hooks_ObScript_Init();
		Hooks_Papyrus_Init();
		Hooks_NetImmerse_Init();
		Hooks_Threads_Init();
		Hooks_Handlers_Init();

		g_pluginManager.Init();

		// Add Hooks_XXX_Commit calls here in the same order
		Hooks_Debug_Commit();
		Hooks_ObScript_Commit();
		Hooks_Papyrus_Commit();
		Hooks_UI_Commit();
		Hooks_Camera_Commit();
		Hooks_NetImmerse_Commit();
		Hooks_Threads_Commit();
		Hooks_Handlers_Commit();
		Hooks_Scaleform_Commit();
		Hooks_Gameplay_Commit();
		Hooks_Event_Commit();
		Hooks_SaveLoad_Commit();
		Hooks_Data_Commit();
		Init_CoreSerialization_Callbacks();
		Hooks_DirectInput_Commit();
		
		FlushInstructionCache(GetCurrentProcess(), NULL, 0);

#ifndef _DEBUG
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		_ERROR("exception thrown during startup");
	}
#endif

	_MESSAGE("init complete");
}