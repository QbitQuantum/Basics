int OGRDXFWriterDS::FixupHANDSEED( VSILFILE *fp )

{
/* -------------------------------------------------------------------- */
/*      What is a good next handle seed?  Scan existing values.         */
/* -------------------------------------------------------------------- */
    unsigned int   nHighestHandle = 0;
    std::set<CPLString>::iterator it;

    for( it = aosUsedEntities.begin(); it != aosUsedEntities.end(); it++ ) 
    {
        unsigned int nHandle;
        if( sscanf( (*it).c_str(), "%x", &nHandle ) == 1 )
        {
            if( nHandle > nHighestHandle )
                nHighestHandle = nHandle;
        }
    }

/* -------------------------------------------------------------------- */
/*      Read the existing handseed value, replace it, and write back.   */
/* -------------------------------------------------------------------- */
    char szWorkBuf[30];
    int  i = 0;

    if( nHANDSEEDOffset == 0 )
        return FALSE;

    VSIFSeekL( fp, nHANDSEEDOffset, SEEK_SET );
    VSIFReadL( szWorkBuf, 1, sizeof(szWorkBuf), fp );
    
    while( szWorkBuf[i] != '\n' )
        i++;

    i++;
    if( szWorkBuf[i] == '\r' )
        i++;
    
    CPLString osNewValue;

    osNewValue.Printf( "%08X", nHighestHandle + 1 );
    strncpy( szWorkBuf + i, osNewValue.c_str(), osNewValue.size() );

    VSIFSeekL( fp, nHANDSEEDOffset, SEEK_SET );
    VSIFWriteL( szWorkBuf, 1, sizeof(szWorkBuf), fp );

    return TRUE;
}