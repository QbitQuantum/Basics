void MFSound_DeinitModulePlatformSpecific()
{
	MFCALLSTACK;

	// TODO: remove this, user will control contexts
	DestroyContext(gpCurrentContext);
}