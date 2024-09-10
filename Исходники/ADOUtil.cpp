void CADOUtil::RunSP_ReturnRS(_bstr_t SP_Name, _RecordsetPtr& out_pRs, CParamArray *ParamArray)
{
	if(!CheckCurrentProcess())
		throw ERR_NEW_PROCESS_DETECTED;

	_ConnectionPtr	pConn	= NULL;
	_ParameterPtr	pPrm	= NULL;
	_ParameterPtr	pprm	= NULL;
	ErrorPtr		pErr	= NULL;
	_CommandPtr		pComm	= NULL;
	CParam*			pr		= NULL;
	LONG			ErrSQLState = 0;
	LONG			count = 0;
	LONG			ErrorCode = 0;
	_variant_t		vIndex;
	_bstr_t			bsEmpty;

	//********************************************************************
	//Connectin to Pool
	try 
	{
		_bstr_t bstrConnString(szConnectionString);
		pConn.CreateInstance(__uuidof(Connection));
		if(pConn == NULL)
		{
			throw(ErrorCode = ERR_UNABLE_CREATE_CONN);
		}
		pConn->ConnectionTimeout = 7;
		pConn->Open(bstrConnString, L"", L"", adConnectUnspecified);
	}
	catch(...)
	{
		Beep(2000, 100);
		//m_ExternalLink.Add2Log(WL_ERROR_LEVEL1,"Unable set connection to SQL Error = Unknown");
		ErrorCode = ERR_UNABLE_CREATE_CONN;
	}

	if(ErrorCode)
		throw ErrorCode;

	//*******************************************************************	
	//Execut command
	try
	{
		pComm.CreateInstance(__uuidof(Command));
		if(pComm == NULL)
		{
			throw(ErrorCode = ERR_UNABLE_CREATE_COMM);
		}
		out_pRs.CreateInstance(__uuidof(Recordset));
		if(out_pRs == NULL)
		{
			throw(ErrorCode = ERR_UNABLE_CREATE_RECSET);
		}
		pComm->ActiveConnection = pConn;
		pComm->CommandText = SP_Name;
		pComm->CommandType = adCmdStoredProc;

		if(ParamArray != NULL)
		{
			DWORD Count = ParamArray->GetSize();
			for (DWORD i=0; i < Count; i++)
			{
				pr = (*ParamArray)[i];
				pprm = pComm->CreateParameter(bsEmpty, pr->Type, pr->Direction, pr->Size, pr->Value);
				pComm->Parameters->Append(pprm);
			}
		}
		out_pRs->CursorLocation = adUseClient;
		out_pRs->Open(_variant_t((IDispatch *)pComm, true), vtMissing, adOpenForwardOnly, adLockReadOnly, NULL);
		out_pRs->PutRefActiveConnection(NULL);
		pConn->Close();
		return;
	}

	//Handle Execut error
	catch(_com_error)
	{
		try
		{
			count = pConn->Errors->Count;
			if(count)
			{
				vIndex = _variant_t((LONG)0);
				pErr = pConn->Errors->GetItem(vIndex);
				ErrSQLState = atol((LPCSTR)pErr->SQLState);
				/*
				//m_ExternalLink.Add2Log(WL_ERROR_LEVEL3,
				"SQL (RS) Error %d [Error #%d Description \"%s\" (Source: %s)"
				"(SQL State: %s)](NativeError: %s)",
				e.Error(),
				pErr->Number,
				(LPCSTR)pErr->Description,
				(LPCSTR)pErr->Source,
				(LPCSTR)pErr->SQLState,
				(LPCSTR)pErr->NativeError);*/

			}
			pConn->Close();
			if (pComm->ActiveConnection != NULL)
			{
				pComm->PutRefActiveConnection(NULL);
			}
		}
		catch(...)
		{
			ErrSQLState = 1;
		}
	}
	catch(long errorCode)
	{
		//m_ExternalLink.Add2Log(WL_ERROR_LEVEL3,"SQL (RS) Error Unable Create Command object");
		pConn->Close();
		throw(errorCode);
	}
	catch(...)
	{
		//m_ExternalLink.Add2Log(WL_ERROR_LEVEL3,"SQL (RS) Error Unknown");
		ErrSQLState = 1;
	}

	if(ErrSQLState)
	{
		switch(ErrSQLState)
		{
		case 23000: //Violation of PRIMARY KEY constraint
			throw (ErrorCode = ERR_PRIMARY_KEY_CONSTRAINT);
			break;
		default: //Code
			throw (ErrorCode = ERR_SQL_UNKNOWN_PROBLEM);
			break;
		}
	}
}