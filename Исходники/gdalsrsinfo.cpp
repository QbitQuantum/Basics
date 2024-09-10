int SearchCSVForWKT( const char *pszFileCSV, const char *pszTarget )
{
    const char *pszFilename = NULL;
    const char *pszWKT = NULL;
    char szTemp[1024];
    int nPos = 0;
    const char *pszTemp = NULL;

    VSILFILE *fp = NULL;
    OGRSpatialReference oSRS;
    int nCode = 0;
    int nFound = -1;

    CPLDebug( "gdalsrsinfo", 
              "SearchCSVForWKT()\nfile=%s\nWKT=%s\n",
              pszFileCSV, pszTarget);

/* -------------------------------------------------------------------- */
/*      Find and open file.                                             */
/* -------------------------------------------------------------------- */
    // pszFilename = pszFileCSV;
    pszFilename = CPLFindFile( "gdal", pszFileCSV );
    if( pszFilename == NULL )
    {
        CPLDebug( "gdalsrsinfo", "could not find support file %s",
                   pszFileCSV );
        // return OGRERR_UNSUPPORTED_SRS;
        return -1;
    }

    /* support gzipped file */
    if ( strstr( pszFileCSV,".gz") != NULL )
        sprintf( szTemp, "/vsigzip/%s", pszFilename);
    else
        sprintf( szTemp, "%s", pszFilename);

    CPLDebug( "gdalsrsinfo", "SearchCSVForWKT() using file %s",
              szTemp );

    fp = VSIFOpenL( szTemp, "r" );
    if( fp == NULL ) 
    {
        CPLDebug( "gdalsrsinfo", "could not open support file %s",
                  pszFilename );

        // return OGRERR_UNSUPPORTED_SRS;
        return -1;
    }

/* -------------------------------------------------------------------- */
/*      Process lines.                                                  */
/* -------------------------------------------------------------------- */
    const char *pszLine;

    while( (pszLine = CPLReadLine2L(fp,-1,NULL)) != NULL )

    {
        // CPLDebug( "gdalsrsinfo", "read line %s", pszLine );

        if( pszLine[0] == '#' )
            continue;
            /* do nothing */;

        // else if( EQUALN(pszLine,"include ",8) )
        // {
        //     eErr = importFromDict( pszLine + 8, pszCode );
        //     if( eErr != OGRERR_UNSUPPORTED_SRS )
        //         break;
        // }

        // else if( strstr(pszLine,",") == NULL )
        //     /* do nothing */;

        pszTemp = strstr(pszLine,",");
        if (pszTemp)
        {
            nPos = pszTemp - pszLine;

            if ( nPos == 0 )
                continue;
            
            strncpy( szTemp, pszLine, nPos );
            szTemp[nPos] = '\0';
            nCode = atoi(szTemp);

            pszWKT = (char *) pszLine + nPos +1;

            // CPLDebug( "gdalsrsinfo", 
            //           "code=%d\nWKT=\n[%s]\ntarget=\n[%s]\n",
            //           nCode,pszWKT, pszTarget );

            if ( EQUAL(pszTarget,pszWKT) )
            {
                nFound = nCode;
                CPLDebug( "gdalsrsinfo", "found EPSG:%d\n"
                          "current=%s\ntarget= %s\n",
                          nCode, pszWKT, pszTarget );
                break;
            }
        }
    }
    
    VSIFCloseL( fp );

    return nFound;

}