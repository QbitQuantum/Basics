//this will take a list of properties and convert it to internal values
bool CBaseFXProps::ParseProperties(FX_PROP* pProps, uint32 nNumProps)
{
	//counts of how many of each key
	uint32 nNumColorKeys = 0;
	uint32 nNumScaleKeys = 0;

	//go through the property list and parse in all the known variables and
	//count up how many of each key type we have
	uint32 nCurrProp = 0;

	for(nCurrProp = 0; nCurrProp < nNumProps; nCurrProp++)
	{
		FX_PROP& fxProp = pProps[nCurrProp];

		if( !_stricmp( fxProp.m_sName, FXPROP_UPDATEPOS ))
		{
			m_nFollowType = (uint32)fxProp.GetComboVal();
		}
		else if( !_stricmp( fxProp.m_sName, FXPROP_ATTACHNAME ))
		{
			fxProp.GetStringVal( m_szAttach );
		}
		else if( !_stricmp( fxProp.m_sName, FXPROP_OFFSET ))
		{
			m_vOffset = fxProp.GetVector();
		}
		else if( !_stricmp( fxProp.m_sName, FXPROP_ROTATEADD ))
		{
			m_vRotAdd = fxProp.GetVector();
		}
		else if( !_stricmp( fxProp.m_sName, FXPROP_MENULAYER ))
		{
			m_nMenuLayer = fxProp.GetIntegerVal();
		}
		else if( !_stricmp( fxProp.m_sName, "Ck" ))
		{
			nNumColorKeys++;
		}
		else if( !_stricmp( fxProp.m_sName, "Sk" ))
		{
			nNumScaleKeys++;
		}
	}

	//allocate our arrays of key types
	debug_deletea( m_pColorKeys );
	m_pColorKeys = debug_newa( FX_COLOURKEY, nNumColorKeys );
	m_nNumColorKeys = 0;

	debug_deletea( m_pScaleKeys );
	m_pScaleKeys = debug_newa( FX_SCALEKEY, nNumScaleKeys );
	m_nNumScaleKeys = 0;

	//now actually read in each key type
	for(nCurrProp = 0; nCurrProp < nNumProps; nCurrProp++)
	{
		FX_PROP& fxProp = pProps[nCurrProp];

		if( !_stricmp( fxProp.m_sName, "Ck" ))
		{
			// Add this key to the list of keys

			FX_COLOURKEY fxClrKey;

			fxClrKey.m_tmKey = fxProp.m_data.m_clrKey.m_tmKey;
			fxClrKey.m_red   = (float) (fxProp.m_data.m_clrKey.m_dwCol & 0x000000FF);
			fxClrKey.m_green = (float)((fxProp.m_data.m_clrKey.m_dwCol & 0x0000FF00) >> 8);
			fxClrKey.m_blue  = (float)((fxProp.m_data.m_clrKey.m_dwCol & 0x00FF0000) >> 16);
			fxClrKey.m_alpha = (float)((fxProp.m_data.m_clrKey.m_dwCol & 0xFF000000) >> 24);

			if(m_pColorKeys)
				m_pColorKeys[m_nNumColorKeys++] = fxClrKey;
		}
		else if( !_stricmp( fxProp.m_sName, "Sk" ))