void PatchMW2_Extrasensory()
{
	entityWriteFieldsHook.initialize(entityWriteFieldsHookLoc, EntityWriteFieldsHookStub);
	entityWriteFieldsHook.installHook();
}