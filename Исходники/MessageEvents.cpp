STDMETHODIMP CExtImpl::OnRead(IExchExtCallback* peecb)
{
	HWND hwnd;

	peecb->GetWindow(&hwnd);
	if (!hwnd)
		hwnd = GetTopWindow(NULL);

	switch (_context)
	{
	case EECONTEXT_SENDNOTEMESSAGE:
		{
			BOOL fAddButtons = TRUE;
			int nNumButtons;
			int nIndex;
			TBBUTTON tbbNew[5];
			TBBUTTON tbbCheck;
			
			// Check to make sure the buttons aren't already on the toolbar

			nNumButtons = SendMessage(_hwndSendToolbar, TB_BUTTONCOUNT, 0, 0);
			for (nIndex=0; nIndex<nNumButtons; nIndex++)
			{
				SendMessage(_hwndSendToolbar, TB_GETBUTTON, (WPARAM) nIndex, 
							(LPARAM) &tbbCheck);

				// If a button exists with the same bitmap ID and command ID
				// as the Encrypt button, odds are good that the button is
				// already on the toolbar
				if ((tbbCheck.iBitmap == (int)_itbmEncrypt) && 
					(tbbCheck.idCommand == (int)_cmdidEncrypt))
				{
					fAddButtons = FALSE;
					nIndex = nNumButtons;
				}
			}

			if (fAddButtons)
			{
				tbbNew[0].iBitmap = 0;
				tbbNew[0].idCommand = 0;
				tbbNew[0].fsState = 0;
				tbbNew[0].fsStyle = TBSTYLE_SEP;
				tbbNew[0].dwData = 0;
				tbbNew[0].iString = -1;
			
				tbbNew[1].iBitmap = _itbmEncrypt;
				tbbNew[1].idCommand = _cmdidEncrypt;
				tbbNew[1].fsState = TBSTATE_ENABLED;
				tbbNew[1].fsStyle = TBSTYLE_CHECK;
				tbbNew[1].dwData = 0;
				tbbNew[1].iString = -1;
			
				tbbNew[2].iBitmap = _itbmSign;
				tbbNew[2].idCommand = _cmdidSign;
				tbbNew[2].fsState = TBSTATE_ENABLED;
				tbbNew[2].fsStyle = TBSTYLE_CHECK;
				tbbNew[2].dwData = 0;
				tbbNew[2].iString = -1;

				tbbNew[3].iBitmap = 0;
				tbbNew[3].idCommand = 0;
				tbbNew[3].fsState = 0;
				tbbNew[3].fsStyle = TBSTYLE_SEP;
				tbbNew[3].dwData = 0;
				tbbNew[3].iString = -1;
			
				tbbNew[4].iBitmap = _itbmPgpKeys;
				tbbNew[4].idCommand = _cmdidPgpKeys;
				tbbNew[4].fsState = TBSTATE_ENABLED;
				tbbNew[4].fsStyle = TBSTYLE_BUTTON;
				tbbNew[4].dwData = 0;
				tbbNew[4].iString = -1;
			
				SendMessage(_hwndSendToolbar, TB_ADDBUTTONS, 5, 
					(LPARAM) tbbNew);
			}
		}
		break;

    case EECONTEXT_SENDPOSTMESSAGE:
		break;
    
	case EECONTEXT_READNOTEMESSAGE:
		{
			BOOL fAddButtons = TRUE;
			int nNumButtons;
			int nIndex;
			TBBUTTON tbbNew[5];
			TBBUTTON tbbCheck;
			BOOL FYEO;

			// Check to make sure the buttons aren't already on the toolbar

			nNumButtons = SendMessage(_hwndReadToolbar, TB_BUTTONCOUNT, 0, 0);
			for (nIndex=0; nIndex<nNumButtons; nIndex++)
			{
				SendMessage(_hwndReadToolbar, TB_GETBUTTON, 
							(WPARAM) nIndex, (LPARAM) &tbbCheck);

				// If a button exists with the same bitmap ID and command ID
				// as the Decrypt button, odds are good that the button is
				// already on the toolbar
				if ((tbbCheck.iBitmap == (int)_itbmDecrypt) && 
					(tbbCheck.idCommand == (int)_cmdidDecrypt))
				{
					fAddButtons = FALSE;
					nIndex = nNumButtons;
				}
			}

			if (fAddButtons)
			{
				tbbNew[0].iBitmap = 0;
				tbbNew[0].idCommand = 0;
				tbbNew[0].fsState = 0;
				tbbNew[0].fsStyle = TBSTYLE_SEP;
				tbbNew[0].dwData = 0;
				tbbNew[0].iString = -1;
			
				tbbNew[1].iBitmap = _itbmDecrypt;
				tbbNew[1].idCommand = _cmdidDecrypt;
				tbbNew[1].fsState = TBSTATE_ENABLED;
				tbbNew[1].fsStyle = TBSTYLE_BUTTON;
				tbbNew[1].dwData = 0;
				tbbNew[1].iString = -1;
			
				tbbNew[2].iBitmap = 0;
				tbbNew[2].idCommand = 0;
				tbbNew[2].fsState = 0;
				tbbNew[2].fsStyle = TBSTYLE_SEP;
				tbbNew[2].dwData = 0;
				tbbNew[2].iString = -1;
			
				tbbNew[3].iBitmap = _itbmPgpKeys;
				tbbNew[3].idCommand = _cmdidPgpKeys;
				tbbNew[3].fsState = TBSTATE_ENABLED;
				tbbNew[3].fsStyle = TBSTYLE_BUTTON;
				tbbNew[3].dwData = 0;
				tbbNew[3].iString = -1;
			
				SendMessage(_hwndReadToolbar, TB_ADDBUTTONS, 4, 
					(LPARAM) tbbNew);
			}

			IMAPISession* psess;

			HRESULT hr = peecb->GetSession(&psess, NULL);
			if (FAILED(hr))
			{
				UIDisplayStringID(hwnd, IDS_E_NOSESSION);
				return S_FALSE;
			}
			
			if (AutoDecrypt(_memoryMgr))
			{
				IMessage *pmsg = 0;
				STATSTG StreamStats;
				DWORD dwInSize;
				UINT nOutSize;
				char *pInput;
				char *pOutput = NULL;
				BOOL bGotHTML = FALSE;
				PGPError nError = kPGPError_NoErr;
				char szFile[256];
				char szName[256];

				UIGetString(szName, sizeof(szName), IDS_LOGNAME);
				UIGetString(szFile, sizeof(szFile), IDS_DLL);
				
				CWaitCursor wait; // Mark busy
				
				hr = peecb->GetObject(NULL, (IMAPIProp**)&pmsg);
				if (FAILED(hr))
				{
					return S_FALSE;
				}
				
				IStream *pstrmBody = 0;

				hr = pmsg->OpenProperty(PR_BODY_HTML, &IID_IStream, 
					STGM_READWRITE, MAPI_MODIFY, (IUnknown**)&pstrmBody);
				
				if (FAILED(hr))
				{
					hr = pmsg->OpenProperty(PR_BODY, &IID_IStream, 
						STGM_READWRITE, MAPI_MODIFY, (IUnknown**)&pstrmBody);
				}
				else
					bGotHTML = TRUE;

				if (FAILED(hr))
				{
					pmsg->Release();
					psess->Release();
					return S_FALSE;
				}
				
				pstrmBody->Stat(&StreamStats, STATFLAG_NONAME);
				dwInSize = StreamStats.cbSize.LowPart;
				
				pInput = (char *) calloc(dwInSize+1, sizeof(char));
				if (!pInput)
				{
					UIDisplayStringID(hwnd, IDS_E_NOMEMORY);
					pstrmBody->Release();
					pmsg->Release();
					psess->Release();
					return S_FALSE;
				}
				pstrmBody->Read(pInput, dwInSize, &dwInSize);
				pInput[dwInSize] = 0;
				
				if (AutoDecrypt(_memoryMgr))
				{
					nError = DecryptVerifyBuffer(UIGetInstance(), hwnd, 
								_pgpContext, _tlsContext, szName, 
								szFile, pInput, dwInSize, 
								FALSE, (VOID ** )&pOutput, &nOutSize, &FYEO);

					if (IsntPGPError(nError) && (nOutSize > 0) && 
						(pOutput != NULL))
					{
						LARGE_INTEGER li = {0,0};
						ULARGE_INTEGER uli = {nOutSize, 0};
						BOOL fPartied;
						char *szBuffer = NULL;
						
						// Alter only the block of encrypted/signed text
						// if this is not HTML

						if((FYEO)||(GetSecureViewerPref(_pgpContext)))
						{
							TempestViewer((void *)_pgpContext,hwnd,
								pOutput,nOutSize,FYEO);
						}
						else
						{
							szBuffer = (char *) calloc(dwInSize+nOutSize+1, 
													sizeof(char));

							strcpy(szBuffer, pOutput);

							if (strlen(szBuffer) > 0)
							{
								uli.LowPart = strlen(szBuffer);
								pstrmBody->Seek(li, STREAM_SEEK_SET, NULL);
								pstrmBody->Write(szBuffer, strlen(szBuffer), 
											NULL);
								pstrmBody->SetSize(uli);
								pstrmBody->Commit(STGC_DEFAULT);
								pstrmBody->Release();
								RTFSync(pmsg, RTF_SYNC_BODY_CHANGED, 
									&fPartied);
							}
	
							free(szBuffer);
						}

						PGPFreeData(pOutput);
					}
					else
						pstrmBody->Release();
				}
				else
					pstrmBody->Release();

				free(pInput);
				pmsg->Release();
			}
			
			psess->Release();
		}
		break;

	case EECONTEXT_READPOSTMESSAGE:
		break;

	default:
		// This way, the function defends itself against unknown future
		// variants, as FindREOnNote is less robust than it might be.
		return S_FALSE;
	}

	return S_FALSE;
}