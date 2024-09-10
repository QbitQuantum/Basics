BOOL CSNMP::SnmpQueryTable( LPCTSTR apColumnOidList[], UINT nListLen, std::vector<std::pair<CString, std::vector<AsnAny>>> *pTable )
{
	if (!apColumnOidList || !pTable)
	{
		m_strLastError = L"[SnmpQueryTable] : Verify the arguments failed. ";
		return FALSE;
	}

	pTable->clear();

	if (!nListLen)
		return TRUE;

	typedef std::map<CString, AsnAny> RELATIVE_OID_TO_VALUE_MAP;

	std::vector<RELATIVE_OID_TO_VALUE_MAP> vColumnRelativeOidToValue(nListLen);

	SnmpVarBindList CurrentVarBindList;
	CurrentVarBindList.len = 0;
	CurrentVarBindList.list = NULL;

	AsnObjectIdentifier TargetObjectIdentifier;
	TargetObjectIdentifier.idLength = 0;
	TargetObjectIdentifier.ids = NULL;

	BOOL bRes = FALSE;
	do 
	{
		UINT i = 0;
		for (; i < nListLen; i++)
		{
			SnmpUtilVarBindListFree(&CurrentVarBindList);

			CurrentVarBindList.len = 1;
			CurrentVarBindList.list = (SnmpVarBind *)SnmpUtilMemAlloc(sizeof(SnmpVarBind));
			CurrentVarBindList.list->name.idLength = 0;
			CurrentVarBindList.list->name.ids = NULL;
			CurrentVarBindList.list->value.asnType = ASN_NULL;

#ifdef _UNICODE
			CStringA strOIDA = XLibS::StringCode::ConvertWideStrToAnsiStr(apColumnOidList[i]); 
#else
			CStringA strOIDA = apColumnOidList[i];
#endif

			if(!::SnmpMgrStrToOid(strOIDA.GetBuffer(), &CurrentVarBindList.list->name) || !CurrentVarBindList.list->name.ids || !CurrentVarBindList.list->name.idLength)
			{

#ifdef _UNICODE
				CStringW strOIDW = apColumnOidList[i];
#else
				CStringW strOIDW = XLibS::StringCode::ConvertAnsiStrToWideStr(apColumnOidList[i]);
#endif
				m_strLastError.Format(L"[SnmpQueryTable] : Bad OID string \"%s\". ", (LPCWSTR)strOIDW);

				strOIDA.ReleaseBuffer();

				break;
			}
			strOIDA.ReleaseBuffer();

			SnmpUtilOidFree(&TargetObjectIdentifier);
			TargetObjectIdentifier.idLength = 0;
			TargetObjectIdentifier.ids = NULL;

			if (!SnmpUtilOidCpy(&TargetObjectIdentifier, &CurrentVarBindList.list->name) || !TargetObjectIdentifier.ids || !TargetObjectIdentifier.idLength)
			{
				m_strLastError.Format(L"[SnmpQueryTable] : Copy OID failed. ");
				break;
			}

			BOOL bFailFlag = FALSE;
			while(1)
			{
				AsnInteger nSNMPErrorCode = 0;
				AsnInteger nSNMPErrorIndex = 0;
				if(!::SnmpMgrRequest(m_SnmpSession, SNMP_PDU_GETNEXT, &CurrentVarBindList, &nSNMPErrorCode, &nSNMPErrorIndex))
				{
					DWORD dwLastWinError = ::GetLastError();
					assert(nSNMPErrorIndex == 0);

					const WCHAR * SNMP_ERROR_MESSAGE[] = { L"The agent reports that no errors occurred during transmission. ", 
						L"The agent could not place the results of the requested operation into a single SNMP message. ", 
						L"The requested operation identified an unknown variable. ", 
						L"The requested operation tried to change a variable but it specified either a syntax or value error. ", 
						L"The requested operation tried to change a variable that was not allowed to change according to the community profile of the variable. "
					};

					const WCHAR * WIN_ERROR_MESSAGE[] = {L"The request timed-out.",
						L"Unexpected error file descriptors indicated by the Windows Sockets select function."
					};

					const WCHAR *pSNMPError = NULL;
					if (nSNMPErrorIndex < ARRAYSIZE(SNMP_ERROR_MESSAGE))
						pSNMPError = SNMP_ERROR_MESSAGE[nSNMPErrorIndex];
					else
						pSNMPError = L"Unknown error. ";

					const WCHAR *pWinError = NULL;
					if (dwLastWinError - 40 < ARRAYSIZE(WIN_ERROR_MESSAGE))
						pWinError = WIN_ERROR_MESSAGE[dwLastWinError - 40];
					else
						pWinError = L"Unknown error. ";

					m_strLastError.Format(L"SNMP requesting failed. SNMP ERROR : %s (%ld). WIN ERROR : %s (%lu). ", 
						pSNMPError, nSNMPErrorIndex, pWinError, dwLastWinError);
	
//					LPCWSTR pSysError = NULL;
//					m_strLastError.Format(L"SNMP requesting failed. SNMP ERROR : %s (%ld). ", pError, nErrorIndex);
//					if (::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM, 
//						NULL, dwLastError, 0, (LPTSTR)&pSysError, 0, NULL) && pSysError)
//					{
//						m_strLastError.AppendFormat(L"Windows ERROR: %s (%lu). ", pSysError, dwLastError);
//
//						::LocalFree((HLOCAL)pSysError);
//						pSysError = NULL;
//					}

					
					bFailFlag = TRUE;
					break;
				}

				assert(SNMP_ERRORSTATUS_NOERROR == nSNMPErrorCode);
				
				if (!CurrentVarBindList.list || (!CurrentVarBindList.list->name.ids && CurrentVarBindList.list->name.idLength))
				{
#ifdef _UNICODE
					CStringW strOIDW = apColumnOidList[i];
#else
					CStringW strOIDW = XLibS::StringCode::ConvertAnsiStrToWideStr(apColumnOidList[i]);
#endif
					m_strLastError.Format(L"[SnmpQueryTable] : GetNext returned a bad OID during the request for %s. ", (LPCWSTR)strOIDW);

					bFailFlag = TRUE;
					break;
				}

				if (CurrentVarBindList.list->name.idLength < TargetObjectIdentifier.idLength)
					break;

				if (SnmpUtilOidNCmp(&CurrentVarBindList.list->name, &TargetObjectIdentifier, TargetObjectIdentifier.idLength))
					break;

				CStringA strOIDTarget = ThreadSafeSnmpUtilOidToA(&TargetObjectIdentifier);
				CStringA strOIDCurrent = ThreadSafeSnmpUtilOidToA(&CurrentVarBindList.list->name);

				assert(strOIDCurrent.Find(strOIDTarget) == 0);



				AsnAny value;
				SnmpUtilAsnAnyCpy(&value, &CurrentVarBindList.list->value);

#ifdef _UNICODE
				CString strRelativeOID = 
					XLibS::StringCode::ConvertAnsiStrToWideStr(strOIDCurrent.Mid(strOIDTarget.GetLength()));
#else
				CString strRelativeOID = strOIDCurrent.Mid(strOIDTarget.GetLength());
#endif

				vColumnRelativeOidToValue[i].insert(std::make_pair(strRelativeOID, value));
			}
			if (bFailFlag)
				break;

		}

		if (i < nListLen)
			break;

		const RELATIVE_OID_TO_VALUE_MAP & FirstCol = vColumnRelativeOidToValue[0];
		for (RELATIVE_OID_TO_VALUE_MAP::const_iterator itFirstCol = FirstCol.begin();
			itFirstCol != FirstCol.end(); itFirstCol++)
		{
			std::vector<RELATIVE_OID_TO_VALUE_MAP::const_iterator> vItFind;

			UINT i = 1;
			for (; i < nListLen; i++)
			{
				const RELATIVE_OID_TO_VALUE_MAP & CurrentCol = 
					vColumnRelativeOidToValue[i];

				RELATIVE_OID_TO_VALUE_MAP::const_iterator itFind =
					 CurrentCol.find(itFirstCol->first);

				if (itFind == CurrentCol.end())
					break;

				vItFind.push_back(itFind);
			}

			if (i < nListLen)
				continue;

			pTable->push_back(make_pair(itFirstCol->first, std::vector<AsnAny>(1, itFirstCol->second)));

			for (std::vector<RELATIVE_OID_TO_VALUE_MAP::const_iterator>::size_type i = 0;
				i < vItFind.size(); i++)
			{
				pTable->back().second.push_back(vItFind[i]->second);
			}
		}

		bRes = TRUE;

	} while (FALSE);

	SnmpUtilOidFree(&TargetObjectIdentifier);
	SnmpUtilVarBindListFree(&CurrentVarBindList);

	if (!bRes)
	{
		ClearQueryTableResult(*pTable);
		pTable->clear();
	}

	return bRes;
}