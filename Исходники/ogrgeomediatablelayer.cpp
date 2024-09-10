CPLErr OGRGeomediaTableLayer::Initialize( const char *pszTableName,
                                          const char *pszGeomCol,
                                          OGRSpatialReference* poSRSIn )


{
    CPLODBCSession *poSession = poDS->GetSession();

    CPLFree( pszGeomColumn );
    if( pszGeomCol == NULL )
        pszGeomColumn = NULL;
    else
        pszGeomColumn = CPLStrdup( pszGeomCol );

    CPLFree( pszFIDColumn );
    pszFIDColumn = NULL;

    this->poSRS = poSRSIn;

/* -------------------------------------------------------------------- */
/*      Do we have a simple primary key?                                */
/* -------------------------------------------------------------------- */
    {
    CPLODBCStatement oGetKey( poSession );

    if( oGetKey.GetPrimaryKeys( pszTableName ) && oGetKey.Fetch() )
    {
        pszFIDColumn = CPLStrdup(oGetKey.GetColData( 3 ));

        if( oGetKey.Fetch() ) // more than one field in key!
        {
            CPLFree( pszFIDColumn );
            pszFIDColumn = NULL;
            CPLDebug( "Geomedia", "%s: Compound primary key, ignoring.",
                      pszTableName );
        }
        else
            CPLDebug( "Geomedia",
                      "%s: Got primary key %s.",
                      pszTableName, pszFIDColumn );
    }
    else
        CPLDebug( "Geomedia", "%s: no primary key", pszTableName );
    }
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

    return CE_None;
}