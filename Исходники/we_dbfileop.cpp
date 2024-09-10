/***********************************************************
 * DESCRIPTION: 
 *    Core function for writing data w/o using VB cache
 *    (bulk load dictionary store inserts)
 ***********************************************************/
int DbFileOp::writeDBFileNoVBCache( IDBDataFile* pFile,
                                    const unsigned char* writeBuf,
                                    const int fbo,
                                    const int numOfBlock  )
{
#ifdef PROFILE
    // This function is only used by bulk load for dictionary store files,
    // so we log as such.
    Stats::startParseEvent(WE_STATS_WRITE_DCT);
#endif

    for( int i = 0; i < numOfBlock; i++ ) {
        Stats::incIoBlockWrite();
        RETURN_ON_ERROR( writeFile( pFile, writeBuf, BYTE_PER_BLOCK ) );
    }

#ifdef PROFILE
    Stats::stopParseEvent(WE_STATS_WRITE_DCT);
#endif

    return NO_ERROR;
}