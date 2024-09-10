BOOL LLFloaterHardwareSettings::postBuild()
{
	childSetAction("OK", onBtnOK, this);
	childSetAction("Cancel", onBtnCancel, this);

// Don't do this on Mac as their braindead GL versioning
// sets this when 8x and 16x are indeed available
//
#if !LL_DARWIN
	if (gGLManager.mIsIntel || gGLManager.mGLVersion < 3.f)
	{ //remove FSAA settings above "4x"
		LLComboBox* combo = getChild<LLComboBox>("fsaa");
		combo->remove("8x");
		combo->remove("16x");
	}
#endif

	refresh();
	center();

	// load it up
	initCallbacks();
	return TRUE;
}