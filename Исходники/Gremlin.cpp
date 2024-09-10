void GremlinAI::PostPropRead(ObjectCreateStruct *pStruct)
{
	if (!pStruct) return;

	char* pFilename = "Models_ao\\Enemies_ao\\Gremlin.abc";
	char* pSkin = "Skins_ao\\Enemies_ao\\Gremlin.dtx";
	_mbscpy((unsigned char*)pStruct->m_Filename, (const unsigned char*)pFilename);
	_mbscpy((unsigned char*)pStruct->m_SkinName, (const unsigned char*)pSkin);
}