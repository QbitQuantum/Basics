void PatchIW3_VA()
{
	vaHook.initialize(vaHookLoc, va);
	vaHook.installHook();
}