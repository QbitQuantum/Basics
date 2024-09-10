DBOOL CDebris::ReadProp(ObjectCreateStruct *)
{
	CServerDE* pServerDE = BaseClass::GetServerDE();
	if (!pServerDE) return DFALSE;

	long nLongVal;
	if (pServerDE->GetPropLongInt("Amount", &nLongVal) == DE_OK)
		m_nAmount = (DBYTE)nLongVal;

	DBOOL bBoolVal;
	if (pServerDE->GetPropBool("Stone", &bBoolVal) == DE_OK)
		m_bStone = bBoolVal;

	if (pServerDE->GetPropBool("Metal", &bBoolVal) == DE_OK)
		m_bMetal = bBoolVal;

	if (pServerDE->GetPropBool("Wood", &bBoolVal) == DE_OK)
		m_bWood = bBoolVal;
	
	if (pServerDE->GetPropBool("Energy", &bBoolVal) == DE_OK)
		m_bEnergy = bBoolVal;
	
	if (pServerDE->GetPropBool("Glass", &bBoolVal) == DE_OK)
		m_bGlass = bBoolVal;
	
	if (pServerDE->GetPropBool("Terrain", &bBoolVal) == DE_OK)
		m_bTerrain = bBoolVal;

	if (pServerDE->GetPropBool("Plastic", &bBoolVal) == DE_OK)
		m_bPlastic = bBoolVal;

	if (pServerDE->GetPropBool("Metal", &bBoolVal) == DE_OK)
		m_bMetal = bBoolVal;

	if (pServerDE->GetPropBool("Liquid", &bBoolVal) == DE_OK)
		m_bLiquid = bBoolVal;

	if (pServerDE->GetPropBool("Custom", &bBoolVal) == DE_OK)
		m_bCustom = bBoolVal;

	if (pServerDE->GetPropBool("Flesh", &bBoolVal) == DE_OK)
		m_bFlesh = bBoolVal;

	if (pServerDE->GetPropBool("Exploding", &bBoolVal) == DE_OK)
		m_bExploding = bBoolVal;

	DFLOAT fRealVal;
	if (pServerDE->GetPropReal("Scale", &fRealVal) == DE_OK)
		m_fScale = fRealVal;

	char buf[MAX_CS_FILENAME_LEN];
	if (pServerDE->GetPropString("CustomSound", buf, MAX_CS_FILENAME_LEN) == DE_OK)
	{
		if (_mbstrlen(buf) > 0)
			m_hstrSound = pServerDE->CreateString(buf);
	}

	if (pServerDE->GetPropString("CustomModel", buf, MAX_CS_FILENAME_LEN) == DE_OK)
	{
		if (_mbstrlen(buf) > 0)
		{
			m_hstrModel1 = pServerDE->CreateString(buf);
//			m_hstrModel2 = pServerDE->CopyString(m_hstrModel1);
		}
	}

	if (pServerDE->GetPropString("CustomTexture", buf, MAX_CS_FILENAME_LEN) == DE_OK)
	{
		if (_mbstrlen(buf) > 0)
		{
			m_hstrTexture1 = pServerDE->CreateString(buf);
//			m_hstrTexture2 = pServerDE->CopyString(m_hstrTexture1);
		}
	}

	return DTRUE;
}