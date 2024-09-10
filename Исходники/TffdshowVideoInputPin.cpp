HRESULT TffdshowVideoInputPin::CheckMediaType(const CMediaType* mt)
{
    if (mt->majortype != MEDIATYPE_Video && !(mt->majortype == MEDIATYPE_DVD_ENCRYPTED_PACK && supdvddec)) {
        return VFW_E_TYPE_NOT_ACCEPTED;
    }
    if (mt->subtype == MEDIASUBTYPE_DVD_SUBPICTURE) {
        return VFW_E_TYPE_NOT_ACCEPTED;
    }
    BITMAPINFOHEADER *hdr = NULL, hdr0;

    if (mt->formattype == FORMAT_VideoInfo) {
        VIDEOINFOHEADER *vih = (VIDEOINFOHEADER*)mt->pbFormat;
        hdr = &vih->bmiHeader;
        fixMPEGinAVI(hdr->biCompression);
    } else if (mt->formattype == FORMAT_VideoInfo2) {
        VIDEOINFOHEADER2 *vih2 = (VIDEOINFOHEADER2*)mt->pbFormat;
        hdr = &vih2->bmiHeader;
        fixMPEGinAVI(hdr->biCompression);
    } else if (mt->formattype == FORMAT_MPEGVideo) {
        MPEG1VIDEOINFO *mpeg1info = (MPEG1VIDEOINFO*)mt->pbFormat;
        hdr = &(hdr0 = mpeg1info->hdr.bmiHeader);
        hdr->biCompression = FOURCC_MPG1;
    } else if (mt->formattype == FORMAT_MPEG2Video) {
        MPEG2VIDEOINFO *mpeg2info = (MPEG2VIDEOINFO*)mt->pbFormat;
        hdr = &(hdr0 = mpeg2info->hdr.bmiHeader);
        if (hdr->biCompression == 0 || hdr->biCompression == 0x0038002d) {
            if (mt->subtype == MEDIASUBTYPE_H264_TRANSPORT) {
                hdr->biCompression = FOURCC_H264;
            } else if (mt->subtype == MEDIASUBTYPE_AVC1 || mt->subtype == MEDIASUBTYPE_avc1 || mt->subtype == MEDIASUBTYPE_H264 || mt->subtype == MEDIASUBTYPE_h264 || mt->subtype == MEDIASUBTYPE_CCV1) {
                hdr->biCompression = FOURCC_H264;
            } else {
                hdr->biCompression = FOURCC_MPG2;
            }
        }
    } else if (mt->formattype == FORMAT_TheoraIll) {
        sTheoraFormatBlock *oggFormat = (sTheoraFormatBlock*)mt->pbFormat;
        hdr = &hdr0;
        hdr->biWidth = oggFormat->width;
        hdr->biHeight = oggFormat->height;
        hdr->biCompression = FOURCC_THEO;
    } else if (mt->formattype == FORMAT_RLTheora) {
        hdr = &hdr0;
        hdr->biCompression = FOURCC_THEO;
    } else {
        return VFW_E_TYPE_NOT_ACCEPTED;
    }

    char_t pomS[60];
    DPRINTF(_l("TffdshowVideoInputPin::CheckMediaType: %s, %i, %i"), fourcc2str(hdr2fourcc(hdr, &mt->subtype), pomS, 60), hdr->biWidth, hdr->biHeight);

    /* Information : WMP 11 and Media Center under Vista do not check for uncompressed format anymore, so no way to get
       ffdshow raw video decoder for postprocessing on uncompressed.
       So instead of saying "Media Type not supported", we says it is but only if there is an existing filter that can
       take this format in charge, and then ffdshow will be plugged after this codec (plug is done by TffdshowDecVideo::ConnectCompatibleFilter). */
    int res = getVideoCodecId(hdr, &mt->subtype, NULL);

    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&osvi);
    ffstring exeFilename(fv->getExefilename());
    exeFilename.ConvertToLowerCase();

    if (res == 0 && pCompatibleFilter == NULL &&
            fv->deci->getParam2(IDFF_alternateUncompressed) == 1 && // Enable WMP11 postprocessing
            fv->deci->getParam2(IDFF_rawv) != 0 && // Raw video not on disabled
            (exeFilename == _l("wmplayer.exe") ||
             exeFilename == _l("ehshell.exe"))) { // Only WMP and Media Center are concerned
        bool doPostProcessing = false;
        if (osvi.dwMajorVersion > 5) { // OS >= VISTA
            doPostProcessing = true;
        } else if (osvi.dwMajorVersion == 5 // If OS=XP, check version of WMP
                   && exeFilename == _l("ehshell.exe")) { // But only for Media Center
            // Read WMP version from the aRegistry
            HKEY hKey = NULL;
            LONG regErr;

            // Read WMP version from the following registry key
            regErr = RegOpenKeyEx(HKEY_LOCAL_MACHINE, _l("SOFTWARE\\Microsoft\\MediaPlayer\\Setup\\Installed Versions"), 0, KEY_READ, &hKey);
            if (regErr != ERROR_SUCCESS) {
                return res == AV_CODEC_ID_NONE ? VFW_E_TYPE_NOT_ACCEPTED : S_OK;
            }

            DWORD dwType;
            BYTE buf[4096] = { '\0' };   // make it big enough for any kind of values
            DWORD dwSize = sizeof(buf);
            regErr = RegQueryValueEx(hKey, _T("wmplayer.exe"), 0, &dwType, buf, &dwSize);

            if (hKey) {
                RegCloseKey(hKey);
            }

            if (regErr != ERROR_SUCCESS || dwType != REG_BINARY) {
                return res == AV_CODEC_ID_NONE ? VFW_E_TYPE_NOT_ACCEPTED : S_OK;
            }

            if (buf[2] >= 0x0b) { // Third byte is the major version number
                doPostProcessing = true;
            }
        }


        if (doPostProcessing) {
            DPRINTF(_l("TffdshowVideoInputPin::CheckMediaType: input format disabled or not supported. Trying to maintain in the graph..."));
            IFilterMapper2 *pMapper = NULL;
            IEnumMoniker *pEnum = NULL;

            HRESULT hr = CoCreateInstance(CLSID_FilterMapper2,
                                          NULL, CLSCTX_INPROC, IID_IFilterMapper2,
                                          (void **) &pMapper);

            if (FAILED(hr)) {
                // Error handling omitted for clarity.
            }

            GUID arrayInTypes[2];
            arrayInTypes[0] = mt->majortype;//MEDIATYPE_Video;
            arrayInTypes[1] = mt->subtype;//MEDIASUBTYPE_dvsd;

            hr = pMapper->EnumMatchingFilters(
                     &pEnum,
                     0,                  // Reserved.
                     TRUE,               // Use exact match?
                     MERIT_DO_NOT_USE + 1, // Minimum merit.
                     TRUE,               // At least one input pin?
                     1,                  // Number of major type/subtype pairs for input.
                     arrayInTypes,       // Array of major type/subtype pairs for input.
                     NULL,               // Input medium.
                     NULL,               // Input pin category.
                     FALSE,              // Must be a renderer?
                     TRUE,               // At least one output pin?
                     0,                  // Number of major type/subtype pairs for output.
                     NULL,               // Array of major type/subtype pairs for output.
                     NULL,               // Output medium.
                     NULL);              // Output pin category.

            // Enumerate the monikers.
            IMoniker *pMoniker;
            ULONG cFetched;

            while (pEnum->Next(1, &pMoniker, &cFetched) == S_OK) {
                IPropertyBag *pPropBag = NULL;
                hr = pMoniker->BindToStorage(0, 0, IID_IPropertyBag,
                                             (void **)&pPropBag);

                if (SUCCEEDED(hr)) {
                    // To retrieve the friendly name of the filter, do the following:
                    VARIANT varName;
                    VariantInit(&varName);
                    hr = pPropBag->Read(L"FriendlyName", &varName, 0);
                    if (SUCCEEDED(hr)) {
                        if (varName.pbstrVal == NULL || _strnicmp(FFDSHOW_NAME_L, varName.bstrVal, 22) != 0) {
                            // Display the name in your UI somehow.
                            DPRINTF(_l("TffdshowVideoInputPin::CheckMediaType: compatible filter found (%s)"), varName.pbstrVal);
                            hr = pMoniker->BindToObject(NULL, NULL, IID_IBaseFilter, (void**)&pCompatibleFilter);
                        }
                    }

                    // Now add the filter to the graph. Remember to release pFilter later.
                    IFilterGraph *pGraph = NULL;
                    fv->deci->getGraph(&pGraph);

                    IGraphBuilder *pGraphBuilder = NULL;
                    hr = pGraph->QueryInterface(IID_IGraphBuilder, (void **)&pGraphBuilder);
                    if (hr == S_OK) {
                        pGraphBuilder->AddFilter(pCompatibleFilter, varName.bstrVal);
                    } else {
                        pCompatibleFilter->Release();
                        pCompatibleFilter = NULL;
                    }

                    // Clean up.
                    VariantClear(&varName);
                    pGraphBuilder->Release();
                    pPropBag->Release();
                }
                pMoniker->Release();
                if (pCompatibleFilter != NULL) {
                    break;
                }
            }

            // Clean up.
            pMapper->Release();
            pEnum->Release();
        }
    }
    if (pCompatibleFilter != NULL) {
        return S_OK;
    }
    return res == AV_CODEC_ID_NONE ? VFW_E_TYPE_NOT_ACCEPTED : S_OK;
}