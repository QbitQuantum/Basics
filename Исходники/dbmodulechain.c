int InitModuleNames(void)
{
	struct DBModuleName *dbmn;
	DWORD ofsThis;
	int nameLen;
	char *mod;

	hModHeap=HeapCreate(0,0,0);
	lMods.sortFunc=ModCompare;
	lMods.increment=50;
	lOfs.sortFunc=OfsCompare;
	lOfs.increment=50;

	ofsThis=dbHeader.ofsFirstModuleName;
	dbmn=(struct DBModuleName*)DBRead(ofsThis,sizeof(struct DBModuleName),NULL);
	while(ofsThis) {
		if(dbmn->signature!=DBMODULENAME_SIGNATURE) DatabaseCorruption(NULL);

		nameLen=dbmn->cbName;

		mod = (char*)HeapAlloc(hModHeap,0,nameLen+1);
		CopyMemory(mod,DBRead(ofsThis+offsetof(struct DBModuleName,name),nameLen,NULL),nameLen);
		mod[nameLen] = 0;

		AddToList(mod, nameLen, ofsThis);

		ofsThis=dbmn->ofsNext;
		dbmn=(struct DBModuleName*)DBRead(ofsThis,sizeof(struct DBModuleName),NULL);
	}
	CreateServiceFunction(MS_DB_MODULES_ENUM,EnumModuleNames);
	return 0;
}