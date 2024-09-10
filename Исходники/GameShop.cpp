void GameShop::Load()	//-> Complete
{
	char * OptionFile	= gDirPath.GetNewPath("GameShop\\GameShop.ini");
	// ----
	this->OptionData.ActiveGameShop	= GetPrivateProfileIntA("Main", "Active", 1, OptionFile);
	this->OptionData.AddGPBonus		= GetPrivateProfileIntA("GoblinPointBonus", "AddBonus", 0, OptionFile);
	// ----
	this->OptionData.ScriptMajor	= GetPrivateProfileIntA("ScriptVersion", "Major", 512, OptionFile);
	this->OptionData.ScriptMinor	= GetPrivateProfileIntA("ScriptVersion", "Minor", 2012, OptionFile);
	this->OptionData.ScriptRevision	= GetPrivateProfileIntA("ScriptVersion", "Revision", 10, OptionFile);
	this->OptionData.BannerMajor	= GetPrivateProfileIntA("BannerVersion", "Major", 512, OptionFile);
	this->OptionData.BannerMinor	= GetPrivateProfileIntA("BannerVersion", "Minor", 2010, OptionFile);
	this->OptionData.BannerRevision	= GetPrivateProfileIntA("BannerVersion", "Revision", 5, OptionFile);
	// ----
	if( !this->OptionData.ActiveGameShop )
	{
		LogAdd("[GameShop] GameShop is disabled");
		return;
	}
	// ----
	this->ItemList.clear();
	this->PackageList.clear();
	ZeroMemory(this->PointCategory, sizeof(this->PointCategory));
	// ----
	this->ReadCategoryList(gDirPath.GetNewPath("GameShop\\GameShopCategory.txt"));
	this->ReadItemList(gDirPath.GetNewPath("GameShop\\GameShopItem.txt"));
	this->ReadPackageList(gDirPath.GetNewPath("GameShop\\GameShopPackage.txt"));
}