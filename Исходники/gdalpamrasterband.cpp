CPLXMLNode *
PamHistogramToXMLTree( double dfMin, double dfMax,
                       int nBuckets, GUIntBig * panHistogram,
                       int bIncludeOutOfRange, int bApprox )

{
    if( nBuckets > (INT_MAX - 10) / 12 )
        return nullptr;

    const size_t nLen = 22 * static_cast<size_t>(nBuckets) + 10;
    char *pszHistCounts = static_cast<char *>( VSIMalloc(nLen) );
    if( pszHistCounts == nullptr )
        return nullptr;

    CPLXMLNode *psXMLHist = CPLCreateXMLNode( nullptr, CXT_Element, "HistItem" );

    CPLString oFmt;
    CPLSetXMLValue( psXMLHist, "HistMin",
                    oFmt.Printf( "%.16g", dfMin ));
    CPLSetXMLValue( psXMLHist, "HistMax",
                    oFmt.Printf( "%.16g", dfMax ));
    CPLSetXMLValue( psXMLHist, "BucketCount",
                    oFmt.Printf( "%d", nBuckets ));
    CPLSetXMLValue( psXMLHist, "IncludeOutOfRange",
                    oFmt.Printf( "%d", bIncludeOutOfRange ));
    CPLSetXMLValue( psXMLHist, "Approximate",
                    oFmt.Printf( "%d", bApprox ));

    size_t iHistOffset = 0;
    pszHistCounts[0] = '\0';
    for( int iBucket = 0; iBucket < nBuckets; iBucket++ )
    {
        snprintf( pszHistCounts + iHistOffset,
                  nLen - iHistOffset,
                  CPL_FRMT_GUIB, panHistogram[iBucket] );
        if( iBucket < nBuckets-1 )
            strcat( pszHistCounts + iHistOffset, "|" );
        iHistOffset += strlen(pszHistCounts+iHistOffset);
    }

    CPLSetXMLValue( psXMLHist, "HistCounts", pszHistCounts );
    CPLFree( pszHistCounts );

    return psXMLHist;
}