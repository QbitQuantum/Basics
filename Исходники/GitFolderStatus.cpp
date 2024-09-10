const FileStatusCacheEntry * GitFolderStatus::GetCachedItem(const CTGitPath& filepath)
{
    sCacheKey.assign(filepath.GetWinPath());
    FileStatusMap::const_iterator iter;
    const FileStatusCacheEntry *retVal;

    if(m_mostRecentPath.IsEquivalentTo(CTGitPath(sCacheKey.c_str())))
    {
        // We've hit the same result as we were asked for last time
        ATLTRACE2(_T("fast cache hit for %s\n"), filepath);
        retVal = m_mostRecentStatus;
    }
    else if ((iter = m_cache.find(sCacheKey)) != m_cache.end())
    {
        ATLTRACE2(_T("cache found for %s\n"), filepath);
        retVal = &iter->second;
        m_mostRecentStatus = retVal;
        m_mostRecentPath = CTGitPath(sCacheKey.c_str());
    }
    else
    {
        retVal = NULL;
    }

    if(retVal != NULL)
    {
        // We found something in a cache - check that the cache is not timed-out or force-invalidated
        DWORD now = GetTickCount();

        if ((now >= m_TimeStamp)&&((now - m_TimeStamp) > GetTimeoutValue()))
        {
            // Cache is timed-out
            ATLTRACE("Cache timed-out\n");
            ClearCache();
            retVal = NULL;
        }
        else if(WaitForSingleObject(m_hInvalidationEvent, 0) == WAIT_OBJECT_0)
        {
            // TortoiseProc has just done something which has invalidated the cache
            ATLTRACE("Cache invalidated\n");
            ClearCache();
            retVal = NULL;
        }
        return retVal;
    }
    return NULL;
}