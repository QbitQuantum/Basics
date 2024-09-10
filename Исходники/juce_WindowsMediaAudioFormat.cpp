    void scanFileForDetails()
    {
        ComSmartPtr<IWMHeaderInfo> wmHeaderInfo;
        HRESULT hr = wmSyncReader.QueryInterface (wmHeaderInfo);

        if (SUCCEEDED (hr))
        {
            QWORD lengthInNanoseconds = 0;
            WORD lengthOfLength = sizeof (lengthInNanoseconds);
            WORD streamNum = 0;
            WMT_ATTR_DATATYPE wmAttrDataType;
            hr = wmHeaderInfo->GetAttributeByName (&streamNum, L"Duration", &wmAttrDataType,
                                                   (BYTE*) &lengthInNanoseconds, &lengthOfLength);

            ComSmartPtr<IWMProfile> wmProfile;
            hr = wmSyncReader.QueryInterface (wmProfile);

            if (SUCCEEDED (hr))
            {
                ComSmartPtr<IWMStreamConfig> wmStreamConfig;
                hr = wmProfile->GetStream (0, wmStreamConfig.resetAndGetPointerAddress());

                if (SUCCEEDED (hr))
                {
                    ComSmartPtr<IWMMediaProps> wmMediaProperties;
                    hr = wmStreamConfig.QueryInterface (wmMediaProperties);

                    if (SUCCEEDED (hr))
                    {
                        DWORD sizeMediaType;
                        hr = wmMediaProperties->GetMediaType (0, &sizeMediaType);

                        HeapBlock<WM_MEDIA_TYPE> mediaType;
                        mediaType.malloc (sizeMediaType, 1);
                        hr = wmMediaProperties->GetMediaType (mediaType, &sizeMediaType);

                        if (mediaType->majortype == WMMEDIATYPE_Audio)
                        {
                            const WAVEFORMATEX* const inputFormat = reinterpret_cast<WAVEFORMATEX*> (mediaType->pbFormat);

                            sampleRate = inputFormat->nSamplesPerSec;
                            numChannels = inputFormat->nChannels;
                            bitsPerSample = inputFormat->wBitsPerSample;
                            lengthInSamples = (lengthInNanoseconds * (int) sampleRate) / 10000000;
                        }
                    }
                }
            }
        }
    }