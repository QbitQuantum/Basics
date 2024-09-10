/**
 * @param strModule - module file name.
 * @return pointer to module processor.
 */
boost::shared_ptr<CBaseProcessor> CExpressModeDlg::GetModuleInfo(const CString& strModule)
{
	boost::shared_ptr<CBaseProcessor> pBaseProcessor;
	if (strModule.IsEmpty())
		return pBaseProcessor;
	CModuleMap::iterator itModule = m_mapModules.find(strModule);
	if (itModule == m_mapModules.end())
	{
		if (m_pXMLNodeProcess != NULL)
		{
			CString strExpression;
			strExpression.Format(_T("./modules/module[name=\"%s\"]"), strModule);
			CComPtr<IXMLDOMNode> pXMLNodeModule;
			if (SelectXMLNode(m_pXMLNodeProcess, CT2CW(strExpression), pXMLNodeModule))
			{
				CString strBaseAddress;
				GetXMLNodeText(pXMLNodeModule, OLESTR("./base"), strBaseAddress);
				PVOID ptrBaseAddress = (PVOID)_tcstoui64(strBaseAddress, NULL, 0);
				CString strModuleSize;
				GetXMLNodeText(pXMLNodeModule, OLESTR("./size"), strModuleSize);
				DWORD dwModuleSize = _tcstoul(strModuleSize, NULL, 0);
				if (ptrBaseAddress != NULL && dwModuleSize != 0)
				{
					TCHAR szModuleName[MAX_PATH];
					_tcscpy_s(szModuleName, countof(szModuleName), PathFindFileName(strModule));
					TCHAR szMapPdbFolder[MAX_PATH];
					m_txtMapPdbFolder.GetWindowText(szMapPdbFolder, countof(szMapPdbFolder));
					TCHAR szSystemFolder[MAX_PATH];
					GetSystemDirectory(szSystemFolder, countof(szSystemFolder));
					TCHAR szMapPdbFile[MAX_PATH];
					if (! FindFileByPattern(szMapPdbFolder, szModuleName, _T(".map"), szMapPdbFile) &&
						! FindFileByPattern(szMapPdbFolder, szModuleName, _T(".pdb"), szMapPdbFile) &&
						! FindFileByPattern(szSystemFolder, szModuleName, _T(".map"), szMapPdbFile) &&
						! FindFileByPattern(szSystemFolder, szModuleName, _T(".pdb"), szMapPdbFile))
					{
						return pBaseProcessor;
					}
					CBaseProcessor::PROCESSED_FILE_TYPE eProcessedFileType = CBaseProcessor::GetFileType(szMapPdbFile);
					switch (eProcessedFileType)
					{
					case CBaseProcessor::PFT_MAP:
						{
							CMapProcessor* pMapProcessor = STATIC_DOWNCAST(CMapProcessor, m_pMapProcessor.get());
							if (pMapProcessor == NULL)
							{
								pMapProcessor = new CMapProcessor();
								pBaseProcessor.reset(pMapProcessor);
							}
							pBaseProcessor = m_pMapProcessor;
							pMapProcessor->LoadMapText(szMapPdbFile);
							pMapProcessor->SetBaseAddress(ptrBaseAddress);
						}
						break;
					case CBaseProcessor::PFT_PDB:
						{
							CPdbProcessor* pPdbProcessor = STATIC_DOWNCAST(CPdbProcessor, m_pPdbProcessor.get());
							if (pPdbProcessor == NULL)
							{
								pPdbProcessor = new CPdbProcessor();
								m_pPdbProcessor.reset(pPdbProcessor);
							}
							pBaseProcessor = m_pPdbProcessor;
							pPdbProcessor->LoadModule(szMapPdbFile, ptrBaseAddress, dwModuleSize);
						}
						break;
					}
					if (pBaseProcessor.get() != NULL)
						m_mapModules.insert(CModuleMap::value_type(strModule, pBaseProcessor));
				}
			}
		}
	}
	else
		pBaseProcessor = itModule->second;
	return pBaseProcessor;
}