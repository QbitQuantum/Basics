void PatchMW2_InGameMenu()
{
	ingameMenuHook.initialize(ingameMenuHookLoc, IngameMenuHookStub);
	ingameMenuHook.installHook();
}