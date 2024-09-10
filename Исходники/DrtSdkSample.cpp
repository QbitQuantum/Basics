bool PerformDrtSearch(DRT_CONTEXT* Drt, INT SearchType)
{
    HRESULT hr = S_OK;
    DWORD dwSize = 1024;
    bool fKeyFound = FALSE;
    DRT_SEARCH_INFO SearchInfo = {0};
    DRT_SEARCH_INFO* pSearchInfo = NULL;
    HDRT_SEARCH_CONTEXT SearchContext = {0};
    DRT_SEARCH_RESULT *pSearchResult = NULL;
    BYTE searchKeyData[KEYSIZE] = {0};
    BYTE minKeyData[KEYSIZE] = {0};
    BYTE maxKeyData[KEYSIZE] = {0};
    DRT_DATA searchKey = {0};
    DRT_DATA minKey = {0};
    DRT_DATA maxKey = {0};

    //Create a manual reset event 
    //The DRT will reset the event when the search result buffer has been consumed
    HANDLE hDrtSearchEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if(NULL == hDrtSearchEvent)
    {
        wprintf(L"Out of memory\n");
        goto Cleanup;
    }
        

    //Set Some Defaults for SearchInfo
    SearchInfo.dwSize = sizeof(DRT_SEARCH_INFO);
    SearchInfo.fIterative = FALSE;
    SearchInfo.fAllowCurrentInstanceMatch = TRUE;
    SearchInfo.fAnyMatchInRange = FALSE;
    SearchInfo.cMaxEndpoints = 1;
    SearchInfo.pMinimumKey = &minKey;
    SearchInfo.pMaximumKey = &maxKey;

    searchKey.cb = KEYSIZE;
    searchKey.pb = searchKeyData;
    minKey.cb = KEYSIZE;
    minKey.pb = minKeyData;
    maxKey.cb = KEYSIZE;
    maxKey.pb = maxKeyData;

    if(!GetKeyFromUser(L"Search Key",searchKeyData))
        goto Cleanup;

    if(SearchType==2) //Simple DRT Search
    {
        pSearchInfo = NULL;
    }
    else if(SearchType==3) //Nearest Match Search
    {
        SearchInfo.fAnyMatchInRange = FALSE;
        pSearchInfo = &SearchInfo;
        memset(minKeyData,0,KEYSIZE);
        memset(maxKeyData,0xFF,KEYSIZE);
    }
    else if(SearchType==4) //Iterative Search
    {
        SearchInfo.fIterative = TRUE;
        pSearchInfo = &SearchInfo;
        minKey.pb = searchKey.pb;
        maxKey.pb = searchKey.pb;
    }
    else if(SearchType==5) //Range Search
    {
        SearchInfo.fAnyMatchInRange = TRUE;
        if(!GetKeyFromUser(L"Min Search Key (01 z)",minKeyData))
            goto Cleanup;
        if(!GetKeyFromUser(L"Max Search Key (ff z)",maxKeyData))
            goto Cleanup;
        pSearchInfo = &SearchInfo;
    }
    else
    {
        wprintf(L"Invalid Search Type passed to DrtPerformSearch");
        goto Cleanup;
    }

    hr = DrtStartSearch(
        Drt->hDrt, 
        &searchKey, 
        pSearchInfo, 
        5000, 
        hDrtSearchEvent, 
        NULL, 
        &SearchContext);

    VERIFY_OR_ABORT("DrtStartSearch",hr);

    do
    {
        DWORD dwRes = WaitForSingleObject(hDrtSearchEvent, 30*1000);

        if(dwRes == WAIT_OBJECT_0)
        {
            hr = DrtGetSearchResultSize(SearchContext,&dwSize);
            if(hr != S_OK)
            {
                continue;
            }
            pSearchResult = (DRT_SEARCH_RESULT*)malloc(dwSize);
            if(pSearchResult == NULL)
            {
                wprintf(L"Error: Out of memory\n");
                break;
            }
            hr = DrtGetSearchResult(SearchContext, dwSize, pSearchResult);
            if(hr != S_OK)
            {
                continue;
            }
            if(pSearchResult->type == DRT_MATCH_EXACT)
            {
                fKeyFound = TRUE;
                wprintf(L"*Found Key*: ");
                for(int i=pSearchResult->registration.key.cb-1;i>=0;i--)
                    wprintf(L"%02x ",pSearchResult->registration.key.pb[i]);
                wprintf(L"\n");
                PrintSearchPath(SearchContext);
            }
            else if(pSearchResult->type == DRT_MATCH_NEAR)
            {
                wprintf(L"*Found Near Match*: ");
                for(int i=pSearchResult->registration.key.cb-1;i>=0;i--)
                    wprintf(L"%02x ",pSearchResult->registration.key.pb[i]);
                wprintf(L"\n");
                if(SearchType==3)
                    fKeyFound = TRUE;
                PrintSearchPath(SearchContext);
            }
            else if(pSearchResult->type == DRT_MATCH_INTERMEDIATE)
            {
                wprintf(L"Intermediate Match: ");
                for(int i=pSearchResult->registration.key.cb-1;i>=0;i--)
                    wprintf(L"%02x ",pSearchResult->registration.key.pb[i]);
                wprintf(L"\n");
                DrtContinueSearch(SearchContext);
            }
        }
        else
        {
            wprintf(L"Drt Search Timed out\n");
            break;
        }
        if(pSearchResult)
        {
            free(pSearchResult);
            pSearchResult = NULL;
        }
    } while( (hr == DRT_E_SEARCH_IN_PROGRESS) || (hr == S_OK) );
    DrtEndSearch(SearchContext);

    //
    // When the search is finished, the HRESULT should be DRT_E_NO_MORE
    //
    if(hr != DRT_E_NO_MORE)
    {
        wprintf(L"Unexpected HRESULT from DrtGetSearchResult: 0x%x\n",hr);
    }

    if(!fKeyFound)
        wprintf(L"Could not find key\n");
    
Cleanup:
    if(pSearchResult)
        free(pSearchResult);
    if (hDrtSearchEvent)
        CloseHandle(hDrtSearchEvent);
        
    return true;
}