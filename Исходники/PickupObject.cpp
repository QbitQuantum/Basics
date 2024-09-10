void PickupObject::PostPropRead(ObjectCreateStruct *pStruct)
{
	if (!pStruct) return;

	pStruct->m_Flags |= FLAG_TOUCH_NOTIFY | FLAG_VISIBLE | FLAG_GRAVITY;
	pStruct->m_Flags &= ~FLAG_SHADOW;
	m_dwFlags = pStruct->m_Flags;

	if (!m_hstrObjectName && m_szObjectName)
		m_hstrObjectName = g_pServerDE->CreateString(m_szObjectName);

#ifdef _ADD_ON
	if(m_nType == WEAP_COMBATSHOTGUN || m_nType == WEAP_FLAYER)
	{
		if (m_szFile)
		{
			_mbscpy((unsigned char*)pStruct->m_Filename, (const unsigned char*)"Models_ao/Powerups_ao/");
			_mbscat((unsigned char*)pStruct->m_Filename, (const unsigned char*)m_szFile);
			_mbscat((unsigned char*)pStruct->m_Filename, (const unsigned char*)".abc");
		}

		// Set the skin filename
		if (m_szFile)
		{
			_mbscpy((unsigned char*)pStruct->m_SkinName, (const unsigned char*)"Skins_ao/Powerups_ao/");
			_mbscat((unsigned char*)pStruct->m_SkinName, (const unsigned char*)m_szFile);
			_mbscat((unsigned char*)pStruct->m_SkinName, (const unsigned char*)".dtx");
		}
	}
	else
	{
		if (m_szFile)
		{
			_mbscpy((unsigned char*)pStruct->m_Filename, (const unsigned char*)"Models/Powerups/");
			_mbscat((unsigned char*)pStruct->m_Filename, (const unsigned char*)m_szFile);
			_mbscat((unsigned char*)pStruct->m_Filename, (const unsigned char*)".abc");
		}

		// Set the skin filename
		if (m_szFile)
		{
			_mbscpy((unsigned char*)pStruct->m_SkinName, (const unsigned char*)"Skins/Powerups/");
			_mbscat((unsigned char*)pStruct->m_SkinName, (const unsigned char*)m_szFile);
			_mbscat((unsigned char*)pStruct->m_SkinName, (const unsigned char*)".dtx");
		}
	}
#else
	// Set the model filename
	if (m_szFile)
	{
		_mbscpy((unsigned char*)pStruct->m_Filename, (const unsigned char*)"Models/Powerups/");
		_mbscat((unsigned char*)pStruct->m_Filename, (const unsigned char*)m_szFile);
		_mbscat((unsigned char*)pStruct->m_Filename, (const unsigned char*)".abc");
	}

	// Set the skin filename
	if (m_szFile)
	{
		_mbscpy((unsigned char*)pStruct->m_SkinName, (const unsigned char*)"Skins/Powerups/");
		_mbscat((unsigned char*)pStruct->m_SkinName, (const unsigned char*)m_szFile);
		_mbscat((unsigned char*)pStruct->m_SkinName, (const unsigned char*)".dtx");
	}
#endif
}