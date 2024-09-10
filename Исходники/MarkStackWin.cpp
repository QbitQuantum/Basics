void MarkStack::initializePagesize()
{
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    MarkStack::s_pageSize = system_info.dwPageSize;
}