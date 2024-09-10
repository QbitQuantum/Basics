bool OGRShapeDataSource::Open( GDALOpenInfo* poOpenInfo,
                              bool bTestOpen, bool bForceSingleFileDataSource )

{
    CPLAssert( nLayers == 0 );

    const char * pszNewName = poOpenInfo->pszFilename;
    const bool bUpdate = poOpenInfo->eAccess == GA_Update;
    papszOpenOptions = CSLDuplicate( poOpenInfo->papszOpenOptions );

    pszName = CPLStrdup( pszNewName );

    bDSUpdate = bUpdate;

    bSingleFileDataSource = CPL_TO_BOOL(bForceSingleFileDataSource);

/* -------------------------------------------------------------------- */
/*      If bSingleFileDataSource is TRUE we don't try to do anything    */
/*      else.                                                           */
/*      This is only utilized when the OGRShapeDriver::Create()         */
/*      method wants to create a stub OGRShapeDataSource for a          */
/*      single shapefile.  The driver will take care of creating the    */
/*      file by calling ICreateLayer().                                 */
/* -------------------------------------------------------------------- */
    if( bSingleFileDataSource )
        return true;

/* -------------------------------------------------------------------- */
/*      Is the given path a directory or a regular file?                */
/* -------------------------------------------------------------------- */
    if( !poOpenInfo->bStatOK )
    {
        if( !bTestOpen )
            CPLError( CE_Failure, CPLE_AppDefined,
                      "%s is neither a file or directory, Shape access failed.",
                      pszNewName );

        return false;
    }

/* -------------------------------------------------------------------- */
/*      Build a list of filenames we figure are Shape files.            */
/* -------------------------------------------------------------------- */
    if( !poOpenInfo->bIsDirectory )
    {
        if( !OpenFile( pszNewName, bUpdate ) )
        {
            if( !bTestOpen )
                CPLError(
                    CE_Failure, CPLE_OpenFailed,
                    "Failed to open shapefile %s.  "
                    "It may be corrupt or read-only file accessed in "
                    "update mode.",
                    pszNewName );

            return false;
        }

        bSingleFileDataSource = true;

        return true;
    }
    else
    {
        char **papszCandidates = VSIReadDir( pszNewName );
        const int nCandidateCount = CSLCount( papszCandidates );
        bool bMightBeOldCoverage = false;
        std::set<CPLString> osLayerNameSet;

        for( int iCan = 0; iCan < nCandidateCount; iCan++ )
        {
            const char *pszCandidate = papszCandidates[iCan];
            const char *pszLayerName = CPLGetBasename(pszCandidate);
            CPLString osLayerName(pszLayerName);
#ifdef WIN32
            // On Windows, as filenames are case insensitive, a shapefile layer
            // can be made of foo.shp and FOO.DBF, so to detect unique layer
            // names, put them upper case in the unique set used for detection.
            osLayerName.toupper();
#endif

            if( EQUAL(pszCandidate,"ARC") )
                bMightBeOldCoverage = true;

            if( strlen(pszCandidate) < 4
                || !EQUAL(pszCandidate+strlen(pszCandidate)-4,".shp") )
                continue;

            char *pszFilename =
                CPLStrdup(CPLFormFilename(pszNewName, pszCandidate, NULL));

            osLayerNameSet.insert(osLayerName);
#ifdef IMMEDIATE_OPENING
            if( !OpenFile( pszFilename, bUpdate )
                && !bTestOpen )
            {
                CPLError(
                    CE_Failure, CPLE_OpenFailed,
                    "Failed to open shapefile %s.  "
                    "It may be corrupt or read-only file accessed in "
                    "update mode.",
                    pszFilename );
                CPLFree( pszFilename );
                CSLDestroy( papszCandidates );
                return false;
            }
#else
            oVectorLayerName.push_back(pszFilename);
#endif
            CPLFree( pszFilename );
        }

        // Try and .dbf files without apparent associated shapefiles.
        for( int iCan = 0; iCan < nCandidateCount; iCan++ )
        {
            const char  *pszCandidate = papszCandidates[iCan];
            const char  *pszLayerName = CPLGetBasename(pszCandidate);
            CPLString osLayerName(pszLayerName);
#ifdef WIN32
            osLayerName.toupper();
#endif

            // We don't consume .dbf files in a directory that looks like
            // an old style Arc/Info (for PC?) that unless we found at least
            // some shapefiles.  See Bug 493.
            if( bMightBeOldCoverage && osLayerNameSet.size() == 0 )
                continue;

            if( strlen(pszCandidate) < 4
                || !EQUAL(pszCandidate+strlen(pszCandidate)-4, ".dbf") )
                continue;

            if( osLayerNameSet.find(osLayerName) != osLayerNameSet.end() )
                continue;

            // We don't want to access .dbf files with an associated .tab
            // file, or it will never get recognised as a mapinfo dataset.
            bool bFoundTAB = false;
            for( int iCan2 = 0; iCan2 < nCandidateCount; iCan2++ )
            {
                const char *pszCandidate2 = papszCandidates[iCan2];

                if( EQUALN(pszCandidate2, pszLayerName, strlen(pszLayerName))
                    && EQUAL(pszCandidate2 + strlen(pszLayerName), ".tab") )
                    bFoundTAB = true;
            }

            if( bFoundTAB )
                continue;

            char *pszFilename =
                CPLStrdup(CPLFormFilename(pszNewName, pszCandidate, NULL));

            osLayerNameSet.insert(osLayerName);

#ifdef IMMEDIATE_OPENING
            if( !OpenFile( pszFilename, bUpdate )
                && !bTestOpen )
            {
                CPLError(
                    CE_Failure, CPLE_OpenFailed,
                    "Failed to open dbf file %s.  "
                    "It may be corrupt or read-only file accessed in "
                    "update mode.",
                    pszFilename );
                CPLFree( pszFilename );
                CSLDestroy( papszCandidates );
                return false;
            }
#else
            oVectorLayerName.push_back(pszFilename);
#endif
            CPLFree( pszFilename );
        }

        CSLDestroy( papszCandidates );

#ifdef IMMEDIATE_OPENING
        const int nDirLayers = nLayers;
#else
        const int nDirLayers = static_cast<int>(oVectorLayerName.size());
#endif

        CPLErrorReset();

        return nDirLayers > 0 || !bTestOpen;
    }
}