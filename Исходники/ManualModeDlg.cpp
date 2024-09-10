/**
 * @param uNotifyCode - notification code if the message is from a control. If the message is from an accelerator, this value is 1. If the message is from a menu, this value is zero.
 * @param nID - specifies the identifier of the menu item, control, or accelerator.
 * @param hWndCtl - handle to the control sending the message if the message is from a control. Otherwise, this parameter is NULL.
 */
void CManualModeDlg::OnCalculate(UINT /*uNotifyCode*/, int /*nID*/, HWND /*hWndCtl*/)
{
	try
	{
		CString strMapPdbFile;
		m_txtMapPdbFile.GetWindowText(strMapPdbFile);
		if (strMapPdbFile.IsEmpty())
		{
			MsgTip::ShowMessage(m_txtMapPdbFile, IDS_INVALIDMAPPDBFILE);
			return;
		}

		CNumEdit& txtBaseAddress = m_txtBaseAddress.GetNumEdit();
		DWORD64 dwBaseAddress64;
		txtBaseAddress.GetValue(dwBaseAddress64);
		PVOID ptrBaseAddress = (PVOID)dwBaseAddress64;
		if (! ptrBaseAddress)
		{
			MsgTip::ShowMessage(txtBaseAddress, IDS_INVALIDBASEADDRESS);
			return;
		}

		CNumEdit& txtCrashAddress = m_txtCrashAddress.GetNumEdit();
		DWORD64 dwCrashAddress64;
		txtCrashAddress.GetValue(dwCrashAddress64);
		PVOID ptrCrashAddress = (PVOID)dwCrashAddress64;
		if (! ptrCrashAddress)
		{
			MsgTip::ShowMessage(txtCrashAddress, IDS_INVALIDCRASHADDRESS);
			return;
		}

		CWaitDialog wait(m_hWnd);
		switch (m_eProcessedFileType)
		{
		case CBaseProcessor::PFT_MAP:
			{
				CBaseProcessor* pBaseProcessor = m_pProcessor.get();
				if (! pBaseProcessor || pBaseProcessor->GetRuntimeClass() != RUNTIME_CLASS(CMapProcessor))
				{
					MsgTip::ShowMessage(m_txtMapPdbFile, IDS_INVALIDMAPPDBFILE);
					return;
				}
				CMapProcessor* pMapProcessor = STATIC_DOWNCAST(CMapProcessor, pBaseProcessor);
				pMapProcessor->SetBaseAddress(ptrBaseAddress);
			}
			break;
		case CBaseProcessor::PFT_PDB:
			{
				CNumEdit& txtModuleSize = m_txtModuleSize.GetNumEdit();
				DWORD32 dwModuleSize;
				txtModuleSize.GetValue(dwModuleSize);
				if (! dwModuleSize)
				{
					MsgTip::ShowMessage(txtModuleSize, IDS_INVALIDMODULESIZE);
					return;
				}
				m_pProcessor.reset(); // unload old modules
				CPdbProcessor* pPdbProcessor = new CPdbProcessor();
				m_pProcessor.reset(pPdbProcessor);
				pPdbProcessor->LoadModule(strMapPdbFile, ptrBaseAddress, dwModuleSize);
			}
			break;
		default:
			MsgTip::ShowMessage(m_txtMapPdbFile, IDS_INVALIDMAPPDBFILE);
			return;
		}

		CString strFunctionInfo;
		boost::shared_ptr<CBaseFnInfo> pFnInfo;
		DWORD64 dwDisplacement64;
		if (m_pProcessor->FindFunctionInfo(ptrCrashAddress, pFnInfo, dwDisplacement64))
		{
			CString strFunctionName(CA2CT(pFnInfo->GetName().c_str()));
			if (dwDisplacement64 != 0)
				strFunctionInfo.Format(_T("%s+%I64u bytes"), strFunctionName, dwDisplacement64);
			else
				strFunctionInfo = strFunctionName;
		}
		else
			strFunctionInfo.LoadString(IDS_NOFUNCTIONINFO);
		m_txtFunctionName.SetWindowText(strFunctionInfo);

		CString strSourceFile, strLineInfo;
		boost::shared_ptr<CBaseFileInfo> pFileInfo;
		boost::shared_ptr<CBaseLineInfo> pLineInfo;
		DWORD dwDisplacement32;
		if (m_pProcessor->FindLineInfo(ptrCrashAddress, pFileInfo, pLineInfo, dwDisplacement32))
		{
			strSourceFile = CA2CT(pFileInfo->GetFileName().c_str());
			UINT uLineNumber = pLineInfo->GetNumber();
			if (dwDisplacement32 != 0)
				strLineInfo.Format(_T("line %u+%I32u bytes"), uLineNumber, dwDisplacement32);
			else
				strLineInfo.Format(_T("line %u"), uLineNumber);
		}
		else
		{
			strSourceFile.LoadString(IDS_NOSOURCEFILEINFO);
			strLineInfo.LoadString(IDS_NOLINEINFO);
		}
		m_txtSourceFile.SetWindowText(strSourceFile);
		m_txtLineNumber.SetWindowText(strLineInfo);
	}
	catch (std::exception& error)
	{
		CString strProjectTitle;
		strProjectTitle.LoadString(IDS_PROJECTTITLE);
		MessageBox(CA2CT(error.what()), strProjectTitle, MB_OK | MB_ICONERROR);
	}
}