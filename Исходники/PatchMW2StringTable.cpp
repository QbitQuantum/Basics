// entry point
void PatchMW2_StringTable()
{
	stringTables.set_empty_key("");

	stringTableHook.initialize(stringTableHookLoc, StringTable_GetAsset);
	stringTableHook.installHook();
}