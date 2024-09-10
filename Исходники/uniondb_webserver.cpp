long WINAPI ExceptionFilter(EXCEPTION_POINTERS * lParam)
{
    //DateTime dateTime(GetCurDateTime());
    char strFileName[64] = "leeloo_webserver.dmp";
    //std::string stdstrDumpName = ConfigSingleton::Instance().GetItem(ICEARK_DUMPNAME_SYSTEM_CONFIG);
    //if(stdstrDumpName.compare(ICEARK_BLANK_SYSTEM_CONFIG) == 0)
    //    stdstrDumpName = "iceark";
    //std::string stdstrOutputpath = ConfigSingleton::Instance().GetItem(ICEARK_OUTPUTPATH_SYSTEM_CONFIG);
    //if(stdstrOutputpath.compare(ICEARK_BLANK_SYSTEM_CONFIG) == 0)
    //    sprintf(strFileName, "dump_%s_%04d_%02d_%02d_%02d_%02d_%02d.dmp", stdstrDumpName.c_str(), dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.second());
    //else
    //    sprintf(strFileName, "%sdump_%s_%04d_%02d_%02d_%02d_%02d_%02d.dmp", stdstrOutputpath.c_str(), stdstrDumpName.c_str(), dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.second());
    //strFileName = "ztcache.dmp";
    HANDLE hFile = ::CreateFile( strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if( hFile != INVALID_HANDLE_VALUE)
    {
            MINIDUMP_EXCEPTION_INFORMATION einfo;
            einfo.ThreadId = ::GetCurrentThreadId();
            einfo.ExceptionPointers = lParam;
            einfo.ClientPointers = FALSE;
            MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, &einfo, NULL, NULL);
            CloseHandle(hFile);
    }
    return EXCEPTION_EXECUTE_HANDLER;
}