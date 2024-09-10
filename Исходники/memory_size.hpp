inline int64_t memory_available()
{

#if defined( ZI_OS_LINUX )

    int64_t page_size = static_cast< uint32_t >( sysconf( _SC_PAGE_SIZE ) );
    return page_size * sysconf( _SC_AVPHYS_PAGES );

#elif defined( ZI_OS_MACOS )

    return memory_size();

#elif defined ( ZI_OS_WINDOWS )

#ifdef WIN64
    MEMORYSTATUSEX ms;
#else
    MEMORYSTATUS ms;
#endif

    ms.dwLength = sizeof(ms);
    GlobalMemoryStatus(&ms);

#ifdef WIN64
    return static_cast< int64_t >( ms.ullAvailPhys );
#else
    return static_cast< int64_t >( ms.dwAvailPhys );
#endif

#else
#warning "no memory_size function available"
#endif

}