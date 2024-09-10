void CLotteryDlg::_readInfo()
{
	CString strCurPath;
	if ((strCurPath = _getCurPath()).IsEmpty())
		return ;
	wchar_t strFilename[1024];
	memset(strFilename, 0, sizeof(strFilename));
	//MultiByteToWideChar(CP_ACP, 0, strCurPath, strCurPath.GetLength() * sizeof(TCHAR), strFilename, strCurPath.GetLength());
	wmemcpy_s(strFilename, sizeof(strFilename), (LPCTSTR)strCurPath, strCurPath.GetLength());
	std::wstring strDataPath(strFilename);

	strDataPath += L"data.txt";
	std::ifstream infile(strDataPath.c_str());
	if (!infile)
	{
		AfxMessageBox(L"没找到参与抽奖者数据");
		return ;
	}
	char buf[32];
	std::string strData;
	PartnersInfo pi;
	char separator[] = "\r\n\t ";
	bool bN = false, bP = false;
	while (1)
	{
		infile.getline(buf, sizeof(buf));
		strData = buf;
		size_t pos = 0;
		bN = false;
		for (; pos < strData.size(); ++pos)
		{
			if ((strData[pos] == '\t' || strData[pos] == ' '))
			{
				if (bN)
					break;
			}
			else
			{
				bN = true;
				pi._name += strData[pos];
			}
		}
		bP = false;
		for (; pos < strData.size(); ++pos)
		{
			if ((strData[pos] == '\t' || strData[pos] == ' '))
			{
				if (bP)
					break;
			}
			else
			{
				bP = true;
				pi._pn += strData[pos];
			}
		}
		if ((infile.rdstate() & ifstream::eofbit) != 0)
			break;
		//要排除数据中出现的信息重复情况
		if (find(m_PartnerInfo.begin(), m_PartnerInfo.end(), pi) == m_PartnerInfo.end())
			m_PartnerInfo.push_back(pi);
		pi.clear();
	}
	infile.close();
	infile.clear();
}