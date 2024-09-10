 int ProcessInfo::getResidentSize() {
     PROCESS_MEMORY_COUNTERS pmc;
     verify( 16051, GetProcessMemoryInfo( GetCurrentProcess() , &pmc, sizeof(pmc) ) );
     return _wconvertmtos( pmc.WorkingSetSize );
 }