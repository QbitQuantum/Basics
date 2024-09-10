void PatchMW2_StringList()
{
	slHashMap.set_empty_key("*DUMMYDUMMY*");
	slHashMap.set_deleted_key("*DUMMYDUMM*");

	call(0x4D2280, SL_Init, PATCH_JUMP);
	call(0x436B40, SL_GetStringOfSize, PATCH_JUMP);
	call(0x4EC1D0, SL_ConvertToString_, PATCH_JUMP);
	call(0x61BCB0, FindStringOfSize, PATCH_JUMP);
	call(0x469D80, SL_ConvertFromString, PATCH_JUMP);
	call(0x4D9B00, SL_AddRefToString, PATCH_JUMP);
	call(0x4F1500, SL_RemoveRefToStringOfSize, PATCH_JUMP);
	call(0x47CD70, SL_RemoveRefToString, PATCH_JUMP);
	call(0x417730, Scr_SetString, PATCH_JUMP);
	call(0x4401E0, SL_GetStringLen, PATCH_JUMP);
	call(0x40C050, SL_TransferRefToUser, PATCH_JUMP);
	call(0x4B4310, SL_AddUser, PATCH_JUMP);
	call(0x430510, SL_ConvertToLowercase, PATCH_JUMP);
	call(0x4F46D0, SL_ShutdownSystem, PATCH_JUMP);
	call(0x4A44A0, SL_TransferSystem, PATCH_JUMP);

	stringHeap = HeapCreate(0, 1024 * 1024, 0);

	// path_node_constant_t marking function; has some terrible string references
	*(BYTE*)0x4F74B0 = 0xC3;
}