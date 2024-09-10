//Инициализирует массивы *DMO*
//Функцию достаточно вызвать единожды (если не потребуется DMO другой категории)
void CDirectShow::UpdateDMOArray(DMOCATEGORY dCategory)
{
	IEnumDMO *pEnumDMO = NULL;
	LPWSTR lpwDMOTmp[E_MAX_ARR_SIZE];
	for (m_lCounter = 0; m_lCounter < E_MAX_ARR_SIZE; m_lCounter++)
	{
		lpwDMOTmp[m_lCounter] = NULL;
		if (m_lpwDMONames[m_lCounter])
		{
			delete[] m_lpwDMONames[m_lCounter];
			m_lpwDMONames[m_lCounter] = NULL;
		}
		ZeroMemory(&m_cDMOCLSIDs[m_lCounter], sizeof(m_cDMOCLSIDs[m_lCounter]));
	}
	ZeroMemory(&m_gidRecentDMOCat, sizeof(m_gidRecentDMOCat));
	switch (dCategory)
	{
		case DMO_CATEGORY_AUDIO_DECODER:
			m_gidRecentDMOCat = DMOCATEGORY_AUDIO_DECODER;
			break;
		case DMO_CATEGORY_AUDIO_EFFECT:
			m_gidRecentDMOCat = DMOCATEGORY_AUDIO_EFFECT;
			break;
		case DMO_CATEGORY_AUDIO_ENCODER:
			m_gidRecentDMOCat = DMOCATEGORY_AUDIO_ENCODER;
			break;
		case DMO_CATEGORY_VIDEO_DECODER:
			m_gidRecentDMOCat = DMOCATEGORY_VIDEO_DECODER;
			break;
		case DMO_CATEGORY_VIDEO_EFFECT:
			m_gidRecentDMOCat = DMOCATEGORY_VIDEO_EFFECT;
			break;
		case DMO_CATEGORY_VIDEO_ENCODER:
			m_gidRecentDMOCat = DMOCATEGORY_VIDEO_ENCODER;
			break;
		case DMO_CATEGORY_AUDIO_CAPTURE_EFFECT:
			m_gidRecentDMOCat = DMOCATEGORY_AUDIO_CAPTURE_EFFECT;
			break;
		default:
			return;
	}
    if (FAILED(DMOEnum(m_gidRecentDMOCat, DMO_ENUMF_INCLUDE_KEYED, 0,
		NULL, 0, NULL, &pEnumDMO))) return;
	pEnumDMO->Next(E_MAX_ARR_SIZE, &m_cDMOCLSIDs[0], &lpwDMOTmp[0], &m_lDMOCount);
	if (!m_lDMOCount) return;
	for (m_lCounter = 0; m_lCounter < m_lDMOCount; m_lCounter++)
	{
		m_lpwDMONames[m_lCounter] = new WCHAR[MAX_PATH];
		wcscpy(m_lpwDMONames[m_lCounter], lpwDMOTmp[m_lCounter]);
		CoTaskMemFree(lpwDMOTmp[m_lCounter]);
	}
	pEnumDMO->Release();
}