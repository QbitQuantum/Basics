void PatchCoD4_Console()
{
	memset((void*)0x4FCB73, 0x90, 9); // disable null check

	hCreateWindow.initialize(SYS_CREATEWINDOW_HOOK, Sys_CreateConsole);
	hCreateWindow.installHook();

	hDestroyWindow.initialize(SYS_DESTROYWINDOW_HOOK, Sys_DestroyConsole);
	hDestroyWindow.installHook();

	hSysPrint.initialize(SYS_PRINT_HOOK, Sys_Print);
	hSysPrint.installHook();
}