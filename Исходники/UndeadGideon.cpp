void UndeadGideon::PostPropRead(ObjectCreateStruct *pStruct)
{
	if (!pStruct) return;

	char* pFilename = "Models\\Enemies\\Undead_Gideon.abc";
	char* pSkin = "Skins\\Enemies\\Undead_Gideon.dtx";
	_mbscpy((unsigned char*)pStruct->m_Filename, (const unsigned char*)pFilename);
	_mbscpy((unsigned char*)pStruct->m_SkinName, (const unsigned char*)pSkin);
}