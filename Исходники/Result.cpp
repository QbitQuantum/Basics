void ClearResultCache()
{
    ATLTRACE(_T("Result cache before clearing(size=%u)\r\n"), ResultCache.Size());
    ResultCache.Clear();
}