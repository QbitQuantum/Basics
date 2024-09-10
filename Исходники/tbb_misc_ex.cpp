static void initialize_hardware_concurrency_info () {
#if __TBB_WIN8UI_SUPPORT
    // For these applications processor groups info is unavailable
    // Setting up a number of processors for one processor group
    theProcessorGroups[0].numProcs = theProcessorGroups[0].numProcsRunningTotal = std::thread::hardware_concurrency();
#else /* __TBB_WIN8UI_SUPPORT */
    dynamic_link( "Kernel32.dll", ProcessorGroupsApiLinkTable,
                  sizeof(ProcessorGroupsApiLinkTable)/sizeof(dynamic_link_descriptor) );
    SYSTEM_INFO si;
    GetNativeSystemInfo(&si);
    DWORD_PTR pam, sam, m = 1;
    GetProcessAffinityMask( GetCurrentProcess(), &pam, &sam );
    int nproc = 0;
    for ( size_t i = 0; i < sizeof(DWORD_PTR) * CHAR_BIT; ++i, m <<= 1 ) {
        if ( pam & m )
            ++nproc;
    }
    __TBB_ASSERT( nproc <= (int)si.dwNumberOfProcessors, NULL );
    // By default setting up a number of processors for one processor group
    theProcessorGroups[0].numProcs = theProcessorGroups[0].numProcsRunningTotal = nproc;
    // Setting up processor groups in case the process does not restrict affinity mask and more than one processor group is present
    if ( nproc == (int)si.dwNumberOfProcessors && TBB_GetActiveProcessorCount ) {
        // The process does not have restricting affinity mask and multiple processor groups are possible
        ProcessorGroupInfo::NumGroups = (int)TBB_GetActiveProcessorGroupCount();
        __TBB_ASSERT( ProcessorGroupInfo::NumGroups <= MaxProcessorGroups, NULL );
        // Fail safety bootstrap. Release versions will limit available concurrency
        // level, while debug ones would assert.
        if ( ProcessorGroupInfo::NumGroups > MaxProcessorGroups )
            ProcessorGroupInfo::NumGroups = MaxProcessorGroups;
        if ( ProcessorGroupInfo::NumGroups > 1 ) {
            TBB_GROUP_AFFINITY ga;
            if ( TBB_GetThreadGroupAffinity( GetCurrentThread(), &ga ) )
                ProcessorGroupInfo::HoleIndex = ga.Group;
            int nprocs = 0;
            for ( WORD i = 0; i < ProcessorGroupInfo::NumGroups; ++i ) {
                ProcessorGroupInfo  &pgi = theProcessorGroups[i];
                pgi.numProcs = (int)TBB_GetActiveProcessorCount(i);
                __TBB_ASSERT( pgi.numProcs <= (int)sizeof(DWORD_PTR) * CHAR_BIT, NULL );
                pgi.mask = pgi.numProcs == sizeof(DWORD_PTR) * CHAR_BIT ? ~(DWORD_PTR)0 : (DWORD_PTR(1) << pgi.numProcs) - 1;
                pgi.numProcsRunningTotal = nprocs += pgi.numProcs;
            }
            __TBB_ASSERT( nprocs == (int)TBB_GetActiveProcessorCount( TBB_ALL_PROCESSOR_GROUPS ), NULL );
        }
    }
#endif /* __TBB_WIN8UI_SUPPORT */

    PrintExtraVersionInfo("Processor groups", "%d", ProcessorGroupInfo::NumGroups);
    if (ProcessorGroupInfo::NumGroups>1)
        for (int i=0; i<ProcessorGroupInfo::NumGroups; ++i)
            PrintExtraVersionInfo( "----- Group", "%d: size %d", i, theProcessorGroups[i].numProcs);
}