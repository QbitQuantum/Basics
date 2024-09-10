/*==========================================================================*/
size_t SystemInformation::FreeMemorySize()
{
// Windows
#if defined ( KVS_PLATFORM_WINDOWS )
#if defined ( KVS_PLATFORM_CPU_64 )
    MEMORYSTATUSEX memstat;
    GlobalMemoryStatusEx( &memstat );
    return memstat.ullAvailPhys;
#else
    MEMORYSTATUS memstat;
    GlobalMemoryStatus( &memstat );
    return memstat.dwAvailPhys;
#endif

// Linux
#elif defined ( KVS_PLATFORM_LINUX ) || defined ( KVS_PLATFORM_CYGWIN )
    long avphys_page_size = sysconf( _SC_AVPHYS_PAGES );
    kvsMessageWarning( avphys_page_size != -1,
                       ::GetWarningMessage( errno, "_SC_AVPHYS_PAGES is not supported." ) );

    long page_size = sysconf( _SC_PAGESIZE );
    kvsMessageWarning( page_size != -1,
                       ::GetWarningMessage( errno, "_SC_PAGESIZE is not supported." ) );

    return avphys_page_size * page_size;

// Mac OS X
#elif defined ( KVS_PLATFORM_MACOSX )
    kern_return_t kr;

    vm_size_t page_size = 0;
    kr = host_page_size( mach_host_self(), &page_size );
    kvsMessageWarning( kr != KERN_SUCCESS, "Failure to get page size." );

    vm_statistics_data_t   page_info;
    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
    kr = host_statistics( mach_host_self(), HOST_VM_INFO, (host_info_t)&page_info, &count );
    kvsMessageWarning( kr != KERN_SUCCESS, "Failure to get page info." );

    return page_info.free_count * page_size;
#endif

}