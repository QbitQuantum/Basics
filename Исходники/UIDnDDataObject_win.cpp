/**
 * Retrieves the data stored in this object and store the result in
 * pMedium.
 *
 * @return  IPRT status code.
 * @return  HRESULT
 * @param   pFormatEtc
 * @param   pMedium
 */
STDMETHODIMP UIDnDDataObject::GetData(LPFORMATETC pFormatEtc, LPSTGMEDIUM pMedium)
{
    AssertPtrReturn(pFormatEtc, DV_E_FORMATETC);
    AssertPtrReturn(pMedium, DV_E_FORMATETC);

    HRESULT hr = DV_E_FORMATETC;

    LPFORMATETC pThisFormat = NULL;
    LPSTGMEDIUM pThisMedium = NULL;

    /* Format supported? */
    ULONG lIndex;
    if (   LookupFormatEtc(pFormatEtc, &lIndex)
        && lIndex < mcFormats) /* Paranoia. */
    {
        pThisMedium = &mpStgMedium[lIndex];
        AssertPtr(pThisMedium);
        pThisFormat = &mpFormatEtc[lIndex];
        AssertPtr(pThisFormat);

        LogFlowFunc(("pThisMedium=%p, pThisFormat=%p\n", pThisMedium, pThisFormat));
        LogFlowFunc(("mStatus=%ld\n", mStatus));
        switch (mStatus)
        {
            case Dropping:
            {
                    LogRel3(("DnD: Dropping\n"));
                    LogFlowFunc(("Waiting for event ...\n"));
                    int rc2 = RTSemEventWait(mSemEvent, RT_INDEFINITE_WAIT);
                    LogFlowFunc(("rc=%Rrc, mStatus=%ld\n", rc2, mStatus));
            }

            case Dropped:
            {
                LogRel3(("DnD: Dropped\n"));
                LogRel3(("DnD: cfFormat=%RI16, sFormat=%s, tyMed=%RU32, dwAspect=%RU32\n",
                         pThisFormat->cfFormat, UIDnDDataObject::ClipboardFormatToString(pFormatEtc->cfFormat),
                         pThisFormat->tymed, pThisFormat->dwAspect));
                LogRel3(("DnD: Got strFormat=%s, pvData=%p, cbData=%RU32\n",
                         mstrFormat.toAscii().constData(), mpvData, mcbData));

                QVariant::Type vaType;
                QString strMIMEType;
                if (    (pFormatEtc->tymed & TYMED_HGLOBAL)
                     && (pFormatEtc->dwAspect == DVASPECT_CONTENT)
                     && (   pFormatEtc->cfFormat == CF_TEXT
                         || pFormatEtc->cfFormat == CF_UNICODETEXT)
                   )
                {
                    strMIMEType = "text/plain"; /** @todo Indicate UTF8 encoding? */
                    vaType = QVariant::String;
                }
                else if (   (pFormatEtc->tymed & TYMED_HGLOBAL)
                         && (pFormatEtc->dwAspect == DVASPECT_CONTENT)
                         && (pFormatEtc->cfFormat == CF_HDROP))
                {
                    strMIMEType = "text/uri-list";
                    vaType = QVariant::StringList;
                }
#if 0 /* More formats; not needed right now. */
                else if (   (pFormatEtc->tymed & TYMED_ISTREAM)
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
#endif
                LogRel3(("DnD: strMIMEType=%s, vaType=%ld\n", strMIMEType.toAscii().constData(), vaType));

                int rc;
                if (!mVaData.isValid())
                {
                    /* Note:  We're usig Qt::MoveAction because this speeds up the whole operation
                     *        significantly: Instead of copying the data from the temporary location to
                     *        the final destination we just move it.
                     *
                     * Note2: The Qt::MoveAction *only* affects the behavior on the host! The desired
                     *        action for the guest (e.g. moving a file from guest to host) is not affected
                     *        by this setting. */
                    rc = m_pDnDHandler->retrieveData(Qt::MoveAction,
                                                     strMIMEType, vaType, mVaData);
                }
                else
                    rc = VINF_SUCCESS; /* Data already retrieved. */

                if (RT_SUCCESS(rc))
                {
                    if (   strMIMEType.startsWith("text/uri-list")
                               /* One item. */
                        && (   mVaData.canConvert(QVariant::String)
                               /* Multiple items. */
                            || mVaData.canConvert(QVariant::StringList))
                       )
                    {
                        QStringList lstFilesURI = mVaData.toStringList();
                        QStringList lstFiles;
                        for (size_t i = 0; i < lstFilesURI.size(); i++)
                        {
                            /* Extract path from URI. */
                            char *pszPath = RTUriPath(lstFilesURI.at(i).toAscii().constData());
                            if (   pszPath
                                && strlen(pszPath) > 1)
                            {
                                pszPath++; /** @todo Skip first '/' (part of URI). Correct? */
                                pszPath = RTPathChangeToDosSlashes(pszPath, false /* fForce */);
                                lstFiles.append(pszPath);
                            }
                        }

                        size_t cFiles = lstFiles.size();
                        Assert(cFiles);
#ifdef DEBUG
                        LogFlowFunc(("Files (%zu)\n", cFiles));
                        for (size_t i = 0; i < cFiles; i++)
                            LogFlowFunc(("\tFile: %s\n", lstFiles.at(i).toAscii().constData()));
#endif
                        size_t cchFiles = 0; /* Number of ASCII characters. */
                        for (size_t i = 0; i < cFiles; i++)
                        {
                            cchFiles += strlen(lstFiles.at(i).toAscii().constData());
                            cchFiles += 1; /* Terminating '\0'. */
                        }

                        size_t cbBuf = sizeof(DROPFILES) + ((cchFiles + 1) * sizeof(RTUTF16));
                        DROPFILES *pDropFiles = (DROPFILES *)RTMemAllocZ(cbBuf);
                        if (pDropFiles)
                        {
                            pDropFiles->pFiles = sizeof(DROPFILES);
                            pDropFiles->fWide = 1; /* We use unicode. Always. */

                            uint8_t *pCurFile = (uint8_t *)pDropFiles + pDropFiles->pFiles;
                            AssertPtr(pCurFile);

                            for (size_t i = 0; i < cFiles; i++)
                            {
                                size_t cchCurFile;
                                PRTUTF16 pwszFile;
                                rc = RTStrToUtf16(lstFiles.at(i).toAscii().constData(), &pwszFile);
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
                                    LPVOID pvMem = GlobalLock(pMedium->hGlobal);
                                    if (pvMem)
                                    {
                                        memcpy(pvMem, pDropFiles, cbBuf);
                                        GlobalUnlock(pMedium->hGlobal);

                                        hr = S_OK;
                                    }
                                    else
                                        rc = VERR_ACCESS_DENIED;
                                }
                                else
                                    rc = VERR_NO_MEMORY;
                            }

                            RTMemFree(pDropFiles);
                        }
                    }
                    else if (   strMIMEType.startsWith("text/plain")
                             && mVaData.canConvert(QVariant::String))
                    {
                        bool fUnicode = pFormatEtc->cfFormat == CF_UNICODETEXT;
                        int cbCh = fUnicode
                                 ? sizeof(WCHAR) : sizeof(char);

                        QString strText = mVaData.toString();
                        size_t cbSrc = strText.length() * cbCh;
                        Assert(cbSrc);
                        LPCVOID pvSrc = fUnicode
                                      ? (void *)strText.unicode()
                                      : (void *)strText.toAscii().constData();
                        AssertPtr(pvSrc);

                        LogFlowFunc(("pvSrc=0x%p, cbSrc=%zu, cbch=%d, fUnicode=%RTbool\n",
                                     pvSrc, cbSrc, cbCh, fUnicode));

                        pMedium->tymed = TYMED_HGLOBAL;
                        pMedium->pUnkForRelease = NULL;
                        pMedium->hGlobal = GlobalAlloc(  GMEM_ZEROINIT
                                                       | GMEM_MOVEABLE
                                                       | GMEM_DDESHARE,
                                                       cbSrc);
                        if (pMedium->hGlobal)
                        {
                            LPVOID pvDst = GlobalLock(pMedium->hGlobal);
                            if (pvDst)
                            {
                                memcpy(pvDst, pvSrc, cbSrc);
                                GlobalUnlock(pMedium->hGlobal);
                            }
                            else
                                rc = VERR_ACCESS_DENIED;

                            hr = S_OK;
                        }
                        else
                            hr  = VERR_NO_MEMORY;
                    }
                    else
                        LogFlowFunc(("MIME type=%s not supported\n",
                                     strMIMEType.toAscii().constData()));

                    LogFlowFunc(("Handling formats ended with rc=%Rrc\n", rc));
                }
            }

            default:
                break;
        }
    }

    /*
     * Fallback in error case.
     */
    if (FAILED(hr))
    {
        if (pThisMedium)
        {
            switch (pThisMedium->tymed)
            {

            case TYMED_HGLOBAL:
                pMedium->hGlobal = (HGLOBAL)OleDuplicateData(pThisMedium->hGlobal,
                                                             pThisFormat->cfFormat,
                                                             0 /* Flags */);
                break;

            default:
                break;
            }
        }

        if (pFormatEtc)
            pMedium->tymed = pFormatEtc->tymed;

        pMedium->pUnkForRelease = NULL;
    }

    LogFlowFunc(("Returning hr=%Rhrc\n", hr));
    return hr;
}