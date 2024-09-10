void PatchT4_NoBorder()
{
	r_noborder = Dvar_RegisterBool(0, "r_noborder", DVAR_FLAG_ARCHIVE, "Remove the border when running in windowed mode (set vid_xpos and vid_ypos to 0).");

	windowedWindowStyleHook.initialize(windowedWindowStyleHookLoc, WindowedWindowStyleHookStub, 5, false);
	windowedWindowStyleHook.installHook();
}