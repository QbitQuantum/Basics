void CTraceZler::SaveToFile()
{
	TCHAR wcsTraceFolder[_MAX_PATH];
	wsprintf(wcsTraceFolder, L"%s\\Trace", ModulePath);
	//进入Trace目录
	if (_wchdir(wcsTraceFolder) != 0)
	{
		_wmkdir(wcsTraceFolder);
		_wchdir(wcsTraceFolder);
	}
	//写入序号文件
	static TCHAR wcsFileName[_MAX_PATH];
	for (int i = 0; i < TrCount2; i++)
	{
		UpdateBoard(&TrList1[TrList2[i].index]);
		UpdateBoard(&TrList2[i]);
		wsprintf(wcsFileName, L"%d_%d.pgn", m_nTraceTimes, i);
		SaveToPgn(wcsFileName);
		//还原盘面
		RestoreBoard(&TrList2[i]);
		RestoreBoard(&TrList1[TrList2[i].index]);
	}
}