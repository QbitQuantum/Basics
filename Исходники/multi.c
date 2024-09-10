CURLMcode __stdcall vbcurl_multi_remove_handle(MULTI_CONTEXT* pmc,
    void* pvEasyContext)
{
    void* pvEasy;
    if (pmc->_magic != MULTI_MAGIC)
        RaiseException(0xE0000000, EXCEPTION_NONCONTINUABLE, 0, NULL);
    pvEasy = easy_get_inner(pvEasyContext);
    if (!pvEasy)
        return CURLM_BAD_EASY_HANDLE;
    return curl_multi_remove_handle(pmc->_multi, pvEasy);
}