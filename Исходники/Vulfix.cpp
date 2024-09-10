HRESULT WINAPI ExpressScanLeak(IVulCollection **pVulCollection, DWORD dwFlags, BOOL bQuickScan)
{
	TIME_CHECK( _T("ExpressScanLeak ") );

	ATLASSERT(pVulCollection);
	CVulCollection *pCollection = new CImplIUnkownT<CVulCollection>;
	
	BOOL bFoundSysVuls = FALSE;
	IVulfix *pscan = new CImplVulfix;
	dwFlags |= VULSCAN_EXPRESS_SCAN;
	
	if( bQuickScan && RequireUsingInterface() )
		// Vista 进行快速扫描 
	{
		pCollection->m_nStatus = pscan->ExpressScanSystem();
		pCollection->m_statusValid = TRUE;
		bFoundSysVuls = pCollection->m_nStatus>0;
	}
	else
	{
		pCollection->m_statusValid = FALSE;
		if( SUCCEEDED( pscan->Scan(dwFlags) ))
		{
			const CSimpleArray<LPTUpdateItem> &arr = pscan->GetResults();
			for(int i=0; i<arr.GetSize(); ++i)
			{
				LPTUpdateItem pLeak = arr[i];

#ifdef _DEBUG
				_tcprintf(_T("-Quick.VUL %d %2d %s \n"), pLeak->nID, pLeak->nWarnLevel, pLeak->strName);
#endif
				if( pLeak->isIgnored || pLeak->nWarnLevel<=0 || pLeak->isExclusive )
					continue;
				
				TOverviewItem item;
				item.nLeakType = VTYPE_WINDOWS;
				item.nID = pLeak->nID;
				item.nLeakLevel = pLeak->nWarnLevel;
				item.dwFlags = pLeak->dwVFlags;
				item.strTitle = pLeak->strName;
				item.strDescription = pLeak->strDescription;
				item.strPubDate = pLeak->strPubdate;
				pCollection->leaks.Add( item );
			}
		}
		bFoundSysVuls = pCollection->leaks.GetSize()>0;

		// 如果没有找到系统漏洞, 则搜索软件漏洞 
		if(!bFoundSysVuls)
		{
			const CSimpleArray<LPTVulSoft> &arr = pscan->GetSoftVuls();
			for(int i=0; i<arr.GetSize(); ++i)
			{
				LPTVulSoft psoft = arr[i];
#ifdef _DEBUG
				_tcprintf(_T("-Quick.SOFT %d %2d %s \n"), psoft->nID, psoft->nLevel, psoft->strName);
#endif
				if(psoft->isIgnored || psoft->state.comState==COM_ALL_DISABLED)
					continue;

				TOverviewItem item;
				item.nLeakType = VTYPE_SOFTLEAK;
				item.nID = psoft->nID;
				item.nLeakLevel = psoft->nLevel;
				item.dwFlags = 0;
				item.strTitle = psoft->strName;
				item.strDescription = psoft->strDescription;
				item.strPubDate = psoft->strPubdate;
				pCollection->leaks.Add( item );
			}
		}
	}
	delete pscan;
	*pVulCollection = pCollection;
	return S_OK;
}