void CRTFReaderTHDDlg::OnRead() 
{
#ifndef _DEBUG
	try
#endif
	{
		UpdateData(TRUE);
		EnableReaders(false);

		IWSRTFFile* pFile1 = NULL;

		USES_CONVERSION;
		IID iidRtfFile;
		IIDFromString(T2W(_T("{") _T(_IID_IWSRTFFile) _T("}")), &iidRtfFile);

		CLSID clsidRtfFile;
		CLSIDFromProgID(T2W(_T(_PROGID_WSRTFFile)), &clsidRtfFile);
		HRESULT hr=CoCreateInstance(clsidRtfFile,NULL,CLSCTX_INPROC_SERVER,iidRtfFile, reinterpret_cast<void**> (&pFile1));

		if (SUCCEEDED(hr))
		{
			BOOL bRes = CopyFile(LPCTSTR(m_csFile1), CString(CGeneral::GetTemporaryPath().c_str()) + _T("\\RTFIn1.rtf"), false);
			bRes = CopyFile(LPCTSTR(m_csFile1), CString(CGeneral::GetTemporaryPath().c_str()) + _T("\\RTFIn1.txt"), false);

			pFile1->InputFileName=_bstr_t(m_csFile1);
			pFile1->OutputFileName=_bstr_t(CString(CGeneral::GetTemporaryPath().c_str())+_T("\\RTFOut1.rtf"));



//			pFile1->put_InputFileName(_bstr_t(m_csFile1));
//			pFile1->put_OutputFileName(_bstr_t());

			pFile1->ReadFile();

			pFile1->WriteFile();

			pFile1->Release();

			bRes=CopyFile(CString(CGeneral::GetTemporaryPath().c_str())+_T("\\RTFOut1.rtf"),CString(CGeneral::GetTemporaryPath().c_str())+_T("\\RTFOut1.txt"),false);

		}
		else
			AfxMessageBox(_T("Cannot Create  WSCompose3.WSRTFFile Object"), MB_OK | MB_ICONSTOP);

/*
		RTFfile f, g;


		ERTFToken ec = f.ReadFile(LPCTSTR(m_csFile1));
		ec = f.WriteFile(CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFOut1.txt");
		CopyFile(CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFOut1.txt", CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFOut1.rtf", false);		
		
		if(m_bMerge)
		{
			bRes = CopyFile(LPCTSTR(m_csFile2), CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFIn2.rtf", false);
		    bRes = CopyFile(LPCTSTR(m_csFile2), CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFIn2.txt", false);

			ec = g.ReadFile(m_csFile2);

			g.WriteFile(CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFOut2.txt");
			CopyFile(CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFOut2.txt", CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFOut2.rtf", false);
			
			f.MergeResources(&g);

			f.WriteFile(CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFMerged.txt");
			CopyFile(CString(CGeneral::GetTemporaryPath().c_str()) + "\\RTFMerged.txt", CString(CGeneral::GetTemporaryPath().c_str()) + "\\Merged.rtf", false);			
		}

*/
		EnableReaders(true);



	}
#ifndef _DEBUG
	catch(...)
	{
		// Exception thrown
		ASSERT(false);
	}
#endif
//	RTFformatting::ClearStatics();
}