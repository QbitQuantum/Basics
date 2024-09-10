BOOL CMDriveDlg::Unadvise()
{
	if (m_nAdviseCnt > 0)
	{
		HRESULT hRes = AtlUnadvise(pRandom, IID_IRandomEvent, m_arrAdvise[--m_nAdviseCnt]);
		return (SUCCEEDED(hRes));
	}
	else
		return FALSE;
}