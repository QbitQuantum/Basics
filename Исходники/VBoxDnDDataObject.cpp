/**
 * Retrieves the data stored in this object and store the result in
 * pMedium.
 *
 * @return  IPRT status code.
 * @return  HRESULT
 * @param   pFormatEtc
 * @param   pMedium
 */
STDMETHODIMP VBoxDnDDataObject::GetData(FORMATETC *pFormatEtc, STGMEDIUM *pMedium)
{
    AssertPtrReturn(pFormatEtc, DV_E_FORMATETC);
    AssertPtrReturn(pMedium, DV_E_FORMATETC);

    ULONG lIndex;
    if (!LookupFormatEtc(pFormatEtc, &lIndex)) /* Format supported? */
        return DV_E_FORMATETC;
    if (lIndex >= mcFormats) /* Paranoia. */
        return DV_E_FORMATETC;

    LogFlowFunc(("pFormatEtc=%p, pMedium=%p\n", pFormatEtc, pMedium));

    FORMATETC *pThisFormat = &mpFormatEtc[lIndex];
    AssertPtr(pThisFormat);

    STGMEDIUM *pThisMedium = &mpStgMedium[lIndex];
    AssertPtr(pThisMedium);

    HRESULT hr = DV_E_FORMATETC;

    LogFlowFunc(("mStatus=%ld\n", mStatus));
    if (mStatus == Dropping)
    {
        LogFlowFunc(("Waiting for event ...\n"));
        int rc2 = RTSemEventWait(mSemEvent, RT_INDEFINITE_WAIT);
        LogFlowFunc(("rc=%Rrc, mStatus=%ld\n", rc2, mStatus));
    }

    if (mStatus == Dropped)
    {
        LogFlowFunc(("cfFormat=%RI16, sFormat=%s, tyMed=%RU32, dwAspect=%RU32\n",
                     pThisFormat->cfFormat, VBoxDnDDataObject::ClipboardFormatToString(pFormatEtc->cfFormat),
                     pThisFormat->tymed, pThisFormat->dwAspect));
        LogFlowFunc(("Got strFormat=%s, pvData=%p, cbData=%RU32\n",
                     mstrFormat.c_str(), mpvData, mcbData));

        if (mstrFormat.equalsIgnoreCase("text/uri-list"))
        {
            RTCList<RTCString> lstFilesURI = RTCString((char*)mpvData, mcbData).split("\r\n");
            RTCList<RTCString> lstFiles;
            for (size_t i = 0; i < lstFilesURI.size(); i++)
            {
                /* Extract path from URI. */
                char *pszPath = RTUriPath(lstFilesURI.at(i).c_str());
                if (   pszPath
                    && strlen(pszPath) > 1)
                {
                    pszPath++; /** @todo Skip first '/' (part of URI). Correct? */
                    pszPath = RTPathChangeToDosSlashes(pszPath, false /* fForce */);
                    lstFiles.append(pszPath);
                }
            }
#ifdef DEBUG
            LogFlowFunc(("Files (%zu)\n", lstFiles.size()));
            for (size_t i = 0; i < lstFiles.size(); i++)
                LogFlowFunc(("\tFile: %s\n", lstFiles.at(i).c_str()));
#endif

#if 0
            if (   (pFormatEtc->tymed & TYMED_ISTREAM)
                && (pFormatEtc->dwAspect == DVASPECT_CONTENT)
                && (pFormatEtc->cfFormat == CF_FILECONTENTS))
            {

            }
            else if  (   (pFormatEtc->tymed & TYMED_HGLOBAL)
                      && (pFormatEtc->dwAspect == DVASPECT_CONTENT)
                      && (pFormatEtc->cfFormat == CF_FILEDESCRIPTOR))
            {

            }
            else if (   (pFormatEtc->tymed & TYMED_HGLOBAL)
                     && (pFormatEtc->cfFormat == CF_PREFERREDDROPEFFECT))
            {
                HGLOBAL hData = GlobalAlloc(GMEM_MOVEABLE | GMEM_SHARE | GMEM_ZEROINIT, sizeof(DWORD));
                DWORD *pdwEffect = (DWORD *)GlobalLock(hData);
                AssertPtr(pdwEffect);
                *pdwEffect = DROPEFFECT_COPY;
                GlobalUnlock(hData);

                pMedium->hGlobal = hData;
                pMedium->tymed = TYMED_HGLOBAL;
            }
            else
#endif
                 if (   (pFormatEtc->tymed & TYMED_HGLOBAL)
                     && (pFormatEtc->dwAspect == DVASPECT_CONTENT)
                     && (pFormatEtc->cfFormat == CF_TEXT))
            {
                pMedium->hGlobal = GlobalAlloc(GHND, mcbData + 1);
                if (pMedium->hGlobal)
                {
                    /** @todo Not working yet -- needs URI to plain ASCII conversion. */

                    char *pcDst  = (char *)GlobalLock(pMedium->hGlobal);
                    memcpy(pcDst, mpvData, mcbData);
                    pcDst[mcbData] = '\0';
                    GlobalUnlock(pMedium->hGlobal);

                    hr = S_OK;
                }
            }
            else if (   (pFormatEtc->tymed & TYMED_HGLOBAL)
                     && (pFormatEtc->dwAspect == DVASPECT_CONTENT)
                     && (pFormatEtc->cfFormat == CF_HDROP))
            {
                int rc = VINF_SUCCESS;

                size_t cchFiles = 0; /* Number of ASCII characters. */
                for (size_t i = 0; i < lstFiles.size(); i++)
                {
                    cchFiles += strlen(lstFiles.at(i).c_str());
                    cchFiles += 1; /* Terminating '\0'. */
                }

                size_t cbBuf = sizeof(DROPFILES) + ((cchFiles + 1) * sizeof(RTUTF16));
                DROPFILES *pBuf = (DROPFILES *)RTMemAllocZ(cbBuf);
                if (pBuf)
                {
                    pBuf->pFiles = sizeof(DROPFILES);
                    pBuf->fWide = 1; /* We use unicode. Always. */

                    uint8_t *pCurFile = (uint8_t *)pBuf + pBuf->pFiles;
                    AssertPtr(pCurFile);

                    for (size_t i = 0; i < lstFiles.size() && RT_SUCCESS(rc); i++)
                    {
                        size_t cchCurFile;
                        PRTUTF16 pwszFile;
                        rc = RTStrToUtf16(lstFiles.at(i).c_str(), &pwszFile);
                        if (RT_SUCCESS(rc))
                        {
                            cchCurFile = RTUtf16Len(pwszFile);
                            Assert(cchCurFile);
                            memcpy(pCurFile, pwszFile, cchCurFile * sizeof(RTUTF16));
                            RTUtf16Free(pwszFile);
                        }
                        else
                            break;

                        pCurFile += cchCurFile * sizeof(RTUTF16);

                        /* Terminate current file name. */
                        *pCurFile = L'\0';
                        pCurFile += sizeof(RTUTF16);
                    }

                    if (RT_SUCCESS(rc))
                    {
                        *pCurFile = L'\0'; /* Final list terminator. */

                        pMedium->tymed = TYMED_HGLOBAL;
                        pMedium->pUnkForRelease = NULL;
                        pMedium->hGlobal = GlobalAlloc(  GMEM_ZEROINIT
                                                       | GMEM_MOVEABLE
                                                       | GMEM_DDESHARE, cbBuf);
                        if (pMedium->hGlobal)
                        {
                            LPVOID pMem = GlobalLock(pMedium->hGlobal);
                            if (pMem)
                            {
                                memcpy(pMem, pBuf, cbBuf);
                                GlobalUnlock(pMedium->hGlobal);

                                hr = S_OK;
                            }
                        }
                    }

                    RTMemFree(pBuf);
                }
                else
                    rc = VERR_NO_MEMORY;

                if (RT_FAILURE(rc))
                    hr = DV_E_FORMATETC;
            }
        }
    }

    if (FAILED(hr))
    {
        LogFlowFunc(("Copying medium ...\n"));
        switch (pThisMedium->tymed)
        {

        case TYMED_HGLOBAL:
            pMedium->hGlobal = (HGLOBAL)OleDuplicateData(pThisMedium->hGlobal,
                                                         pThisFormat->cfFormat, NULL);
            break;

        default:
            break;
        }

        pMedium->tymed          = pThisFormat->tymed;
        pMedium->pUnkForRelease = NULL;
    }

    LogFlowFunc(("hr=%Rhrc\n", hr));
    return hr;
}