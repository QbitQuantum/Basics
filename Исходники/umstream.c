void UMCloseCacheFileStream(IUMCacheStream *This)
{
    if (!This->closed)
    {
       FILETIME ftZero;

       ftZero.dwLowDateTime = ftZero.dwHighDateTime = 0;

       This->closed = 1;
       CommitUrlCacheEntryW(This->pszURL,
                            This->pszFileName,
                            ftZero,
                            ftZero,
                            NORMAL_CACHE_ENTRY,
                            0,
                            0,
                            0,
                            0);
    }
}