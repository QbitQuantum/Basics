void PatchMW2_UserAvatars()
{
	call(0x594295, SetPlayerCardInfoHook, PATCH_CALL);

	initGFXImages.initialize(initGFXImagesLoc, InitGFXImagesHook);
	initGFXImages.installHook();

	call(0x59449F, OnServerCommandStub, PATCH_JUMP);

	call(0x5910BC, DrawScoreboardRankStub, PATCH_CALL);
}