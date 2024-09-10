CString CBase_AnalysisTemplate::GetDataFolder(enumPADATATYPENAME nDataType)
{
	TCHAR szOut[MAX_PATH];
	DWORD dwAttr;
	switch(nDataType) {
	case PA_DATATYPENAME_SAMPLE:
		StrCpy(szOut, g_cConfigIni.CurrentSystem().m_szPathSample);
		break;
	case PA_DATATYPENAME_TASK:
		StrCpy(szOut, g_cConfigIni.CurrentSystem().m_szPathTask);
		break;
	case PA_DATATYPENAME_COMPOUND:
		StrCpy(szOut, g_cConfigIni.CurrentSystem().m_szPathCompound);
		break;
	case PA_DATATYPENAME_METHOD:
		StrCpy(szOut, g_cConfigIni.CurrentSystem().m_szPathMethod);
		break;
	case PA_DATATYPENAME_CRYSTALREPORT:
		StrCpy(szOut, g_cConfigIni.CurrentSystem().m_szPathCrystalReport);
		break;
	case PA_DATATYPENAME_LOG:
		StrCpy(szOut, g_cConfigIni.CurrentSystem().m_szPathLog);
		break;
	case PA_DATATYPENAME_DATA:
	default:
		StrCpy(szOut, g_cConfigIni.CurrentSystem().m_szPathData);
	}

	dwAttr = GetFileAttributes(szOut);
	if (dwAttr == INVALID_FILE_ATTRIBUTES || !(dwAttr & FILE_ATTRIBUTE_DIRECTORY)) {
		SHCreateDirectory(NULL, szOut);
	}
	PathAddBackslash(szOut);
	return CString(szOut);
}