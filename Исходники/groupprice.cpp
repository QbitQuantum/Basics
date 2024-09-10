long CGroupPrice::_OptionsProc(ULONG ulFunction, DBA_KEY *pDbaKey, DBA_OPTIONS_FILTER_RECORD *pDbaRec, DWORD dwStatus) 
{
	if (ulFunction == DBA_TERMINATE_STREAM_FUNCTION || m_bTerminate)
	{
		SetEvent(m_hTerminateGroupOption);
		return TRUE;
	}

	if (dwStatus == DBA_ERR_NO_ERROR)
	{
#ifdef __PERFMON
		if(m_spGlobalPerfCounter!=NULL)
			m_spGlobalPerfCounter->AddGroupRequestResponce();
		if(m_pPerfMon)
			m_pPerfMon->AddGroupRequestResponce();
#endif // __PERFMON


		if(_IsOurOptionExchange(pDbaKey->exchangeCode[0]))
		{
			_QuoteUpdateParams Params;
			ParamFromKey(*pDbaKey, enOPT, Params);

			CHahedKeyStringPtr pHashedKey = CHahedKeyStringPtr(new CHahedKeyString(pDbaKey));


			if(enGroupRequestLastQuote != m_enRequestType)
				EgLib::CEgLibTraceManager::Trace(LogSubsExt, __FUNCTION__, _T("[%s]\t Group Option Subscribe %s"), m_strUserName.c_str(), pHashedKey->GetKeyString().c_str()); 
			else
				EgLib::CEgLibTraceManager::Trace(LogSubsExt, __FUNCTION__, _T("[%s]\t Group Option Get %s"), m_strUserName.c_str(), pHashedKey->GetKeyString().c_str()); 

			//StoreClosePrice(pHashedKey, );
			//EgLib::CEgLibTraceManager::Trace(LogCustom, __FUNCTION__, _T("[%s]\t Group Option Close Price Set %s"), m_strUserName.c_str(), pHashedKey->GetKeyString().c_str()); 

			m_bIsGotOptions = true;

			if(enGroupRequestLastQuote != m_enRequestType)
			{
				if(m_bsUndSymbol.length())
				{
					CAutoLock lk(m_csGroupSubscript);
					m_mapGroupSubscript[m_bsUndSymbol].insert(pHashedKey);
				}

				CSubscriptionInfoPtr pSubscription = AddSubscription(pHashedKey, enOPT);
				pSubscription->SetClosePrice(pDbaRec->priceRec.dbaRec.close.price);

				if(enGroupRequestAllNotify == m_enRequestType)
				{
					CSubscribedResponsePtr pResponse = CSubscribedResponsePtr(new CSubscribedResponse(Params));
					PublicResponse(boost::shared_dynamic_cast<CResponseBase>(pResponse));
				}
				CDBARecordPtr pRecData =  CDBARecordPtr(new DBA_RECORD_3);
				memcpy(pRecData.get(), &pDbaRec->priceRec.dbaRec, sizeof(DBA_RECORD_3));

				pSubscription->AssignData(pRecData);
				PostIntoRealtimeMessageProcessor(pSubscription);

				pRecData = pSubscription->GetData();
				PublicLastQuote(&Params, pRecData);
			}
			
			if(enGroupRequestSubscribe != m_enRequestType && enGroupRequestAllNotify != m_enRequestType)
			{
				CDBARecordPtr pRec = CDBARecordPtr(new DBA_RECORD_3);
				if(pRec!=NULL)
				{
					memcpy(pRec.get(), &pDbaRec->priceRec.dbaRec, sizeof(DBA_RECORD_3));
					PublicLastQuote(&Params, pRec);
				}
			}
		}
		else
		{
			if(enGroupRequestLastQuote != m_enRequestType)
				m_NeedToUnsubscribe.push_back(CHahedKeyStringPtr(new CHahedKeyString(pDbaKey)));
		}
		return FALSE;
	}
	else 
	{
		CErrorResponsePtr pError(new CErrorResponse());
		pError->m_vtRequest = m_vtRequest;			
		if(enGroupRequestLastQuote != m_enRequestType)
		{
			pError->m_enRequestType = enSubscribeQuote;
			if(dwStatus == DBA_ERR_KEY_NOT_FOUND)
			{
				pError->m_bstrDescription = L"Unable to subscribe underlying options.";
				pError->m_Error = enNoDataAvailableForSymbol;
			}
			else if(dwStatus == DBA_ERR_INTEREST)
			{
				pError->m_bstrDescription = L"HyperFeed server subscription list is full";
				pError->m_Error = enProviderInternalError;
			}
			else
			{
				_bstr_t bs =  "Unable to get underlying options. Error: ";
				bs += EtGetMessage(DBA_ERROR,dwStatus);
				TCHAR buffer[0x100] = {0};				
				_ltot(dwStatus,buffer,10);
				bs += " (";
				bs += buffer;
				bs += ")";
				pError->m_bstrDescription = bs;
				pError->m_Error = enProviderInternalError;
			}
			EgLib::CEgLibTraceManager::Trace(LogError, __FUNCTION__ , _T("[%s]\t %s"), m_strUserName.c_str(), (LPCSTR)pError->m_bstrDescription);

		}
		else
		{
			pError->m_enRequestType = enRequestLastQuote;
			if(dwStatus == DBA_ERR_KEY_NOT_FOUND)
			{
				pError->m_bstrDescription = L"Couldn't get options prices for underlying. Unknown symbol.";
				pError->m_Error = enNoDataAvailableForSymbol;
			}
			else
			{
				_bstr_t bs =  "Couldn't get options prices for underlying. Error: ";
				bs += EtGetMessage(DBA_ERROR,dwStatus);
				TCHAR buffer[0x100] = {0};				
				_ltot(dwStatus,buffer,10);
				bs += " (";
				bs += buffer;
				bs += ")";
				pError->m_bstrDescription = bs;
				pError->m_Error = enProviderInternalError;
			}
		}
		CResponseBasePtr pErrorPtr = boost::shared_dynamic_cast<CResponseBase>(pError);
		PublicResponse(pErrorPtr);
		m_bIsGotError = true;
		EgLib::CEgLibTraceManager::Trace(LogError, __FUNCTION__ , _T("[%s]\t %s"), m_strUserName.c_str(), (LPCSTR)pError->m_bstrDescription);

	}

	return FALSE;
}