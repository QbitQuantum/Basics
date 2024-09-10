void DefenseGlobeLegs::PostPropRead(ObjectCreateStruct *pStruct)
{
    if (!pStruct) return;

	char* pFilename = "Models\\Enemies\\def_bot.abc";
	char* pSkin = "Skins\\Enemies\\def_bot.dtx";
	_mbscpy((unsigned char*)pStruct->m_Filename, (const unsigned char*)pFilename);
	_mbscpy((unsigned char*)pStruct->m_SkinName, (const unsigned char*)pSkin);
    
   	pStruct->m_NextUpdate = 0.0f;
    
	pStruct->m_Flags = FLAG_VISIBLE | FLAG_SOLID | FLAG_GRAVITY | FLAG_STAIRSTEP | FLAG_SHADOW;	
}