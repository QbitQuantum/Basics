STDMETHODIMP VBoxDnDDropTarget::Drop(IDataObject *pDataObject, DWORD grfKeyState, POINTL pt, DWORD *pdwEffect)
{
    RT_NOREF(pt);
    AssertPtrReturn(pDataObject, E_INVALIDARG);
    AssertPtrReturn(pdwEffect,   E_INVALIDARG);

    LogFlowFunc(("mFormatEtc.cfFormat=%RI16 (%s), pDataObject=0x%p, grfKeyState=0x%x, x=%ld, y=%ld\n",
                 mFormatEtc.cfFormat, VBoxDnDDataObject::ClipboardFormatToString(mFormatEtc.cfFormat),
                 pDataObject, grfKeyState, pt.x, pt.y));

    HRESULT hr = S_OK;

    if (mFormatEtc.cfFormat) /* Did we get a supported format yet? */
    {
        /* Make sure the data object's data format is still valid. */
        hr = pDataObject->QueryGetData(&mFormatEtc);
        AssertMsg(SUCCEEDED(hr),
                  ("Data format changed to invalid between DragEnter() and Drop(), cfFormat=%RI16 (%s), hr=%Rhrc\n",
                  mFormatEtc.cfFormat, VBoxDnDDataObject::ClipboardFormatToString(mFormatEtc.cfFormat), hr));
    }

    int rc = VINF_SUCCESS;

    if (SUCCEEDED(hr))
    {
        STGMEDIUM stgMed;
        hr = pDataObject->GetData(&mFormatEtc, &stgMed);
        if (SUCCEEDED(hr))
        {
            /*
             * First stage: Prepare the access to the storage medium.
             *              For now we only support HGLOBAL stuff.
             */
            PVOID pvData = NULL; /** @todo Put this in an own union? */

            switch (mFormatEtc.tymed)
            {
                case TYMED_HGLOBAL:
                    pvData = GlobalLock(stgMed.hGlobal);
                    if (!pvData)
                    {
                        LogFlowFunc(("Locking HGLOBAL storage failed with %Rrc\n",
                                     RTErrConvertFromWin32(GetLastError())));
                        rc = VERR_INVALID_HANDLE;
                        hr = E_INVALIDARG; /* Set special hr for OLE. */
                    }
                    break;

                default:
                    AssertMsgFailed(("Storage medium type %RI32 supported\n",
                                     mFormatEtc.tymed));
                    rc = VERR_NOT_SUPPORTED;
                    hr = DV_E_TYMED; /* Set special hr for OLE. */
                    break;
            }

            if (RT_SUCCESS(rc))
            {
                /*
                 * Second stage: Do the actual copying of the data object's data,
                 *               based on the storage medium type.
                 */
                switch (mFormatEtc.cfFormat)
                {
                    case CF_TEXT:
                    /* Fall through is intentional. */
                    case CF_UNICODETEXT:
                    {
                        AssertPtr(pvData);
                        size_t cbSize = GlobalSize(pvData);
                        LogFlowFunc(("CF_TEXT/CF_UNICODETEXT 0x%p got %zu bytes\n", pvData, cbSize));
                        if (cbSize)
                        {
                            char *pszText = NULL;

                            rc = mFormatEtc.cfFormat == CF_TEXT
                               /* ANSI codepage -> UTF-8 */
                               ? RTStrCurrentCPToUtf8(&pszText, (char *)pvData)
                               /* Unicode  -> UTF-8 */
                               : RTUtf16ToUtf8((PCRTUTF16)pvData, &pszText);

                            if (RT_SUCCESS(rc))
                            {
                                AssertPtr(pszText);

                                size_t cbText = strlen(pszText) + 1; /* Include termination. */

                                mpvData = RTMemDup((void *)pszText, cbText);
                                mcbData = cbText;

                                RTStrFree(pszText);
                                pszText = NULL;
                            }
                        }

                        break;
                    }

                    case CF_HDROP:
                    {
                        AssertPtr(pvData);

                        /* Convert to a string list, separated by \r\n. */
                        DROPFILES *pDropFiles = (DROPFILES *)pvData;
                        AssertPtr(pDropFiles);
                        bool fUnicode = RT_BOOL(pDropFiles->fWide);

                        /* Get the offset of the file list. */
                        Assert(pDropFiles->pFiles >= sizeof(DROPFILES));
                        /* Note: This is *not* pDropFiles->pFiles! DragQueryFile only
                         *       will work with the plain storage medium pointer! */
                        HDROP hDrop = (HDROP)(pvData);

                        /* First, get the file count. */
                        /** @todo Does this work on Windows 2000 / NT4? */
                        char *pszFiles = NULL;
                        uint32_t cchFiles = 0;
                        UINT cFiles = DragQueryFile(hDrop, UINT32_MAX /* iFile */,
                                                    NULL /* lpszFile */, 0 /* cchFile */);
                        LogFlowFunc(("CF_HDROP got %RU16 file(s)\n", cFiles));

                        for (UINT i = 0; i < cFiles; i++)
                        {
                            UINT cch = DragQueryFile(hDrop, i /* File index */,
                                                     NULL /* Query size first */,
                                                     0 /* cchFile */);
                            Assert(cch);

                            if (RT_FAILURE(rc))
                                break;

                            char *pszFile = NULL; /* UTF-8 version. */
                            UINT cchFile = 0;
                            if (fUnicode)
                            {
                                /* Allocate enough space (including terminator). */
                                WCHAR *pwszFile = (WCHAR *)RTMemAlloc((cch + 1) * sizeof(WCHAR));
                                if (pwszFile)
                                {
                                    cchFile = DragQueryFileW(hDrop, i /* File index */,
                                                             pwszFile, cch + 1 /* Include terminator */);
                                    AssertMsg(cchFile == cch, ("cchCopied (%RU16) does not match cchFile (%RU16)\n",
                                                               cchFile, cch));
                                    rc = RTUtf16ToUtf8(pwszFile, &pszFile);
                                    AssertRC(rc);

                                    RTMemFree(pwszFile);
                                }
                                else
                                    rc = VERR_NO_MEMORY;
                            }
                            else /* ANSI */
                            {
                                /* Allocate enough space (including terminator). */
                                pszFile = (char *)RTMemAlloc((cch + 1) * sizeof(char));
                                if (pszFile)
                                {
                                    cchFile = DragQueryFileA(hDrop, i /* File index */,
                                                             pszFile, cchFile + 1 /* Include terminator */);
                                    AssertMsg(cchFile == cch, ("cchCopied (%RU16) does not match cchFile (%RU16)\n",
                                                               cchFile, cch));
                                }
                                else
                                    rc = VERR_NO_MEMORY;
                            }

                            if (RT_SUCCESS(rc))
                            {
                                LogFlowFunc(("\tFile: %s (cchFile=%RU32)\n", pszFile, cchFile));
                                rc = RTStrAAppendExN(&pszFiles, 1 /* cPairs */,
                                                     pszFile, cchFile);
                                if (RT_SUCCESS(rc))
                                    cchFiles += cchFile;
                            }

                            if (pszFile)
                                RTStrFree(pszFile);

                            if (RT_FAILURE(rc))
                                break;

                            /* Add separation between filenames.
                             * Note: Also do this for the last element of the list. */
                            rc = RTStrAAppendExN(&pszFiles, 1 /* cPairs */,
                                                 "\r\n", 2 /* Bytes */);
                            if (RT_SUCCESS(rc))
                                cchFiles += 2; /* Include \r\n */
                        }

                        if (RT_SUCCESS(rc))
                        {
                            cchFiles += 1; /* Add string termination. */
                            uint32_t cbFiles = cchFiles * sizeof(char);

                            LogFlowFunc(("cFiles=%u, cchFiles=%RU32, cbFiles=%RU32, pszFiles=0x%p\n",
                                         cFiles, cchFiles, cbFiles, pszFiles));

                            /* Translate the list into URI elements. */
                            DnDURIList lstURI;
                            rc = lstURI.AppendNativePathsFromList(pszFiles, cbFiles,
                                                                  DNDURILIST_FLAGS_ABSOLUTE_PATHS);
                            if (RT_SUCCESS(rc))
                            {
                                RTCString strRoot = lstURI.RootToString();
                                size_t cbRoot = strRoot.length() + 1; /* Include termination */

                                mpvData = RTMemAlloc(cbRoot);
                                if (mpvData)
                                {
                                    memcpy(mpvData, strRoot.c_str(), cbRoot);
                                    mcbData = cbRoot;
                                }
                                else
                                    rc = VERR_NO_MEMORY;
                            }
                        }

                        LogFlowFunc(("Building CF_HDROP list rc=%Rrc, pszFiles=0x%p, cFiles=%RU16, cchFiles=%RU32\n",
                                     rc, pszFiles, cFiles, cchFiles));

                        if (pszFiles)
                            RTStrFree(pszFiles);
                        break;
                    }

                    default:
                        /* Note: Should not happen due to the checks done in DragEnter(). */
                        AssertMsgFailed(("Format of type %RI16 (%s) not supported\n",
                                         mFormatEtc.cfFormat, VBoxDnDDataObject::ClipboardFormatToString(mFormatEtc.cfFormat)));
                        hr = DV_E_CLIPFORMAT; /* Set special hr for OLE. */
                        break;
                }

                /*
                 * Third stage: Unlock + release access to the storage medium again.
                 */
                switch (mFormatEtc.tymed)
                {
                    case TYMED_HGLOBAL:
                        GlobalUnlock(stgMed.hGlobal);
                        break;

                    default:
                        AssertMsgFailed(("Really should not happen -- see init stage!\n"));
                        break;
                }
            }

            /* Release storage medium again. */
            ReleaseStgMedium(&stgMed);

            /* Signal waiters. */
            mDroppedRc = rc;
            RTSemEventSignal(hEventDrop);
        }
    }

    if (RT_SUCCESS(rc))
    {
        /* Note: pt is not used since we don't need to differentiate within our
         *       proxy window. */
        *pdwEffect = VBoxDnDDropTarget::GetDropEffect(grfKeyState, *pdwEffect);
    }
    else
        *pdwEffect = DROPEFFECT_NONE;

    if (mpWndParent)
        mpWndParent->hide();

    LogFlowFunc(("Returning with hr=%Rhrc (%Rrc), mFormatEtc.cfFormat=%RI16 (%s), *pdwEffect=%RI32\n",
                 hr, rc, mFormatEtc.cfFormat, VBoxDnDDataObject::ClipboardFormatToString(mFormatEtc.cfFormat),
                 *pdwEffect));

    return hr;
}