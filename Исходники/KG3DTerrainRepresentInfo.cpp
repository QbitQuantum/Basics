HRESULT KG3DTerrainRepresentInfo::Init()
{
	HRESULT hResult = E_FAIL;
    HRESULT hRetCode = E_FAIL;
	int nHeight = 0;
	
	m_TerrainRepresentInfo.clear();

	ITabFile *pTabFile = g_OpenTabFile(s_strConfigFile);
	KG_PROCESS_ERROR(pTabFile);

	nHeight = pTabFile->GetHeight();
	for (int i = 2; i <= nHeight; i++)
	{
		TerrainRepresentInfo Info;
		int nGroundType = 0;
		TCHAR strLower[MAX_PATH];
		pTabFile->GetString(i, COL_FILENAME, "", Info.strFileName, MAX_PATH);
		strcpy_s(strLower, MAX_PATH, Info.strFileName);
		_strlwr_s(strLower, MAX_PATH);
		DWORD dwHash = g_FileNameHash(strLower);
		pTabFile->GetString(i, COL_ANNOTATE, "", Info.strAnnotate, MAX_PATH);
		pTabFile->GetInteger(i, COL_TYPE, INVALID_GROUNDTYPE, &nGroundType);
		Info.dwType = static_cast<DWORD>(nGroundType);

        pTabFile->GetString(i,COL_SFX,"",Info.strSfx[COL_SFX-COL_SFX],MAX_PATH);
        pTabFile->GetString(i,COL_SFX1,"",Info.strSfx[COL_SFX1-COL_SFX],MAX_PATH);
        pTabFile->GetString(i,COL_SFX2,"",Info.strSfx[COL_SFX2-COL_SFX],MAX_PATH);
        pTabFile->GetString(i,COL_SFX3,"",Info.strSfx[COL_SFX3-COL_SFX],MAX_PATH);
        pTabFile->GetString(i,COL_SFXTERRAIN,"",Info.strSfxTerrain,MAX_PATH);

		pTabFile->GetFloat(i, COL_SFX_RATE, 1.0f, &Info.fSfxPlayRate);//不填默认100%
		m_TerrainRepresentInfo[dwHash] = Info;
	}
    hRetCode = InitDis();
    KG_COM_PROCESS_ERROR(hRetCode);
    hRetCode = InitDefaultSfx();
    KG_COM_PROCESS_ERROR(hRetCode);
	hResult = S_OK;
Exit0:
	SAFE_RELEASE(pTabFile);
	return hResult;
}