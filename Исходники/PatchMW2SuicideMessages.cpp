void PatchMW2_SuicideMessages()
{
	srand((unsigned int)time(NULL));

	printObituaryHook.initialize(printObituaryHookLoc, PrintObituaryHookStub);
	printObituaryHook.installHook();
}