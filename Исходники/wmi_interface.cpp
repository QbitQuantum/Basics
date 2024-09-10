/*!
 * @brief Perform a WMI query.
 * @param lpwRoot Name of the root object that is to be queried against.
 * @param lpwQuery The filter to use when reading objects (LDAP style).
 * @param response The response \c Packet to add the results to.
 */
DWORD wmi_query(LPCWSTR lpwRoot, LPWSTR lpwQuery, Packet* response)
{
	HRESULT hResult;

	dprintf("[WMI] Initialising COM");
	if ((hResult = CoInitializeEx(NULL, COINIT_MULTITHREADED)) == S_OK)
	{
		dprintf("[WMI] COM initialised");
		IWbemLocator* pLocator = NULL;
		IWbemServices* pServices = NULL;
		IEnumWbemClassObject* pEnumerator = NULL;
		IWbemClassObject* pSuperClass = NULL;
		IWbemClassObject* pObj = NULL;
		Tlv* valueTlvs = NULL;
		char* values = NULL;
		VARIANT** fields = NULL;

		do
		{
			if (FAILED(hResult = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, 0)))
			{
				dprintf("[WMI] Failed to initialize security: %x", hResult);
				break;
			}
			dprintf("[WMI] Security initialised");

			if (FAILED(hResult = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_ALL, IID_PPV_ARGS(&pLocator))))
			{
				dprintf("[WMI] Failed to create WbemLocator: %x", hResult);
				break;
			}
			dprintf("[WMI] WbemLocator created.");

			if (FAILED(hResult = pLocator->ConnectServer(_bstr_t(lpwRoot), NULL, NULL, NULL, WBEM_FLAG_CONNECT_USE_MAX_WAIT, NULL, NULL, &pServices)))
			{
				dprintf("[WMI] Failed to create WbemServices at %S: %x", lpwRoot, hResult);
				break;
			}
			dprintf("[WMI] WbemServices created.");

			if (FAILED(hResult = pServices->ExecQuery(L"WQL", lpwQuery, WBEM_FLAG_FORWARD_ONLY, NULL, &pEnumerator)))
			{
				dprintf("[WMI] Failed to create Enumerator for query %S: %x", lpwQuery, hResult);
				break;
			}
			dprintf("[WMI] Enumerated created.");

			ULONG numFound;
			if (FAILED(hResult = pEnumerator->Next(ENUM_TIMEOUT, 1, &pObj, &numFound)))
			{
				dprintf("[WMI] Failed to get the first query element: %x", lpwQuery, hResult);
				break;
			}
			dprintf("[WMI] First result read. hr=%x p=%p", hResult, pObj);

			if (hResult == WBEM_S_FALSE)
			{
				// this is not an error
				dprintf("[WMI] No results found!");
				break;
			}

			// get the names of the fields out of the first object before doing anything else.
			LPSAFEARRAY pFieldArray = NULL;
			if (FAILED(hResult = pObj->GetNames(NULL, WBEM_FLAG_ALWAYS, NULL, &pFieldArray)))
			{
				dprintf("[WMI] Failed to get field names: %x", hResult);
				break;
			}
			dprintf("[WMI] Field Names extracted. hr=%x p=%p", hResult, pFieldArray);

			// lock the array
			if (FAILED(hResult = SafeArrayLock(pFieldArray)))
			{
				dprintf("[WMI] Failed to get array dimension: %x", hResult);
				break;
			}
			dprintf("[WMI] Field name array locked.");

			do
			{
				dprintf("[WMI] Array dimensions: %u", SafeArrayGetDim(pFieldArray));

				// this array is just one dimension, let's get the bounds of the first dimension
				LONG lBound, uBound;
				if (FAILED(hResult = SafeArrayGetLBound(pFieldArray, 1, &lBound))
					|| FAILED(hResult = SafeArrayGetUBound(pFieldArray, 1, &uBound)))
				{
					dprintf("[WMI] Failed to get array dimensions: %x", hResult);
					break;
				}
				dprintf("[WMI] Bounds: %u to %u", lBound, uBound);

				LONG fieldCount = uBound - lBound - SYSTEM_FIELD_COUNT - 1;
				dprintf("[WMI] Query results in %u fields", fieldCount);

				fields = (VARIANT**)malloc(fieldCount * sizeof(VARIANT**));
				valueTlvs = (Tlv*)malloc(fieldCount * sizeof(Tlv));
				values = (char*)malloc(fieldCount * FIELD_SIZE);
				memset(fields, 0, fieldCount * sizeof(VARIANT**));
				memset(valueTlvs, 0, fieldCount * sizeof(Tlv));
				memset(values, 0, fieldCount * FIELD_SIZE);

				for (LONG i = 0; i < fieldCount; ++i)
				{
					LONG indices[1] = { i + SYSTEM_FIELD_COUNT };
					char* fieldName = values + (i * FIELD_SIZE);
					SafeArrayPtrOfIndex(pFieldArray, indices, (void**)&fields[i]);
					_bstr_t bstr(fields[i]->bstrVal);

					strncpy_s(fieldName, FIELD_SIZE, (const char*)bstr, FIELD_SIZE - 1);

					valueTlvs[i].header.type = TLV_TYPE_EXT_WMI_FIELD;
					valueTlvs[i].header.length = (UINT)strlen(fieldName) + 1;
					valueTlvs[i].buffer = (PUCHAR)fieldName;

					dprintf("[WMI] Added header field: %s", fieldName);
				}

				dprintf("[WMI] added all field headers");
				// add the field names to the packet
				packet_add_tlv_group(response, TLV_TYPE_EXT_WMI_FIELDS, valueTlvs, fieldCount);

				dprintf("[WMI] processing values...");
				// with that horrible pain out of the way, let's actually grab the data
				do
				{
					if (FAILED(hResult))
					{
						dprintf("[WMI] Loop exited via %x", hResult);
						break;
					}

					memset(valueTlvs, 0, fieldCount * sizeof(Tlv));
					memset(values, 0, fieldCount * FIELD_SIZE);

					for (LONG i = 0; i < fieldCount; ++i)
					{
						char* value = values + (i * FIELD_SIZE);
						valueTlvs[i].header.type = TLV_TYPE_EXT_WMI_VALUE;
						valueTlvs[i].buffer = (PUCHAR)value;

						VARIANT varValue;
						VariantInit(&varValue);

						_bstr_t field(fields[i]->bstrVal);
						dprintf("[WMI] Extracting value for %s", (char*)field);
						if (SUCCEEDED(pObj->Get(field, 0, &varValue, NULL, NULL)))
						{
							variant_to_string(_variant_t(varValue), value, FIELD_SIZE);
						}

						valueTlvs[i].header.length = (UINT)strlen(value) + 1;
						dprintf("[WMI] Added value for %s: %s", (char*)_bstr_t(fields[i]->bstrVal), value);
					}

					// add the field values to the packet
					packet_add_tlv_group(response, TLV_TYPE_EXT_WMI_VALUES, valueTlvs, fieldCount);

					pObj->Release();
					pObj = NULL;
				} while ((hResult = pEnumerator->Next(ENUM_TIMEOUT, 1, &pObj, &numFound)) != WBEM_S_FALSE);

			} while (0);

			SafeArrayUnlock(pFieldArray);
		} while (0);

		if (fields)
		{
			free(fields);
		}

		if (values)
		{
			free(values);
		}

		if (valueTlvs)
		{
			free(valueTlvs);
		}

		if (pObj)
		{
			pObj->Release();
		}

		if (pEnumerator)
		{
			pEnumerator->Release();
		}

		if (pServices)
		{
			pServices->Release();
		}

		if (pLocator)
		{
			pLocator->Release();
		}
		CoUninitialize();

		if (SUCCEEDED(hResult))
		{
			hResult = S_OK;
			dprintf("[WMI] Things appeard to go well!");
		}
	}
	else
	{
		dprintf("[WMI] Failed to initialize COM");
	}

	if (FAILED(hResult))
	{
		// if we failed, we're going to convert the error to a string, add it and still return success, but we'll
		// also include the hresult.
		char errorMessage[1024];
		memset(errorMessage, 0, 1024);
		_com_error comError(hResult);
		_snprintf_s(errorMessage, 1024, 1023, "%s (0x%x)", comError.ErrorMessage(), hResult);
		dprintf("[WMI] returning error -> %s", errorMessage);
		packet_add_tlv_string(response, TLV_TYPE_EXT_WMI_ERROR, errorMessage);
		hResult = S_OK;
	}

	return (DWORD)hResult;
}