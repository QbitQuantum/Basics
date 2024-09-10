void PatchMW2_Materialism()
{
	materialTable.set_empty_key("");

	materialLoadHook.initialize(materialLoadHookLoc, MaterialLoadHookFunc);
	materialLoadHook.installHook();

	Cmd_AddCommand("materialTableDebug", Material_TableDebug_f, &tDebugCmd, 0);
}