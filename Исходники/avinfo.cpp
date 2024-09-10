int AVInfo::GetCodecListSize(int width, int height)
{
    if (m_plCodecList)
    {
        for (int i=0; i<m_codecListSize; ++i)
            delete m_plCodecList[i];
        delete[] m_plCodecList;
        m_plCodecList = NULL;
        m_codecListSize = 0;
    }

    BITMAPINFO bmi;
    Make24BitRGB(&bmi.bmiHeader, width, height);

    ICINFO icInfo;
    ZeroMemory(&icInfo, sizeof ICINFO);
    icInfo.dwSize = sizeof ICINFO;
    int count = 0;

    std::vector<CODECINFO *> codecList;

    // The first codec is always uncompressed RGB
    // data. We can be sure this is the case here
    CODECINFO *pInfo = new CODECINFO;
    pInfo->fcc = MAKEFOURCC('D', 'I', 'B', ' ');
    pInfo->alternativeFcc = BI_RGB;
    pInfo->bHasAboutDialog = false;
    pInfo->bHasConfigureDialog = false;
    pInfo->bSupportsKeyframes = false;
    pInfo->bSupportsQuality = false;
    pInfo->nDefaultKeyframeRate = 1;
    pInfo->nDefaultQuality = 100;
    _tcscpy(pInfo->tszDescription, _T("DIB : <uncompressed>"));
    codecList.push_back(pInfo);

    while (ICInfo(ICTYPE_VIDEO, count, &icInfo))
    {
        HIC hic = ICOpen(icInfo.fccType, icInfo.fccHandler, ICMODE_QUERY);
        if (hic)
        {
            ICINFO moreInfo;
            ZeroMemory(&moreInfo, sizeof ICINFO);
            moreInfo.dwSize = sizeof ICINFO;

            if (ICGetInfo(hic, &moreInfo, sizeof ICINFO) > 0)
            {
                // Ignore MSVC/CRAM
                if (moreInfo.fccHandler != 'CVSM' &&
                        moreInfo.fccHandler != 'MARC')
                {
                    if (ICERR_OK == ICCompressQuery(hic, &bmi, NULL))
                    {
                        // Ok, this codec seems to be ok; put that
                        // into the list
                        CODECINFO *pInfo = new CODECINFO;
                        ZeroMemory(pInfo, sizeof CODECINFO);

                        char szFcc[5];
                        if (moreInfo.fccHandler != BI_RGB)
                        {
                            szFcc[0] = (moreInfo.fccHandler & 0x000000ff);
                            szFcc[1] = (moreInfo.fccHandler & 0x0000ff00) >> 8;
                            szFcc[2] = (moreInfo.fccHandler & 0x00ff0000) >> 16;
                            szFcc[3] = (moreInfo.fccHandler & 0xff000000) >> 24;
                            szFcc[4] = 0;
                        }
                        else
                            strcpy(szFcc, "DIB ");

                        bool bIsReallyOk = true;

                        // We know that IV50 has restrictions.
                        if (moreInfo.fccHandler == '05vi' ||
                                moreInfo.fccHandler == '05VI')
                        {
                            if (width % 4 != 0 ||
                                    height % 4 != 0)
                                bIsReallyOk = false;
                        }

                        // The following code should normally check if the codec
                        // is really able encode a certain BITMAPINFO type. But,
                        // This will fail for the HuffYUV codec. Thus, we have to
                        // assume that it might fail for other codecs, too.
                        /*
                        if (moreInfo.fccHandler == BI_RGB)
                        {
                           bIsReallyOk = true;
                        }
                        else
                        {
                           // The codec says that the input format is ok.
                           // Let's try to create an output format and try
                           // again. For some resolutions, e.g. Indeo Video 5
                           // now fails to compress the format.
                           AM_MEDIA_TYPE mtTmp;
                           ZeroMemory(&mtTmp, sizeof AM_MEDIA_TYPE);
                           bool cool = CreateStreamFormat(moreInfo.fccHandler, width, height, &mtTmp);

                           if (cool)
                           {
                              BITMAPINFO bmiOut;
                              ZeroMemory(&bmiOut, sizeof BITMAPINFO);
                              bmiOut.bmiHeader = ((VIDEOINFOHEADER *) mtTmp.pbFormat)->bmiHeader;
                              DWORD dwOk = ICCompressBegin(hic, &bmi, &bmiOut);
                              if (ICERR_OK == dwOk)
                              {
                                 // It's really ok to use this codec.
                                 bIsReallyOk = true;
                                 ICCompressEnd(hic);
                              }
                           }

                           FreeMediaType(mtTmp);
                        }
                        */

                        if (bIsReallyOk)
                        {
                            // Copy the name
#ifndef _UNICODE
                            _TCHAR tszDesc[128];
                            if (WideCharToMultiByte(CP_ACP, 0, moreInfo.szDescription, -1, tszDesc, 128, NULL, NULL) == 0)
                                strcpy(tszDesc, "<unknown>");
                            sprintf(pInfo->tszDescription, "(%s): %s", szFcc, tszDesc);
#else
                            _stprintf(pInfo->tszDescription, _T("(%S): %s"), szFcc, moreInfo.szDescription);
#endif

                            pInfo->fcc = moreInfo.fccHandler;
                            pInfo->alternativeFcc = icInfo.fccHandler;
                            pInfo->bSupportsKeyframes = (moreInfo.dwFlags & VIDCF_TEMPORAL) > 0;
                            pInfo->bSupportsQuality = (moreInfo.dwFlags & VIDCF_QUALITY) > 0;
                            if (pInfo->bSupportsKeyframes)
                                pInfo->nDefaultKeyframeRate = ICGetDefaultKeyFrameRate(hic);
                            else
                                pInfo->nDefaultKeyframeRate = 0;
                            if (pInfo->bSupportsQuality)
                                pInfo->nDefaultQuality = ICGetDefaultQuality(hic) / 100;
                            else
                                pInfo->nDefaultQuality = 0;

                            pInfo->bHasConfigureDialog = ICQueryConfigure(hic) == TRUE ? true : false;
                            pInfo->bHasAboutDialog = ICQueryAbout(hic) == TRUE ? true : false;

                            codecList.push_back(pInfo);
                        }
                    }
                }
            }