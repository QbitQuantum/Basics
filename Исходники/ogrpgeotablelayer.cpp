CPLErr OGRPGeoTableLayer::Initialize( const char *pszTableName, 
                                      const char *pszGeomCol,
                                      int nShapeType, 
                                      double dfExtentLeft,
                                      double dfExtentRight,
                                      double dfExtentBottom,
                                      double dfExtentTop,
                                      int nSRID,
                                      int bHasZ )


{
    CPLODBCSession *poSession = poDS->GetSession();
    
    SetDescription( pszTableName );

    CPLFree( pszGeomColumn );
    if( pszGeomCol == NULL )
        pszGeomColumn = NULL;
    else
        pszGeomColumn = CPLStrdup( pszGeomCol );

    CPLFree( pszFIDColumn );
    pszFIDColumn = NULL;

    sExtent.MinX = dfExtentLeft;
    sExtent.MaxX = dfExtentRight;
    sExtent.MinY = dfExtentBottom;
    sExtent.MaxY = dfExtentTop;

    LookupSRID( nSRID );

/* -------------------------------------------------------------------- */
/*      Setup geometry type.                                            */
/* -------------------------------------------------------------------- */
    OGRwkbGeometryType  eOGRType;

    switch( nShapeType )
    {
        case ESRI_LAYERGEOMTYPE_NULL:
            eOGRType = wkbNone;
            break;

        case ESRI_LAYERGEOMTYPE_POINT:
            eOGRType = wkbPoint;
            break;

        case ESRI_LAYERGEOMTYPE_MULTIPOINT:
            eOGRType = wkbMultiPoint;
            break;

        case ESRI_LAYERGEOMTYPE_POLYLINE:
            eOGRType = wkbLineString;
            break;

        case ESRI_LAYERGEOMTYPE_POLYGON:
        case ESRI_LAYERGEOMTYPE_MULTIPATCH:
            eOGRType = wkbPolygon;
            break;

        default:
            CPLDebug("PGeo", "Unexpected value for shape type : %d", nShapeType);
            eOGRType = wkbUnknown;
            break;
    }

    if( eOGRType != wkbUnknown && eOGRType != wkbNone && bHasZ )
        eOGRType = wkbSetZ(eOGRType);

/* -------------------------------------------------------------------- */
/*      Do we have a simple primary key?                                */
/* -------------------------------------------------------------------- */
    CPLODBCStatement oGetKey( poSession );
    
    if( oGetKey.GetPrimaryKeys( pszTableName ) && oGetKey.Fetch() )
    {
        pszFIDColumn = CPLStrdup(oGetKey.GetColData( 3 ));
        
        if( oGetKey.Fetch() ) // more than one field in key! 
        {
            CPLFree( pszFIDColumn );
            pszFIDColumn = NULL;
            CPLDebug( "PGeo", "%s: Compound primary key, ignoring.",
                      pszTableName );
        }
        else
            CPLDebug( "PGeo", 
                      "%s: Got primary key %s.",
                      pszTableName, pszFIDColumn );
    }
    else
        CPLDebug( "PGeo", "%s: no primary key", pszTableName );

/* -------------------------------------------------------------------- */
/*      Get the column definitions for this table.                      */
/* -------------------------------------------------------------------- */
    CPLODBCStatement oGetCol( poSession );
    CPLErr eErr;

    if( !oGetCol.GetColumns( pszTableName ) )
    {
        CPLError( CE_Failure, CPLE_AppDefined, 
                  "GetColumns() failed on %s.\n%s",
                  pszTableName, poSession->GetLastError() );
        return CE_Failure;
    }

    eErr = BuildFeatureDefn( pszTableName, &oGetCol );
    if( eErr != CE_None )
        return eErr;

    if( poFeatureDefn->GetFieldCount() == 0 )
    {
        CPLError( CE_Failure, CPLE_AppDefined, 
                  "No column definitions found for table '%s', layer not usable.", 
                  pszTableName );
        return CE_Failure;
    }

/* -------------------------------------------------------------------- */
/*      Set geometry type.                                              */
/*                                                                      */
/*      NOTE: per reports from Craig Miller, it seems we cannot really  */
/*      trust the ShapeType value.  At the very least "line" tables     */
/*      sometimes have multilinestrings.  So for now we just always     */
/*      return wkbUnknown.                                              */
/*                                                                      */
/*      TODO - mloskot: Similar issue has been reported in Ticket #1484 */
/* -------------------------------------------------------------------- */
#ifdef notdef
    poFeatureDefn->SetGeomType( eOGRType );
#endif

    return CE_None;
}