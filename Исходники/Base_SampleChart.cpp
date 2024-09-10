void CBase_SampleChart::OnExportData()
{
	CString file = _T("C:/Points.csv");

	CFileDialog mFileDlg(FALSE,_T("csv"),_T("Points"),OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,_T("csv文件|*.csv||"),this);
	DWORD dwVersion = GetVersion();
	DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
	DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
	if (dwVersion < 0x80000000) mFileDlg.m_ofn.lStructSize=88;//显示新的文件对话框
	else mFileDlg.m_ofn.lStructSize=76;//显示老的文件对话框
	mFileDlg.m_ofn.lpstrTitle= _T("保存到文件");
	if(mFileDlg.DoModal() !=IDOK ) return;
	file = mFileDlg.GetPathName();

	CString strSep = _T(",");
	CFile f;
	BOOL ret = f.Open(file,CFile::modeCreate | CFile::modeReadWrite);
	if(!ret)
	{
		MessageBox(_T("打开文件失败，可能是文件为只读属性或被占用"));
		return;
	}
	CString line(_T("时间"));
	//
	CArray<CChartSerie*, CChartSerie*> series;
	series.Add(m_pcCurveMain);
	unsigned maxCount = 0;
	CChartSerie* pSerieOfMaxCount = NULL;
	for(int i=0; i<=series.GetUpperBound(); ++i)
	{
		CChartSerie* pS = series.GetAt(i);
		unsigned c = pS->GetPointsCount();
		if(c > maxCount)
		{
			maxCount = c;
			pSerieOfMaxCount = pS;
		}
		line = line + strSep + pS->GetName().c_str();
	}
	//标题列
	{
		TWen_USES_CONVERSION;
		LPCSTR s=TWen_CT2A(line + _T("\r\n"));
		f.Write(s,strlen(s));
	}
	for(size_t i=0; i<maxCount; i++)
	{
		line.Format(_T("%.15f"), pSerieOfMaxCount->m_vPoints.m_pPoints[i].x);
		for(int j=0; j<=series.GetUpperBound(); ++j)
		{
			CChartSerie* pS = GetSerieByIndex(j);
			unsigned c = pS->GetPointsCount();
			CString v;
			if(c > i) v.Format(_T("%.15f"), pS->m_vPoints.m_pPoints[i].y);
			line = line + strSep + v;
		}
		{
			TWen_USES_CONVERSION;
			LPCSTR s=TWen_CT2A(line + _T("\r\n"));
			f.Write(s,strlen(s));
		}
	}
	f.Close();
	MessageBox(_T("数据已保存到文件[")+file+_T("]"));
}