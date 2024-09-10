void PatchMW2_WeaponCamos()
{
#if PRE_RELEASE_DEMO
	// before enabling: g_modelindex: overflow
	return;
#endif

	xModelTable.set_empty_key("");
	xMaterialTable.set_empty_key("");

	/*
	xModelLoadHook.initialize(xModelLoadHookLoc, XModelLoadHookFunc);
	xModelLoadHook.installHook();

	xModelLoadHook2.initialize(xModelLoadHook2Loc, XModelLoadHookFunc);
	xModelLoadHook2.installHook();

	xModelLoadHook3.initialize(xModelLoadHook3Loc, XModelLoadHookFunc);
	xModelLoadHook3.installHook();
	*/

	forEachXAssetHook.initialize(forEachXAssetHookLoc, ForEachXAssetHookStub);
	forEachXAssetHook.installHook();

	postWeaponLoadHook.initialize(postWeaponLoadHookLoc, PostWeaponLoadHookStub);
	postWeaponLoadHook.installHook();
}