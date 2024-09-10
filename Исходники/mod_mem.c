static int modmem_memory_total( INSTANCE * my, int * params )
{
#ifdef WIN32
    MEMORYSTATUS mem ;
    GlobalMemoryStatus( &mem ) ;
    return mem.dwTotalPhys ;

#elif defined(TARGET_BEOS)
    system_info info;
    get_system_info( &info );
    return  B_PAGE_SIZE * ( info.max_pages );

#elif !defined(TARGET_MAC) && !defined(TARGET_WII)
    /* Linux and other Unix (?) */
    struct sysinfo meminf;
    int fv;

    if ( sysinfo( &meminf ) == -1 ) return -1;

    if ( !( fv = kernel_version_type() ) ) return -1;

    if ( fv == 1 )
        return meminf.totalram * meminf.mem_unit;
    else
        return meminf.totalram;

    return -1;

#else
    return 0; //TODO

#endif
}