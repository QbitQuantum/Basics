static void PatchMW2_ClientConsole_Toggle()
{
	clKeyEventToggleConsoleHook1.initialize((PBYTE)clKeyEventToggleConsoleHook1Loc);
	clKeyEventToggleConsoleHook1.installHook(Con_ToggleConsole, false);

	clKeyEventToggleConsoleHook2.initialize(5, (PBYTE)clKeyEventToggleConsoleHook2Loc);
	clKeyEventToggleConsoleHook2.installHook(Con_ToggleConsole, true, false);
}