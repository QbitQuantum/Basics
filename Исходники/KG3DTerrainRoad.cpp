void KG3DTerrainRoad::UnInit()
{
	KG3DSerpentine::UnInit();
	if(m_lpPointLightInfo)
	{
		g_cPointLightInfoPool.FreeResource(m_lpPointLightInfo);
		m_lpPointLightInfo = NULL;
	}
	SAFE_RELEASE(m_lpTexture);
}