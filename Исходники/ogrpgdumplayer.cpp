OGRErr OGRPGDumpLayer::CreateField( OGRFieldDefn *poFieldIn,
                                    int bApproxOK )
{
    CPLString           osCommand;
    CPLString           osFieldType;
    OGRFieldDefn        oField( poFieldIn );

    /* -------------------------------------------------------------------- */
    /*      Do we want to "launder" the column names into Postgres          */
    /*      friendly format?                                                */
    /* -------------------------------------------------------------------- */
    if( bLaunderColumnNames )
    {
        char    *pszSafeName = poDS->LaunderName( oField.GetNameRef() );

        oField.SetName( pszSafeName );
        CPLFree( pszSafeName );

        if( EQUAL(oField.GetNameRef(),"oid") )
        {
            CPLError( CE_Warning, CPLE_AppDefined,
                      "Renaming field 'oid' to 'oid_' to avoid conflict with internal oid field." );
            oField.SetName( "oid_" );
        }
    }

    const char* pszOverrideType = CSLFetchNameValue(papszOverrideColumnTypes, oField.GetNameRef());
    if( pszOverrideType != NULL )
        osFieldType = pszOverrideType;
    else
    {
        osFieldType = OGRPGTableLayerGetType(oField, bPreservePrecision, bApproxOK);
        if (osFieldType.size() == 0)
            return OGRERR_FAILURE;
    }

    /* -------------------------------------------------------------------- */
    /*      Create the new field.                                           */
    /* -------------------------------------------------------------------- */
    osCommand.Printf( "ALTER TABLE %s ADD COLUMN %s %s",
                      pszSqlTableName, OGRPGDumpEscapeColumnName(oField.GetNameRef()).c_str(),
                      osFieldType.c_str() );
    if (bCreateTable)
        poDS->Log(osCommand);

    poFeatureDefn->AddFieldDefn( &oField );

    return OGRERR_NONE;
}