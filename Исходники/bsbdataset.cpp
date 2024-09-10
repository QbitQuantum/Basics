void BSBDataset::ScanForGCPs( bool isNos, const char *pszFilename )

{
/* -------------------------------------------------------------------- */
/*      Collect GCPs as appropriate to source.                          */
/* -------------------------------------------------------------------- */
    nGCPCount = 0;

    if ( isNos )
    {
        ScanForGCPsNos(pszFilename);
    } else {
        ScanForGCPsBSB();
    }

/* -------------------------------------------------------------------- */
/*      Apply heuristics to re-wrap GCPs to maintain continguity        */
/*      over the international dateline.                                */
/* -------------------------------------------------------------------- */
    if( nGCPCount > 1 )
        GDALHeuristicDatelineWrapGCPs( nGCPCount, pasGCPList );

/* -------------------------------------------------------------------- */
/*      Collect coordinate system related parameters from header.       */
/* -------------------------------------------------------------------- */
    int i;
    const char *pszKNP=NULL, *pszKNQ=NULL;

    for( i = 0; psInfo->papszHeader[i] != NULL; i++ )
    {
        if( EQUALN(psInfo->papszHeader[i],"KNP/",4) )
        {
            pszKNP = psInfo->papszHeader[i];
            SetMetadataItem( "BSB_KNP", pszKNP + 4 );
        }
        if( EQUALN(psInfo->papszHeader[i],"KNQ/",4) )
        {
            pszKNQ = psInfo->papszHeader[i]; 
            SetMetadataItem( "BSB_KNQ", pszKNQ + 4 );
        }
    }

    
/* -------------------------------------------------------------------- */
/*      Can we derive a reasonable coordinate system definition for     */
/*      this file?  For now we keep it simple, just handling            */
/*      mercator. In the future we should consider others.              */
/* -------------------------------------------------------------------- */
    CPLString osUnderlyingSRS;
    if( pszKNP != NULL )
    {
        const char *pszPR = strstr(pszKNP,"PR=");
        const char *pszGD = strstr(pszKNP,"GD=");
        const char *pszValue, *pszEnd = NULL;
        const char *pszGEOGCS = "GEOGCS[\"WGS 84\",DATUM[\"WGS_1984\",SPHEROID[\"WGS 84\",6378137,298.257223563,AUTHORITY[\"EPSG\",\"7030\"]],TOWGS84[0,0,0,0,0,0,0],AUTHORITY[\"EPSG\",\"6326\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.0174532925199433,AUTHORITY[\"EPSG\",\"9108\"]],AUTHORITY[\"EPSG\",\"4326\"]]";
        CPLString osPP;
        
        // Capture the PP string.
        pszValue = strstr(pszKNP,"PP=");
        if( pszValue )
            pszEnd = strstr(pszValue,",");
        if( pszValue && pszEnd )
            osPP.assign(pszValue+3,pszEnd-pszValue-3);
        
        // Look at the datum
        if( pszGD == NULL )
        {
            /* no match. We'll default to EPSG:4326 */
        }
        else if( EQUALN(pszGD,"GD=European 1950", 16) )
        {
            pszGEOGCS = "GEOGCS[\"ED50\",DATUM[\"European_Datum_1950\",SPHEROID[\"International 1924\",6378388,297,AUTHORITY[\"EPSG\",\"7022\"]],TOWGS84[-87,-98,-121,0,0,0,0],AUTHORITY[\"EPSG\",\"6230\"]],PRIMEM[\"Greenwich\",0,AUTHORITY[\"EPSG\",\"8901\"]],UNIT[\"degree\",0.01745329251994328,AUTHORITY[\"EPSG\",\"9122\"]],AUTHORITY[\"EPSG\",\"4230\"]]";
        }

        // Look at the projection
        if( pszPR == NULL )
        {
            /* no match */
        }
        else if( EQUALN(pszPR,"PR=MERCATOR", 11) )
        {
            // We somewhat arbitrarily select our first GCPX as our 
            // central meridian.  This is mostly helpful to ensure 
            // that regions crossing the dateline will be contiguous 
            // in mercator.
            osUnderlyingSRS.Printf( "PROJCS[\"Global Mercator\",%s,PROJECTION[\"Mercator_2SP\"],PARAMETER[\"standard_parallel_1\",0],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",%d],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0],UNIT[\"Meter\",1]]",
                pszGEOGCS, (int) pasGCPList[0].dfGCPX );
        }

        else if( EQUALN(pszPR,"PR=TRANSVERSE MERCATOR", 22)
                 && osPP.size() > 0 )
        {
            
            osUnderlyingSRS.Printf( 
                "PROJCS[\"unnamed\",%s,PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",%s],PARAMETER[\"scale_factor\",1],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0]]",
                pszGEOGCS, osPP.c_str() );
        }

        else if( EQUALN(pszPR,"PR=UNIVERSAL TRANSVERSE MERCATOR", 32)
                 && osPP.size() > 0 )
        {
            // This is not *really* UTM unless the central meridian 
            // matches a zone which it does not in some (most?) maps. 
            osUnderlyingSRS.Printf( 
                "PROJCS[\"unnamed\",%s,PROJECTION[\"Transverse_Mercator\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",%s],PARAMETER[\"scale_factor\",0.9996],PARAMETER[\"false_easting\",500000],PARAMETER[\"false_northing\",0]]", 
                pszGEOGCS, osPP.c_str() );
        }

        else if( EQUALN(pszPR,"PR=POLYCONIC", 12) && osPP.size() > 0 )
        {
            osUnderlyingSRS.Printf( 
                "PROJCS[\"unnamed\",%s,PROJECTION[\"Polyconic\"],PARAMETER[\"latitude_of_origin\",0],PARAMETER[\"central_meridian\",%s],PARAMETER[\"false_easting\",0],PARAMETER[\"false_northing\",0]]", 
                pszGEOGCS, osPP.c_str() );
        }
        
        else if( EQUALN(pszPR,"PR=LAMBERT CONFORMAL CONIC", 26) 
                 && osPP.size() > 0 && pszKNQ != NULL )
        {
            CPLString osP2, osP3;
        
            // Capture the KNQ/P2 string.
            pszValue = strstr(pszKNQ,"P2=");
            if( pszValue )
                pszEnd = strstr(pszValue,",");
            if( pszValue && pszEnd )
                osP2.assign(pszValue+3,pszEnd-pszValue-3);
            
            // Capture the KNQ/P3 string.
            pszValue = strstr(pszKNQ,"P3=");
            if( pszValue )
                pszEnd = strstr(pszValue,",");
            if( pszValue )
            {
                if( pszEnd )
                    osP3.assign(pszValue+3,pszEnd-pszValue-3);
                else
                    osP3.assign(pszValue+3);
            }

            if( osP2.size() > 0 && osP3.size() > 0 )
                osUnderlyingSRS.Printf( 
                    "PROJCS[\"unnamed\",%s,PROJECTION[\"Lambert_Conformal_Conic_2SP\"],PARAMETER[\"standard_parallel_1\",%s],PARAMETER[\"standard_parallel_2\",%s],PARAMETER[\"latitude_of_origin\",0.0],PARAMETER[\"central_meridian\",%s],PARAMETER[\"false_easting\",0.0],PARAMETER[\"false_northing\",0.0]]",
                    pszGEOGCS, osP2.c_str(), osP3.c_str(), osPP.c_str() );

        }
    }

/* -------------------------------------------------------------------- */
/*      If we got an alternate underlying coordinate system, try        */
/*      converting the GCPs to that coordinate system.                  */
/* -------------------------------------------------------------------- */
    if( osUnderlyingSRS.length() > 0 )
    {
        OGRSpatialReference oGeog_SRS, oProjected_SRS;
        OGRCoordinateTransformation *poCT;
        
        oProjected_SRS.SetFromUserInput( osUnderlyingSRS );
        oGeog_SRS.CopyGeogCSFrom( &oProjected_SRS );
        
        poCT = OGRCreateCoordinateTransformation( &oGeog_SRS, 
                                                  &oProjected_SRS );
        if( poCT != NULL )
        {
            for( i = 0; i < nGCPCount; i++ )
            {
                poCT->Transform( 1, 
                                 &(pasGCPList[i].dfGCPX), 
                                 &(pasGCPList[i].dfGCPY), 
                                 &(pasGCPList[i].dfGCPZ) );
            }

            osGCPProjection = osUnderlyingSRS;

            delete poCT;
        }
        else
            CPLErrorReset();
    }

/* -------------------------------------------------------------------- */
/*      Attempt to prepare a geotransform from the GCPs.                */
/* -------------------------------------------------------------------- */
    if( GDALGCPsToGeoTransform( nGCPCount, pasGCPList, adfGeoTransform, 
                                FALSE ) )
    {
        bGeoTransformSet = TRUE;
    }
}