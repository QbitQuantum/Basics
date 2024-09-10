/*! 
  \brief Opens the wan (dialup, vpn...) adapter.
  \return If the function succeeds, the return value is the pointer to a properly initialized WAN_ADAPTER structure,
   otherwise the return value is NULL.
*/
PWAN_ADAPTER WanPacketOpenAdapter()
{
	PWAN_ADAPTER pWanAdapter = NULL;
	PBLOB_TABLE pBlobTable = NULL;
	HBLOB hFilterBlob = NULL;
	HRESULT hResult;
	DWORD i;

	if ( g_hModule == NULL)
	{
		g_hModule = LoadLibrary("npp\\ndisnpp.dll");
	}

	if ( g_hModule == NULL)
	{
		return NULL;
	}

	hResult = CoInitialize(NULL);

	//
 	// if  the calling thread has already initialized COM with a 
 	// different threading model, we have this error
 	// however, we are able to support another threading model,
 	// so we try to initialize COM with another threading model.
 	// This new call should succeed with S_FALSE.
 	//
 	if (hResult == RPC_E_CHANGED_MODE)
	{
		hResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	
		//MULTITHREADED threading is only supported on Windows 2000
		if (hResult == RPC_E_CHANGED_MODE && IsWindows2000())
		{
			hResult = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		}
	}

	if (hResult != S_OK && hResult != S_FALSE)
		return NULL;

	pWanAdapter = (PWAN_ADAPTER)GlobalAlloc(GPTR, sizeof (WAN_ADAPTER));

	if ( pWanAdapter == NULL )
		goto error;
	
	memset(pWanAdapter, 0, sizeof(WAN_ADAPTER));
	
	if ( CreateBlob(&hFilterBlob) != NMERR_SUCCESS )
	{
		goto error;
	}
	
	if ( SetBoolInBlob(hFilterBlob, OWNER_NPP, CATEGORY_CONFIG, TAG_INTERFACE_REALTIME_CAPTURE, TRUE) != NMERR_SUCCESS )
	{
		DestroyBlob( hFilterBlob);
		goto error;
	}

	if ( SetBoolInBlob(hFilterBlob, OWNER_NPP, CATEGORY_LOCATION, TAG_RAS, TRUE) != NMERR_SUCCESS )
	{
		DestroyBlob( hFilterBlob);
		goto error;
	}

	if ( GetNPPBlobTable(hFilterBlob, &pBlobTable) != NMERR_SUCCESS )
	{
		DestroyBlob( hFilterBlob);
		goto error;
	}

	DestroyBlob (hFilterBlob);

	if ( pBlobTable->dwNumBlobs == 0 || pBlobTable->dwNumBlobs > 1)
	{
		///fixme.....
		for ( i = 0 ; i < pBlobTable->dwNumBlobs ; i++ )
			DestroyBlob(pBlobTable->hBlobs[i]);
		
		GlobalFree(pBlobTable);
		goto error;
	}

	pWanAdapter->hCaptureBlob = pBlobTable->hBlobs[0];

	GlobalFree(pBlobTable);

	InitializeCriticalSection(&pWanAdapter->CriticalSection);

	pWanAdapter->hReadEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if ( pWanAdapter->hReadEvent == NULL )
		goto error;

	pWanAdapter->MemEx.buffer = (PUCHAR)GlobalAlloc(GPTR, DEFAULT_MEM_EX_SIZE);
	if (pWanAdapter->MemEx.buffer == NULL)
		goto error;
	
	pWanAdapter->MemEx.size = DEFAULT_MEM_EX_SIZE;
	pWanAdapter->Tme.active = TME_NONE_ACTIVE;

	if (CreateNPPInterface(pWanAdapter->hCaptureBlob, IID_IRTC, (void**) &pWanAdapter->pIRTC) == NMERR_SUCCESS && pWanAdapter->pIRTC != NULL) 
	{
		//create OK
		if (pWanAdapter->pIRTC->Connect(pWanAdapter->hCaptureBlob, NULL, WanPacketReceiverCallback, (LPVOID)pWanAdapter , NULL) == NMERR_SUCCESS)
		{
			//connect OK
			if (pWanAdapter->pIRTC->Start() == NMERR_SUCCESS)
			{
				return pWanAdapter;
			}
			else
			{
				pWanAdapter->pIRTC->Disconnect();
				pWanAdapter->pIRTC->Release();
				goto error;
			}
		}
		else
		{
			pWanAdapter->pIRTC->Release();
			goto error;
		}
	}
	else
	{
		goto error;
	}

	//awfully never reached
//	return NULL;

error:

	if (pWanAdapter != NULL)
	{
		if (pWanAdapter->hReadEvent != NULL)
			CloseHandle(pWanAdapter->hReadEvent);

		DeleteCriticalSection(&pWanAdapter->CriticalSection);
		if (pWanAdapter->hCaptureBlob)
			DestroyBlob(pWanAdapter->hCaptureBlob);

		GlobalFree(pWanAdapter);
	}

	CoUninitialize();
	
	return NULL;
}