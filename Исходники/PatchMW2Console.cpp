// patch entry point
void PatchMW2_Console()
{
	createConsoleHook.initialize(5, (PBYTE)HOOK_Sys_CreateConsole);
	createConsoleHook.installHook(Sys_CreateConsole, true, false);

	destroyConsoleHook.initialize(5, (PBYTE)HOOK_Sys_DestroyConsole);
	destroyConsoleHook.installHook(Sys_DestroyConsole, true, false);

	// TODO: get rid of weird casts
	sysPrintHook.initialize(5, (PBYTE)HOOK_Sys_Print);
	sysPrintHook.installHook((void (__cdecl *)(void))Sys_Print, true, false);

	sysErrorHook.initialize(5, (PBYTE)HOOK_Sys_Error);
	sysErrorHook.installHook((void (__cdecl *)(void))Sys_Error, true, false);

	consoleInputHook.initialize((PBYTE)HOOK_Sys_ConsoleInput);
	consoleInputHook.installHook((void (__cdecl *)(void))Sys_ConsoleInput, false);

	//PatchMW2_DebugAllocations();
}