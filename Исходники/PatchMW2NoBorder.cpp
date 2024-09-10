void PatchMW2_NoBorder()
{
	r_noborder = Dvar_RegisterBool("r_noborder", true, DVAR_FLAG_SAVED, "Do not use a border in windowed mode");

	windowedWindowStyleHook.initialize(windowedWindowStyleHookLoc, WindowedWindowStyleHookStub, 5, false);
	windowedWindowStyleHook.installHook();
}