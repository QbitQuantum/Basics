void KG3DAnimationSoundTagInfo::Init()
{
	int nHeight = 0;
	ITabFile *pTabFile = NULL;
    IIniFile *pIniFile = NULL;
    pTabFile = g_OpenTabFile(s_strConfigTabFile);
	KG_PROCESS_ERROR(pTabFile);
	m_SoundType.clear();
	m_AnimationSoundTagInfo.clear();
	for (size_t i = 0 ; i < sizeof(s_strSoundType) / sizeof(TCHAR *) ; i ++)
	{
		std::string strFirst = s_strSoundType[i];
		m_SoundType[strFirst] = i;
	}
	nHeight = pTabFile->GetHeight();
	for (int i = 2 ; i <= nHeight ; i ++)
	{
		AnimationSoundTagInfo Info;
		TCHAR strSoundType[MAX_PATH];
		std::string SoundTypetemp;
		iter it = m_SoundType.begin();
		int nSoundType = 0;
		pTabFile->GetString(i,COL_SOUNDTYPE,"",strSoundType,MAX_PATH);
		pTabFile->GetString(i,COL_FILENAME,"",Info.strFileName,MAX_PATH);
		pTabFile->GetFloat(i,COL_RATE,0.0f,&Info.fRate);
		_strlwr_s(strSoundType,MAX_PATH);
		SoundTypetemp = strSoundType;
		KG_PROCESS_ERROR(m_SoundType.find(SoundTypetemp) != m_SoundType.end());
		Info.soundType = static_cast<SoundType>(m_SoundType[SoundTypetemp]);
		nSoundType = m_SoundType[SoundTypetemp];
		if(m_AnimationSoundTagInfo.find(nSoundType) 
			!= m_AnimationSoundTagInfo.end())
		{
			m_AnimationSoundTagInfo[nSoundType].push_back(Info);
		}
		else
		{
			std::vector<AnimationSoundTagInfo> vec;
			vec.push_back(Info);
			m_AnimationSoundTagInfo[nSoundType] = vec;
		}
	}
	Adjust();
    pIniFile = g_OpenIniFile(s_strConfigIniFile);
    KG_PROCESS_ERROR(pIniFile);
    pIniFile->GetInteger("ROOT","SaveVersion3Data",0,&m_nSaveVersion3Data);
	m_bInit = TRUE;
Exit0:
    SAFE_RELEASE(pTabFile);
    SAFE_RELEASE(pIniFile);
	;
}