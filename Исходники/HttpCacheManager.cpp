void CHttpCacheManager::CreateVssCacheL( CRepository& aRepository, const TDesC& aVssCacheFolder, const TInt& aVssCacheSize, const TInt& aCriticalLevel, const THttpCachePostponeParameters& aPostpone )
    {
    //Get the white list
    TBuf<2048> whiteList;
    
    if (aRepository.Get(KPhoneSpecificCacheDomainUrl, whiteList) == KErrNone)
        {
        iVSSWhiteList = HBufC8::NewL(whiteList.Length());
        iVSSWhiteList->Des().Append(whiteList);
        }
    else
        {
        iVSSWhiteList = NULL;
        }
    
    // create cache handler
    iphoneSpecificCache = CHttpCacheHandler::NewL(aVssCacheSize, aVssCacheFolder, KDefaultVSSIndexFile(), aCriticalLevel, aPostpone);
    }