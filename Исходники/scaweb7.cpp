HRESULT ScaWebsRead7(
    __in SCA_WEB7** ppswList,
    __in SCA_HTTP_HEADER** ppshhList,
    __in SCA_WEB_ERROR** ppsweList,
    __in WCA_WRAPQUERY_HANDLE hUserQuery,
    __in WCA_WRAPQUERY_HANDLE hWebDirPropQuery,
    __in WCA_WRAPQUERY_HANDLE hSslCertQuery,
    __in WCA_WRAPQUERY_HANDLE hWebLogQuery,
    __in WCA_WRAPQUERY_HANDLE hWebAppQuery,
    __in WCA_WRAPQUERY_HANDLE hWebAppExtQuery,
    __inout LPWSTR *ppwzCustomActionData
    )
{
    Assert(ppswList);
    WcaLog(LOGMSG_VERBOSE, "Entering ScaWebsRead7()");

    HRESULT hr = S_OK;

    MSIHANDLE hRec;
    MSIHANDLE hRecAddresses;

    WCA_WRAPQUERY_HANDLE hQueryWebSite = NULL;
    WCA_WRAPQUERY_HANDLE hQueryWebAddress = NULL;

    SCA_WEB7* psw = NULL;
    LPWSTR pwzData = NULL;

    DWORD dwLen = 0;
    errno_t error = EINVAL;

    // check to see what tables are available
    hr = WcaBeginUnwrapQuery(&hQueryWebSite, ppwzCustomActionData);
    ExitOnFailure(hr, "Failed to unwrap query for ScaWebsRead");

    hr = WcaBeginUnwrapQuery(&hQueryWebAddress, ppwzCustomActionData);
    ExitOnFailure(hr, "Failed to unwrap query for ScaWebsRead");


    if (0 == WcaGetQueryRecords(hQueryWebSite) || 0 == WcaGetQueryRecords(hQueryWebAddress))
    {
        WcaLog(LOGMSG_VERBOSE, "Required tables not present");
        ExitFunction1(hr = S_FALSE);
    }

    // loop through all the webs
    while (S_OK == (hr = WcaFetchWrappedRecord(hQueryWebSite, &hRec)))
    {
        psw = NewWeb7();
        if (!psw)
        {
            hr = E_OUTOFMEMORY;
            break;
        }

        // get the darwin information
        hr = WcaGetRecordString(hRec, wqWeb, &pwzData);
        ExitOnFailure(hr, "Failed to get Web");
        hr = ::StringCchCopyW(psw->wzKey, countof(psw->wzKey), pwzData);
        ExitOnFailure(hr, "Failed to copy key string to web object");

        // get component install state
        hr = WcaGetRecordString(hRec, wqComponent, &pwzData);
        ExitOnFailure(hr, "Failed to get Component for Web");
        hr = ::StringCchCopyW(psw->wzComponent, countof(psw->wzComponent), pwzData);
        ExitOnFailure(hr, "Failed to copy component string to web object");
        if (*(psw->wzComponent))
        {
            psw->fHasComponent = TRUE;

            hr = WcaGetRecordInteger(hRec, wqInstalled, (int *)&psw->isInstalled);
            ExitOnFailure(hr, "Failed to get web Component's installed state");

            WcaGetRecordInteger(hRec, wqAction, (int *)&psw->isAction);
            ExitOnFailure(hr, "Failed to get web Component's action state");
        }

        // Get the web's description.
        hr = WcaGetRecordString(hRec, wqDescription, &pwzData);
        ExitOnFailure(hr, "Failed to get Description for Web");
        hr = ::StringCchCopyW(psw->wzDescription, countof(psw->wzDescription), pwzData);
        ExitOnFailure(hr, "Failed to copy description string to web object");

        //get web's site Id
        hr = WcaGetRecordInteger(hRec, wqId, &psw->iSiteId);
        ExitOnFailure(hr, "Failed to get SiteId for Web");

        // get the web's key address (Bindings)
        hr = WcaGetRecordString(hRec, wqAddress, &pwzData);
        ExitOnFailure(hr, "Failed to get Address for Web");
        hr = ::StringCchCopyW(psw->swaBinding.wzKey, countof(psw->swaBinding.wzKey), pwzData);
        ExitOnFailure(hr, "Failed to copy web binding key");

        hr = WcaGetRecordString(hRec, wqIP, &pwzData);
        ExitOnFailure(hr, "Failed to get IP for Web");
        hr = ::StringCchCopyW(psw->swaBinding.wzIP, countof(psw->swaBinding.wzIP), pwzData);
        ExitOnFailure(hr, "Failed to copy web IP");

        hr = WcaGetRecordString(hRec, wqPort, &pwzData);
        ExitOnFailure(hr, "Failed to get Web Address port");
        psw->swaBinding.iPort = wcstol(pwzData, NULL, 10);

        hr = WcaGetRecordString(hRec, wqHeader, &pwzData);
        ExitOnFailure(hr, "Failed to get Header for Web");
        hr = ::StringCchCopyW(psw->swaBinding.wzHeader, countof(psw->swaBinding.wzHeader), pwzData);
        ExitOnFailure(hr, "Failed to copy web header");

        hr = WcaGetRecordInteger(hRec, wqSecure, &psw->swaBinding.fSecure);
        ExitOnFailure(hr, "Failed to get if Web is secure");
        if (S_FALSE == hr)
        {
            psw->swaBinding.fSecure = FALSE;
        }

        // look to see if site exists
        dwLen = METADATA_MAX_NAME_LEN;
        hr = ScaWebFindBase7(*ppswList, psw->wzDescription);

        // If we didn't find a web in memory, ignore it - during execute CA
        // if the site truly does not exist then there will be an error.
        if (S_OK == hr)
        {
            // site exists in config
            psw->fBaseExists = TRUE;
        }
        else if (HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) == hr)
        {
            hr = S_OK;

            // site does not exists in config
            psw->fBaseExists = FALSE;
        }
        ExitOnFailure(hr, "Failed to find web site");

        // get any extra web addresses
        WcaFetchWrappedReset(hQueryWebAddress);

        while (S_OK == (hr = WcaFetchWrappedRecordWhereString(hQueryWebAddress, 2, psw->wzKey, &hRecAddresses)))
        {
            if (MAX_ADDRESSES_PER_WEB <= psw->cExtraAddresses)
            {
                hr = HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER);
                ExitOnFailure(hr, "Failure to get more extra web addresses, max exceeded.");
            }

            hr = WcaGetRecordString(hRecAddresses, waqAddress, &pwzData);
            ExitOnFailure(hr, "Failed to get extra web Address");

            // if this isn't the key address add it
            if (0 != lstrcmpW(pwzData, psw->swaBinding.wzKey))
            {
                hr = ::StringCchCopyW(psw->swaExtraAddresses[psw->cExtraAddresses].wzKey,
                    countof(psw->swaExtraAddresses[psw->cExtraAddresses].wzKey), pwzData);
                ExitOnFailure(hr, "Failed to copy web binding key");

                hr = WcaGetRecordString(hRecAddresses, waqIP, &pwzData);
                ExitOnFailure(hr, "Failed to get extra web IP");
                hr = ::StringCchCopyW(psw->swaExtraAddresses[psw->cExtraAddresses].wzIP, countof(psw->swaExtraAddresses[psw->cExtraAddresses].wzIP), pwzData);
                ExitOnFailure(hr, "Failed to copy web binding IP");

                hr = WcaGetRecordString(hRecAddresses, waqPort, &pwzData);
                ExitOnFailure(hr, "Failed to get port for extra web IP");
                psw->swaExtraAddresses[psw->cExtraAddresses].iPort= wcstol(pwzData, NULL, 10);

                // errno is set to ERANGE if overflow or underflow occurs
                _get_errno(&error);

                if (ERANGE == error)
                {
                    hr = E_INVALIDARG;
                    ExitOnFailure(hr, "Failed to convert web Port address");
                }

                hr = WcaGetRecordString(hRecAddresses, waqHeader, &pwzData);
                ExitOnFailure(hr, "Failed to get header for extra web IP");
                hr = ::StringCchCopyW(psw->swaExtraAddresses[psw->cExtraAddresses].wzHeader, countof(psw->swaExtraAddresses[psw->cExtraAddresses].wzHeader), pwzData);
                ExitOnFailure(hr, "Failed to copy web binding header");

                hr = WcaGetRecordInteger(hRecAddresses, waqSecure, &psw->swaExtraAddresses[psw->cExtraAddresses].fSecure);
                ExitOnFailure(hr, "Failed to get if secure extra web IP");
                if (S_FALSE == hr)
                {
                    psw->swaExtraAddresses[psw->cExtraAddresses].fSecure = FALSE;
                }

                ++psw->cExtraAddresses;
            }
        }

        if (E_NOMOREITEMS == hr)
        {
            hr = S_OK;
        }
        ExitOnFailure(hr, "Failure occured while getting extra web addresses");

        //
        // Connection time out
        //
        hr = WcaGetRecordInteger(hRec, wqConnectionTimeout, &psw->iConnectionTimeout);
        ExitOnFailure(hr, "Failed to get connection timeout for Web");

        if (psw->fHasComponent) // If we're installing it, it needs a dir
        {
            // get the web's directory
            if (INSTALLSTATE_SOURCE == psw->isAction)
            {
                hr = WcaGetRecordString(hRec, wqSourcePath, &pwzData);
            }
            else
            {
                hr = WcaGetRecordString(hRec, wqTargetPath, &pwzData);
            }
            ExitOnFailure(hr, "Failed to get Source/TargetPath for Directory");

            dwLen = lstrlenW(pwzData);
            // remove trailing backslash
            if (dwLen > 0 && pwzData[dwLen-1] == L'\\')
            {
                pwzData[dwLen-1] = 0;
            }
            hr = ::StringCchCopyW(psw->wzDirectory, countof(psw->wzDirectory), pwzData);
            ExitOnFailure1(hr, "Failed to copy web dir: '%ls'", pwzData);

        }

        hr = WcaGetRecordInteger(hRec, wqState, &psw->iState);
        ExitOnFailure(hr, "Failed to get state for Web");

        hr = WcaGetRecordInteger(hRec, wqAttributes, &psw->iAttributes);
        ExitOnFailure(hr, "Failed to get attributes for Web");

        // get the dir properties for this web
        hr = WcaGetRecordString(hRec, wqProperties, &pwzData);
        ExitOnFailure(hr, "Failed to get directory properties for Web");
        if (*pwzData)
        {
            hr = ScaGetWebDirProperties(pwzData, hUserQuery, hWebDirPropQuery, &psw->swp);
            ExitOnFailure(hr, "Failed to get directory properties for Web");

            psw->fHasProperties = TRUE;
        }

        // get the application information for this web
        hr = WcaGetRecordString(hRec, wqApplication, &pwzData);
        ExitOnFailure(hr, "Failed to get application identifier for Web");
        if (*pwzData)
        {
            hr = ScaGetWebApplication(NULL, pwzData, hWebAppQuery, hWebAppExtQuery, &psw->swapp);
            ExitOnFailure(hr, "Failed to get application for Web");

            psw->fHasApplication = TRUE;
        }

        // get the SSL certificates
        hr = ScaSslCertificateRead(psw->wzKey, hSslCertQuery, &(psw->pswscList));
        ExitOnFailure(hr, "Failed to get SSL Certificates.");

        // get the custom headers
        if (*ppshhList)
        {
            hr = ScaGetHttpHeader(hhptWeb, psw->wzKey, ppshhList, &(psw->pshhList));
            ExitOnFailure(hr, "Failed to get Custom HTTP Headers");
        }

        // get the errors
        if (*ppsweList)
        {
            hr = ScaGetWebError(weptWeb, psw->wzKey, ppsweList, &(psw->psweList));
            ExitOnFailure(hr, "Failed to get Custom Errors");
        }

        // get the log information for this web
        hr = WcaGetRecordString(hRec, wqLog, &pwzData);
        ExitOnFailure(hr, "Failed to get log identifier for Web");
        if (*pwzData)
        {
            hr = ScaGetWebLog7(pwzData, hWebLogQuery, &psw->swl);
            ExitOnFailure(hr, "Failed to get Log for Web.");
            psw->fHasLog = TRUE;
        }

        *ppswList = AddWebToList7(*ppswList, psw);
        psw = NULL; // set the web NULL so it doesn't accidentally get freed below
    }

    if (E_NOMOREITEMS == hr)
    {
        hr = S_OK;
    }

LExit:
    // if anything was left over after an error clean it all up
    WcaFinishUnwrapQuery(hQueryWebSite);
    WcaFinishUnwrapQuery(hQueryWebAddress);

    ScaWebsFreeList7(psw);

    ReleaseStr(pwzData);
    WcaLog(LOGMSG_VERBOSE, "Exiting ScaWebsRead7()");

    return hr;
}