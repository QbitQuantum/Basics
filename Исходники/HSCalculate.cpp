CString CHSCalculate::CreateHtml(const CString& strContent, const InfoIndex* pInfoIndex)
{
	if (pInfoIndex == NULL)
	{
		return "";
	}

	// 读格式文件
	CString strPath = CGeneralHelper::GetAppPath() + _T("face\\html\\") + HTMLFORMAT_PATH;
	CFile  fRead(strPath, CFile::modeRead); 
    long flen = (long)fRead.GetLength(); 
	if (flen <= 0)
	{
		return "";
	}
	char*  pBuffer = new char[flen]; 
	fRead.Read(pBuffer,flen); 
	CString strFotmat(pBuffer, flen);
	delete[] pBuffer;
	fRead.Close();

	//////////////////////////////////////////////////////////////////////////
	// 形成html文件
	// 标题
	strFotmat.Replace(HTML_REPLACE_TITLE, pInfoIndex->m_cTitle);
	// 正文
	// 将换行符替换成<\br>
	CString strFormatContent(strContent, strContent.GetLength());
	strFormatContent.Replace("\r\n", "</br>&nbsp&nbsp");
	strFotmat.Replace(HTML_REPLACE_CONTENT, strContent);
	// 时间
	CString strTime;
	strTime.Format("%04d-%02d-%02d ", pInfoIndex->m_lDate/10000, (pInfoIndex->m_lDate%10000)/100, pInfoIndex->m_lDate%100);
	strTime.AppendFormat("%02d:%02d:%02d", pInfoIndex->m_lTime/10000, (pInfoIndex->m_lTime%10000)/100, pInfoIndex->m_lTime%100);
	strFotmat.Replace(HTML_REPLACE_TIME, strTime);
	// 作者
	CString strAuthor = "";
	strFotmat.Replace(HTML_REPLACE_AUTHOR, strAuthor);
	// 来源
	CString strOrigin = "";
	strFotmat.Replace(HTML_REPLACE_ORIGIN, strOrigin);
	//////////////////////////////////////////////////////////////////////////

	// 写html文件
	strPath = CGeneralHelper::GetAppPath() + _T("face\\html\\") + HTMLCONTENT_PATH;
	CFile fWrite(strPath, CFile::modeCreate | CFile::modeWrite);
	fWrite.Write(strFotmat.GetBuffer(), strFotmat.GetLength());
	fWrite.Close();

	return strPath;
}