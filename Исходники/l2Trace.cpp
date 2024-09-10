 unsigned long long CTraceFn::ThreadTime()
 {
    unsigned long long ret( 0 );
    
    FILETIME creationTime;
    FILETIME exitTime;
    FILETIME kernelTime;
    FILETIME userTime;
    
    if( GetThreadTimes( GetCurrentThread(), &creationTime, &exitTime, &kernelTime, &userTime ) )
    {
       unsigned long long theKernelTime( static_cast< unsigned long long >( kernelTime.dwHighDateTime ) << 32 | kernelTime.dwLowDateTime );
       unsigned long long theUserTime( static_cast< unsigned long long >( userTime.dwHighDateTime ) << 32 | userTime.dwLowDateTime );
       
       ret = ( theKernelTime + theUserTime );
    }
    
    return ret;
 }