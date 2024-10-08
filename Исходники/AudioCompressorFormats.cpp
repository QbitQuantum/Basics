HRESULT CAudioCompressorFormats::GetSupportedFormats(std::vector<WAVEFORMATEX*>& listFormats)
{
	CStringW swDeviceName(m_sAudComp);

	HRESULT hr = m_pSysDevEnum->CreateClassEnumerator(CLSID_AudioCompressorCategory, &m_pEnumCat, 0);
	if(NULL == m_pEnumCat)
		return E_POINTER;
	if(S_OK == hr)
	{
		ULONG cFetched;
		while(m_pEnumCat->Next(1, &m_pMoniker, &cFetched) == S_OK)
		{
			IPropertyBag *pPropBag;
			hr = m_pMoniker->BindToStorage(0, 0, IID_IPropertyBag, 
				(void **)&pPropBag);
			if (SUCCEEDED(hr))
			{
				VARIANT varName;
				VariantInit(&varName);
				hr = pPropBag->Read(L"FriendlyName", &varName, 0);
				if (SUCCEEDED(hr))
				{
					if(wcscmp((WCHAR*)varName.pbstrVal, swDeviceName.GetBuffer()) == 0)
					{
						m_pMoniker->AddRef();
						break;
					}
				}
				VariantClear(&varName);
				pPropBag->Release();
			}
			m_pMoniker->Release();
		}
	}
	if(m_pMoniker)
	{
		IBaseFilter *pFilter = 0;
		hr = m_pMoniker->BindToObject(0, 0, IID_IBaseFilter, (void**)&pFilter);
		if(SUCCEEDED(hr))
		{
			IEnumPins *pEnum = NULL;
			hr = pFilter->EnumPins(&pEnum);
			if (SUCCEEDED(hr))
			{
				IPin *pPin = NULL;
				while(S_OK == pEnum->Next(1, &pPin, NULL))
				{
					IAMStreamConfig *pConf;
					hr = pPin->QueryInterface(IID_IAMStreamConfig, (void**)&pConf);
					if (SUCCEEDED(hr))
					{
						CString sFormat;
						int iCount, iSize;
						BYTE *pSCC = NULL;
						AM_MEDIA_TYPE *pmt;
						float fSample;
						hr = pConf->GetNumberOfCapabilities(&iCount, &iSize);
						pSCC = new BYTE[iSize];
						if (pSCC == NULL)
						{
							return E_POINTER;
						}
						if (iSize == sizeof(AUDIO_STREAM_CONFIG_CAPS))
						{
							// Use the audio capabilities structure.
							for (int iFormat = 0; iFormat < iCount; iFormat++)
							{
								AUDIO_STREAM_CONFIG_CAPS scc;
								AM_MEDIA_TYPE *pmtConfig;
								hr = pConf->GetStreamCaps(iFormat, &pmtConfig, (BYTE*)&scc);
								if (SUCCEEDED(hr))
								{
									if(pmtConfig->formattype == FORMAT_WaveFormatEx)
									{
										WAVEFORMATEX *pFormat = new WAVEFORMATEX(*(reinterpret_cast<WAVEFORMATEX*>(pmtConfig->pbFormat)));
										if(pFormat)
										{
											listFormats.push_back(pFormat);
										}
										FreeMediaType(*pmtConfig); 
										CoTaskMemFree(pmtConfig);
									}
								}
							}
							delete pSCC;
						}
						pConf->Release();
					}
					pPin->Release();
				}
				pEnum->Release();
			}
			pFilter->Release();
		}
	}
}