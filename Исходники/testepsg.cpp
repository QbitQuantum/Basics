int main( int nArgc, char ** papszArgv )

{
    OGRSpatialReference oSRS;
    int i;
    int bReportXML = FALSE;

    /* -------------------------------------------------------------------- */
    /*      Processing command line arguments.                              */
    /* -------------------------------------------------------------------- */
    nArgc = OGRGeneralCmdLineProcessor( nArgc, &papszArgv, 0 );

    if( nArgc < 2 )
        Usage();

    for( i = 1; i < nArgc; i++ )
    {
        if( EQUAL(papszArgv[i],"-xml") )
            bReportXML = TRUE;

        else if( EQUAL(papszArgv[i],"-t") && i < nArgc - 4 )
        {
            OGRSpatialReference oSourceSRS, oTargetSRS;
            OGRCoordinateTransformation *poCT;
            double                      x, y, z_orig, z;
            int                         nArgsUsed = 4;

            if( oSourceSRS.SetFromUserInput(papszArgv[i+1]) != OGRERR_NONE )
            {
                CPLError( CE_Failure, CPLE_AppDefined,
                          "SetFromUserInput(%s) failed.",
                          papszArgv[i+1] );
                continue;
            }
            if( oTargetSRS.SetFromUserInput(papszArgv[i+2]) != OGRERR_NONE )
            {
                CPLError( CE_Failure, CPLE_AppDefined,
                          "SetFromUserInput(%s) failed.",
                          papszArgv[i+2] );
                continue;
            }

            poCT = OGRCreateCoordinateTransformation( &oSourceSRS,
                    &oTargetSRS );
            x = CPLAtof( papszArgv[i+3] );
            y = CPLAtof( papszArgv[i+4] );
            if( i < nArgc - 5
                    && (CPLAtof(papszArgv[i+5]) > 0.0 || papszArgv[i+5][0] == '0') )
            {
                z_orig = z = CPLAtof(papszArgv[i+5]);
                nArgsUsed++;
            }
            else
                z_orig = z = 0;

            if( poCT == NULL || !poCT->Transform( 1, &x, &y, &z ) )
                printf( "Transformation failed.\n" );
            else
                printf( "(%f,%f,%f) -> (%f,%f,%f)\n",
                        CPLAtof( papszArgv[i+3] ),
                        CPLAtof( papszArgv[i+4] ),
                        z_orig,
                        x, y, z );

            i += nArgsUsed;
        }
        else
        {
            /* coverity[tainted_data] */
            if( oSRS.SetFromUserInput(papszArgv[i]) != OGRERR_NONE )
                CPLError( CE_Failure, CPLE_AppDefined,
                          "Error occurred translating %s.\n",
                          papszArgv[i] );
            else
            {
                char  *pszWKT = NULL;

                if( oSRS.Validate() != OGRERR_NONE )
                    printf( "Validate Fails.\n" );
                else
                    printf( "Validate Succeeds.\n" );

                oSRS.exportToPrettyWkt( &pszWKT, FALSE );
                printf( "WKT[%s] =\n%s\n",
                        papszArgv[i], pszWKT );
                CPLFree( pszWKT );

                printf( "\n" );

                oSRS.exportToPrettyWkt( &pszWKT, TRUE );
                printf( "Simplified WKT[%s] =\n%s\n",
                        papszArgv[i], pszWKT );
                CPLFree( pszWKT );

                printf( "\n" );

                OGRSpatialReference *poSRS2;

                poSRS2 = oSRS.Clone();
                poSRS2->StripCTParms();
                poSRS2->exportToWkt( &pszWKT );
                printf( "Old Style WKT[%s] = %s\n",
                        papszArgv[i], pszWKT );
                CPLFree( pszWKT );
                OGRSpatialReference::DestroySpatialReference( poSRS2 );

                poSRS2 = oSRS.Clone();
                poSRS2->morphToESRI();
                poSRS2->exportToPrettyWkt( &pszWKT, FALSE );
                printf( "ESRI'ified WKT[%s] = \n%s\n",
                        papszArgv[i], pszWKT );
                CPLFree( pszWKT );
                OGRSpatialReference::DestroySpatialReference( poSRS2 );

                oSRS.exportToProj4( &pszWKT );
                printf( "PROJ.4 rendering of [%s] = %s\n",
                        papszArgv[i], pszWKT );
                CPLFree( pszWKT );


                if( bReportXML )
                {
                    char       *pszRawXML;
                    if( oSRS.exportToXML(&pszRawXML) == OGRERR_NONE )
                    {
                        printf( "XML[%s] =\n%s\n",
                                papszArgv[i], pszRawXML );
                        CPLFree( pszRawXML );
                    }
                    else
                    {
                        printf( "XML translation failed\n" );
                    }
                }

                printf( "\n" );
            }
        }
    }

    CSLDestroy( papszArgv );
    OSRCleanup();
    CPLFinderClean();
    CPLCleanupTLS();

    return 0;
}