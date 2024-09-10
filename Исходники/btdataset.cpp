GDALDataset *BTDataset::Open( GDALOpenInfo * poOpenInfo )

{
/* -------------------------------------------------------------------- */
/*      Verify that this is some form of binterr file.                  */
/* -------------------------------------------------------------------- */
    if( poOpenInfo->nHeaderBytes < 256)
        return NULL;

    if( strncmp( (const char *) poOpenInfo->pabyHeader, "binterr", 7 ) != 0 )
        return NULL;

/* -------------------------------------------------------------------- */
/*      Create the dataset.                                             */
/* -------------------------------------------------------------------- */
    BTDataset  *poDS;

    poDS = new BTDataset();
 
    memcpy( poDS->abyHeader, poOpenInfo->pabyHeader, 256 );

/* -------------------------------------------------------------------- */
/*      Get the version.                                                */
/* -------------------------------------------------------------------- */
    char szVersion[4];

    strncpy( szVersion, (char *) (poDS->abyHeader + 7), 3 );
    szVersion[3] = '\0';
    poDS->nVersionCode = (int) (atof(szVersion) * 10);

/* -------------------------------------------------------------------- */
/*      Extract core header information, being careful about the        */
/*      version.                                                        */
/* -------------------------------------------------------------------- */
    GInt32 nIntTemp;
    GInt16 nDataSize;
    GDALDataType eType;

    memcpy( &nIntTemp, poDS->abyHeader + 10, 4 );
    poDS->nRasterXSize = CPL_LSBWORD32( nIntTemp );
    
    memcpy( &nIntTemp, poDS->abyHeader + 14, 4 );
    poDS->nRasterYSize = CPL_LSBWORD32( nIntTemp );

    if (!GDALCheckDatasetDimensions(poDS->nRasterXSize, poDS->nRasterYSize))
    {
        delete poDS;
        return NULL;
    }

    memcpy( &nDataSize, poDS->abyHeader+18, 2 );
    nDataSize = CPL_LSBWORD16( nDataSize );

    if( poDS->abyHeader[20] != 0 && nDataSize == 4 )
        eType = GDT_Float32;
    else if( poDS->abyHeader[20] == 0 && nDataSize == 4 )
        eType = GDT_Int32;
    else if( poDS->abyHeader[20] == 0 && nDataSize == 2 )
        eType = GDT_Int16;
    else
    {
        CPLError( CE_Failure, CPLE_AppDefined, 
                  ".bt file data type unknown, got datasize=%d.", 
                  nDataSize );
        delete poDS;
        return NULL;
    }

    /*
        rcg, apr 7/06: read offset 62 for vert. units.
        If zero, assume 1.0 as per spec.

    */
    memcpy( &poDS->m_fVscale, poDS->abyHeader + 62, 4 );
    CPL_LSBPTR32(&poDS->m_fVscale);
    if(poDS->m_fVscale == 0.0f)
        poDS->m_fVscale = 1.0f; 

/* -------------------------------------------------------------------- */
/*      Try to read a .prj file if it is indicated.                     */
/* -------------------------------------------------------------------- */
    OGRSpatialReference oSRS;						

    if( poDS->nVersionCode >= 12 && poDS->abyHeader[60] != 0 )
    {
        const char  *pszPrjFile = CPLResetExtension( poOpenInfo->pszFilename, 
                                                     "prj" );
        VSILFILE *fp;

        fp = VSIFOpenL( pszPrjFile, "rt" );
        if( fp != NULL )
        {
            char *pszBuffer, *pszBufPtr;
            int  nBufMax = 10000;
            int nBytes;

            pszBuffer = (char *) CPLMalloc(nBufMax);
            nBytes = VSIFReadL( pszBuffer, 1, nBufMax-1, fp );
            VSIFCloseL( fp );

            pszBuffer[nBytes] = '\0';

            pszBufPtr = pszBuffer;
            if( oSRS.importFromWkt( &pszBufPtr ) != OGRERR_NONE )
            {
                CPLError( CE_Warning, CPLE_AppDefined, 
                          "Unable to parse .prj file, coordinate system missing." );
            }
            CPLFree( pszBuffer );
        }
    }

/* -------------------------------------------------------------------- */
/*      If we didn't find a .prj file, try to use internal info.        */
/* -------------------------------------------------------------------- */
    if( oSRS.GetRoot() == NULL )
    {
        GInt16 nUTMZone, nDatum, nHUnits;
        
        memcpy( &nUTMZone, poDS->abyHeader + 24, 2 );
        nUTMZone = CPL_LSBWORD16( nUTMZone );
        
        memcpy( &nDatum, poDS->abyHeader + 26, 2 );
        nDatum = CPL_LSBWORD16( nDatum );
        
        memcpy( &nHUnits, poDS->abyHeader + 22, 2 );
        nHUnits = CPL_LSBWORD16( nHUnits );

        if( nUTMZone != 0 )
            oSRS.SetUTM( ABS(nUTMZone), nUTMZone > 0 );
        else if( nHUnits != 0 )
            oSRS.SetLocalCS( "Unknown" );
        
        if( nHUnits == 1 )
            oSRS.SetLinearUnits( SRS_UL_METER, 1.0 );
        else if( nHUnits == 2 )
            oSRS.SetLinearUnits( SRS_UL_FOOT, atof(SRS_UL_FOOT_CONV) );
        else if( nHUnits == 3 )
            oSRS.SetLinearUnits( SRS_UL_US_FOOT, atof(SRS_UL_US_FOOT_CONV) );

        // Translate some of the more obvious old USGS datum codes 
        if( nDatum == 0 )
            nDatum = 6201;
        else if( nDatum == 1 )
            nDatum = 6209;
        else if( nDatum == 2 )
            nDatum = 6210;
        else if( nDatum == 3 )
            nDatum = 6202;
        else if( nDatum == 4 )
            nDatum = 6203;
        else if( nDatum == 4 )
            nDatum = 6203;
        else if( nDatum == 6 )
            nDatum = 6222;
        else if( nDatum == 7 )
            nDatum = 6230;
        else if( nDatum == 13 )
            nDatum = 6267;
        else if( nDatum == 14 )
            nDatum = 6269;
        else if( nDatum == 17 )
            nDatum = 6277;
        else if( nDatum == 19 )
            nDatum = 6284;
        else if( nDatum == 21 )
            nDatum = 6301;
        else if( nDatum == 22 )
            nDatum = 6322;
        else if( nDatum == 23 )
            nDatum = 6326;

        if( !oSRS.IsLocal() )
        {
            if( nDatum >= 6000 )
            {
                char szName[32];
                sprintf( szName, "EPSG:%d", nDatum-2000 );
                oSRS.SetWellKnownGeogCS( szName );
            }
            else
                oSRS.SetWellKnownGeogCS( "WGS84" );
        }                
    }

/* -------------------------------------------------------------------- */
/*      Convert coordinate system back to WKT.                          */
/* -------------------------------------------------------------------- */
    if( oSRS.GetRoot() != NULL )
        oSRS.exportToWkt( &poDS->pszProjection );

/* -------------------------------------------------------------------- */
/*      Get georeferencing bounds.                                      */
/* -------------------------------------------------------------------- */
    if( poDS->nVersionCode >= 11 )
    {
        double dfLeft, dfRight, dfTop, dfBottom;

        memcpy( &dfLeft, poDS->abyHeader + 28, 8 );
        CPL_LSBPTR64( &dfLeft );
        
        memcpy( &dfRight, poDS->abyHeader + 36, 8 );
        CPL_LSBPTR64( &dfRight );
        
        memcpy( &dfBottom, poDS->abyHeader + 44, 8 );
        CPL_LSBPTR64( &dfBottom );
        
        memcpy( &dfTop, poDS->abyHeader + 52, 8 );
        CPL_LSBPTR64( &dfTop );

        poDS->adfGeoTransform[0] = dfLeft;
        poDS->adfGeoTransform[1] = (dfRight - dfLeft) / poDS->nRasterXSize;
        poDS->adfGeoTransform[2] = 0.0;
        poDS->adfGeoTransform[3] = dfTop;
        poDS->adfGeoTransform[4] = 0.0;
        poDS->adfGeoTransform[5] = (dfBottom - dfTop) / poDS->nRasterYSize;
        
        poDS->bGeoTransformValid = TRUE;
    }
    
/* -------------------------------------------------------------------- */
/*      Re-open the file with the desired access.                       */
/* -------------------------------------------------------------------- */

    if( poOpenInfo->eAccess == GA_Update )
        poDS->fpImage = VSIFOpenL( poOpenInfo->pszFilename, "rb+" );
    else
        poDS->fpImage = VSIFOpenL( poOpenInfo->pszFilename, "rb" );

    if( poDS->fpImage == NULL )
    {
        CPLError( CE_Failure, CPLE_OpenFailed,
                  "Failed to re-open %s within BT driver.\n",
                  poOpenInfo->pszFilename );
        return NULL;
    }
    poDS->eAccess = poOpenInfo->eAccess;

/* -------------------------------------------------------------------- */
/*      Create band information objects                                 */
/* -------------------------------------------------------------------- */
    poDS->SetBand( 1, new BTRasterBand( poDS, poDS->fpImage, eType ) );

#ifdef notdef
    poDS->bGeoTransformValid = 
        GDALReadWorldFile( poOpenInfo->pszFilename, ".wld", 
                           poDS->adfGeoTransform );
#endif

/* -------------------------------------------------------------------- */
/*      Initialize any PAM information.                                 */
/* -------------------------------------------------------------------- */
    poDS->SetDescription( poOpenInfo->pszFilename );
    poDS->TryLoadXML();

/* -------------------------------------------------------------------- */
/*      Check for overviews.                                            */
/* -------------------------------------------------------------------- */
    poDS->oOvManager.Initialize( poDS, poOpenInfo->pszFilename );

    return( poDS );
}