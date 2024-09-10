void DB_LoadXAssets_Hook(XZoneInfo *zoneinfo, unsigned int assetscount)
{

	int i;

	DB_FreeUnusedResources();
	for(i = 0; i < assetscount; i++)
	{
		DB_UnloadFastFile( zoneinfo[i].notknown );
	}
	_InterlockedExchangeAdd(&g_unknownVar_1, -1);
	g_archiveBuf = 0;
	DB_LoadSounds();
	DB_LoadDObjs();
	Material_DirtyTechniqueSetOverrides();
	BG_FillInAllWeaponItems();

}