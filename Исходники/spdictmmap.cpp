int munmap(void *start, size_t length)
{
    int i, j;

    for( i = 0; i < g_curMMapInfos; i++ ) {
        if( g_mmapInfos[i].start == start )
            break;
    }
    if( i == g_curMMapInfos ) {
        _set_errno( EINVAL );
        return -1;
    }

    UnmapViewOfFile( g_mmapInfos[g_curMMapInfos].start );
    CloseHandle( g_mmapInfos[g_curMMapInfos].hMap );
    CloseHandle( g_mmapInfos[g_curMMapInfos].hFile );

    EnterCriticalSection( &cs );
    for( j = i + 1; j < g_curMMapInfos; j++ ) {
        memcpy( &g_mmapInfos[ j - 1 ], &g_mmapInfos[ j ],
                sizeof( struct mmapInfos ) );
    }
    g_curMMapInfos--;
    
    if( g_curMMapInfos == 0 ) {
        free( g_mmapInfos );
        g_mmapInfos = NULL;
        g_maxMMapInfos = 0;
    }
    LeaveCriticalSection( &cs );
    
    return 0;
}