WIAMICRO_API HRESULT MicroEntry(LONG lCommand, _Inout_ PVAL pValue)
{ // depends on command
	PWIASANE_Context pContext;
	PWINSANE_Option oOption;
	LONG lReceived;
	HANDLE hHeap;
	HRESULT hr;

	Trace(TEXT("------ MicroEntry(lCommand=%d) ------"), lCommand);

	if (!pValue || !pValue->pScanInfo)
		return E_INVALIDARG;

	if (!pValue->pScanInfo->DeviceIOHandles[1])
		pValue->pScanInfo->DeviceIOHandles[1] = GetProcessHeap();

	hHeap = pValue->pScanInfo->DeviceIOHandles[1];
	if (!hHeap)
		return E_OUTOFMEMORY;

	if (!pValue->pScanInfo->pMicroDriverContext)
		pValue->pScanInfo->pMicroDriverContext = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(WIASANE_Context));

	pContext = (PWIASANE_Context) pValue->pScanInfo->pMicroDriverContext;
	if (!pContext)
		return E_OUTOFMEMORY;

	hr = E_NOTIMPL;

	switch (lCommand) {
		case CMD_SETSTIDEVICEHKEY: // offline
			Trace(TEXT("CMD_SETSTIDEVICEHKEY"));

			if (pValue->pHandle) {
				pValue->pScanInfo->DeviceIOHandles[2] = *pValue->pHandle;

				hr = ReadRegistryInformation(pValue->pScanInfo, pContext);
			} else
				hr = E_FAIL;

			break;

		case CMD_INITIALIZE: // online
			Trace(TEXT("CMD_INITIALIZE"));
			g_pContext = pContext;

			hr = OpenScannerDevice(pValue->pScanInfo, pContext);
			if (SUCCEEDED(hr)) {
				hr = InitScannerDefaults(pValue->pScanInfo, pContext);

				ExitScannerSession(pValue->pScanInfo, pContext);
			}

			pValue->pScanInfo->DeviceIOHandles[2] = NULL;
			break;

		case CMD_UNINITIALIZE: // online
			Trace(TEXT("CMD_UNINITIALIZE"));
			g_pContext = NULL;

			hr = FreeScannerSession(pValue->pScanInfo, pContext);
			FreeScannerDefaults(pValue->pScanInfo, pContext);
			FreeRegistryInformation(pValue->pScanInfo, pContext);

			pValue->pScanInfo->pMicroDriverContext = NULL;
			pValue->pScanInfo->DeviceIOHandles[2] = NULL;
			pValue->pScanInfo->DeviceIOHandles[1] = NULL;
			break;

		case CMD_RESETSCANNER: // online
			Trace(TEXT("CMD_RESETSCANNER"));

		case CMD_STI_DEVICERESET: // online
			if (lCommand == CMD_STI_DEVICERESET)
				Trace(TEXT("CMD_STI_DEVICERESET"));

		case CMD_STI_DIAGNOSTIC: // online
			if (lCommand == CMD_STI_DIAGNOSTIC)
				Trace(TEXT("CMD_STI_DIAGNOSTIC"));

			hr = OpenScannerDevice(pValue->pScanInfo, pContext);
			if (SUCCEEDED(hr)) {
				hr = ExitScannerSession(pValue->pScanInfo, pContext);
			}
			break;

		case CMD_STI_GETSTATUS: // online
			Trace(TEXT("CMD_STI_GETSTATUS"));

			hr = OpenScannerDevice(pValue->pScanInfo, pContext);
			if (SUCCEEDED(hr)) {
				pValue->lVal = MCRO_STATUS_OK;

				ExitScannerSession(pValue->pScanInfo, pContext);
			} else {
				pValue->lVal = MCRO_ERROR_OFFLINE;
			}
			pValue->pGuid = (GUID*) &GUID_NULL;

			hr = S_OK;
			break;

		case CMD_SETXRESOLUTION: // offline, but requires device options
			Trace(TEXT("CMD_SETXRESOLUTION"));

			if (pContext->oDevice) {
				oOption = pContext->oDevice->GetOption(WIASANE_OPTION_RESOLUTION);
				if (!oOption) {
					Trace(TEXT("Required option '%hs' is not supported."),
						WIASANE_OPTION_RESOLUTION);
					hr = E_NOTIMPL;
					break;
				}
				if (!oOption->IsValidValue(pValue->lVal)) {
					Trace(TEXT("Invalid value '%d' for option '%hs'."),
						pValue->lVal, oOption->GetName());
					hr = E_INVALIDARG;
					break;
				}
			} else {
				Trace(TEXT("No device selected."));
				hr = E_FAIL;
				break;
			}

			Trace(TEXT("Set Xresolution to '%d'."), pValue->lVal);
			pValue->pScanInfo->Xresolution = pValue->lVal;
			hr = S_OK;
			break;

		case CMD_SETYRESOLUTION: // offline, but requires device options
			Trace(TEXT("CMD_SETYRESOLUTION"));

			if (pValue->pScanInfo->Xresolution != pValue->lVal) {
				Trace(TEXT("Invalid value '%d' compared to '%d'."),
					pValue->lVal, pValue->pScanInfo->Xresolution);
				hr = E_INVALIDARG;
				break;
			}

			Trace(TEXT("Set Yresolution to '%d'."), pValue->lVal);
			pValue->pScanInfo->Yresolution = pValue->lVal;
			hr = S_OK;
			break;

		case CMD_SETCONTRAST: // offline, but requires device options
			Trace(TEXT("CMD_SETCONTRAST"));

			if (pContext->oDevice) {
				oOption = pContext->oDevice->GetOption(WIASANE_OPTION_CONTRAST);
				if (!oOption) {
					oOption = pContext->oDevice->GetOption(WIASANE_OPTION_SHARPNESS);
				}
				if (!oOption) {
					Trace(TEXT("Option '%hs' or '%hs' is not supported."),
						WIASANE_OPTION_CONTRAST, WIASANE_OPTION_SHARPNESS);
					hr = E_NOTIMPL;
					break;
				}
				if (!oOption->IsValidValue(pValue->lVal)) {
					Trace(TEXT("Invalid value '%d' for option '%hs'."),
						pValue->lVal, oOption->GetName());
					hr = E_INVALIDARG;
					break;
				}
			} else {
				Trace(TEXT("No device selected."));
				hr = E_FAIL;
				break;
			}

			Trace(TEXT("Set Contrast to '%d'."), pValue->lVal);
			pValue->pScanInfo->Contrast = pValue->lVal;
			hr = S_OK;
			break;

		case CMD_SETINTENSITY: // offline, but requires device options
			Trace(TEXT("CMD_SETINTENSITY"));

			if (pContext->oDevice) {
				oOption = pContext->oDevice->GetOption(WIASANE_OPTION_BRIGHTNESS);
				if (!oOption) {
					Trace(TEXT("Option '%hs' or '%hs' is not supported."),
						WIASANE_OPTION_BRIGHTNESS);
					hr = E_NOTIMPL;
					break;
				}
				if (!oOption->IsValidValue(pValue->lVal)) {
					Trace(TEXT("Invalid value '%d' for option '%hs'."),
						pValue->lVal, oOption->GetName());
					hr = E_INVALIDARG;
					break;
				}
			} else {
				Trace(TEXT("No device selected."));
				hr = E_FAIL;
				break;
			}

			Trace(TEXT("Set Intensity to '%d'."), pValue->lVal);
			pValue->pScanInfo->Intensity = pValue->lVal;
			hr = S_OK;
			break;

		case CMD_SETDATATYPE: // offline
			Trace(TEXT("CMD_SETDATATYPE"));

			if (pValue->lVal == WIA_DATA_THRESHOLD && !(
			    pValue->pScanInfo->SupportedDataTypes & SUPPORT_BW)) {
					Trace(TEXT("Threshold mode is not supported."));
					hr = E_NOTIMPL;
					break;
			}
			if (pValue->lVal == WIA_DATA_GRAYSCALE && !(
			    pValue->pScanInfo->SupportedDataTypes & SUPPORT_GRAYSCALE)) {
					Trace(TEXT("Grayscale mode is not supported."));
					hr = E_NOTIMPL;
					break;
			}
			if (pValue->lVal == WIA_DATA_COLOR && !(
			    pValue->pScanInfo->SupportedDataTypes & SUPPORT_COLOR)) {
					Trace(TEXT("Color mode is not supported."));
					hr = E_NOTIMPL;
					break;
			}

			Trace(TEXT("Set DataType to '%d'."), pValue->lVal);
			pValue->pScanInfo->DataType = pValue->lVal;
			hr = S_OK;
			break;

		case CMD_SETSCANMODE: // offline
			Trace(TEXT("CMD_SETSCANMODE"));

			if (pValue->lVal != SCANMODE_FINALSCAN &&
				pValue->lVal != SCANMODE_PREVIEWSCAN) {
					Trace(TEXT("Unknown scan mode is not supported."));
					hr = E_INVALIDARG;
					break;
			}

			Trace(TEXT("Set lScanMode to '%d'."), pValue->lVal);
			pContext->lScanMode = pValue->lVal;
			hr = S_OK;
			break;

		case CMD_SETNEGATIVE: // offline
			Trace(TEXT("CMD_SETNEGATIVE"));

			Trace(TEXT("Set Negative to '%d'."), pValue->lVal);
			pValue->pScanInfo->Negative = pValue->lVal;
			hr = S_OK;
			break;

		case CMD_GETCAPABILITIES: // offline
			Trace(TEXT("CMD_GETCAPABILITIES"));

			pValue->lVal = 0;
			pValue->pGuid = NULL;
			pValue->ppButtonNames = NULL;

			hr = S_OK;
			break;

		case CMD_GETADFSTATUS: // online
			Trace(TEXT("CMD_GETADFSTATUS"));

			hr = OpenScannerDevice(pValue->pScanInfo, pContext);
			if (SUCCEEDED(hr)) {
				pValue->lVal = MCRO_STATUS_OK;

				if (pContext->pTask && pContext->pTask->bUsingADF) {
					CloseScannerDevice(pValue->pScanInfo, pContext);
				} else {
					ExitScannerSession(pValue->pScanInfo, pContext);
				}
			} else {
				pValue->lVal = MCRO_ERROR_OFFLINE;
			}

			hr = S_OK;
			break;

		case CMD_GETADFHASPAPER: // online
			Trace(TEXT("CMD_GETADFHASPAPER"));

			hr = OpenScannerDevice(pValue->pScanInfo, pContext);
			if (SUCCEEDED(hr)) {
				if (!pContext->pTask) {
					MicroEntry(CMD_LOAD_ADF, pValue);
				}

				if (pContext->pTask && pContext->pTask->bUsingADF) {
					pValue->lVal = MCRO_STATUS_OK;
					CloseScannerDevice(pValue->pScanInfo, pContext);
				} else {
					pValue->lVal = MCRO_ERROR_PAPER_EMPTY;
					ExitScannerSession(pValue->pScanInfo, pContext);
				}
			} else {
				pValue->lVal = MCRO_ERROR_OFFLINE;
			}

			hr = S_OK;
			break;

		case CMD_LOAD_ADF: // online
			Trace(TEXT("CMD_LOAD_ADF"));

			if (pContext->pTask && pContext->pTask->bUsingADF) {
				hr = S_OK;
				break;
			}

			hr = OpenScannerDevice(pValue->pScanInfo, pContext);
			if (SUCCEEDED(hr)) {
				oOption = pContext->oDevice->GetOption(WIASANE_OPTION_SOURCE);
				if (oOption && pContext->pValues) {
					switch (pValue->pScanInfo->ADF) {
						case 1:
							hr = oOption->SetValueString(pContext->pValues->pszSourceADF);
							break;

						case 2:
							hr = oOption->SetValueString(pContext->pValues->pszSourceDuplex);
							break;
					}
					if (SUCCEEDED(hr)) {
						hr = Scan(pValue->pScanInfo, SCAN_FIRST, NULL, 0, &lReceived);
						if (pContext->pTask) {
							if (SUCCEEDED(hr)) {
								pContext->pTask->bUsingADF = TRUE;
							} else {
								Scan(pValue->pScanInfo, SCAN_FINISHED, NULL, 0, &lReceived);
							}
						}
						if (!pContext->pTask || !pContext->pTask->bUsingADF) {
							oOption = pContext->oDevice->GetOption(WIASANE_OPTION_SOURCE);
							if (oOption) {
								oOption->SetValueString(pContext->pValues->pszSourceFlatbed);
							}
						}
					}
				} else
					hr = E_NOTIMPL;

				CloseScannerDevice(pValue->pScanInfo, pContext);
			}
			break;

		case CMD_UNLOAD_ADF: // online
			Trace(TEXT("CMD_UNLOAD_ADF"));

			hr = OpenScannerDevice(pValue->pScanInfo, pContext);
			if (SUCCEEDED(hr)) {
				oOption = pContext->oDevice->GetOption(WIASANE_OPTION_SOURCE);
				if (oOption && pContext->pValues) {
					hr = oOption->SetValueString(pContext->pValues->pszSourceFlatbed);
					if (SUCCEEDED(hr)) {
						if (pContext->pTask) {
							pContext->pTask->bUsingADF = FALSE;
						}
						hr = Scan(pValue->pScanInfo, SCAN_FINISHED, NULL, 0, &lReceived);
					}
				} else
					hr = E_NOTIMPL;

				ExitScannerSession(pValue->pScanInfo, pContext);
			}
			break;

		default:
			Trace(TEXT("Unknown Command (%d)"), lCommand);
			break;
	}

	return hr;
}