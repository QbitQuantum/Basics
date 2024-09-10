OGRMSSQLSpatialSelectLayer::OGRMSSQLSpatialSelectLayer( OGRMSSQLSpatialDataSource *poDSIn,
                                        CPLODBCStatement * poStmtIn )

{
    poDS = poDSIn;

    iNextShapeId = 0;
    nSRSId = 0;
    poFeatureDefn = nullptr;

    poStmt = poStmtIn;
    pszBaseStatement = CPLStrdup( poStmtIn->GetCommand() );

    /* identify the geometry column */
    pszGeomColumn = nullptr;
    int iImageCol = -1;
    for ( int iColumn = 0; iColumn < poStmt->GetColCount(); iColumn++ )
    {
        if ( EQUAL(poStmt->GetColTypeName( iColumn ), "image") )
        {
            SQLCHAR     szTableName[256];
            SQLSMALLINT nTableNameLength = 0;

            SQLColAttribute(poStmt->GetStatement(), (SQLSMALLINT)(iColumn + 1), SQL_DESC_TABLE_NAME,
                                     szTableName, sizeof(szTableName),
                                     &nTableNameLength, nullptr);

            if (nTableNameLength > 0)
            {
                OGRLayer *poBaseLayer = poDS->GetLayerByName((const char*)szTableName);
                if (poBaseLayer != nullptr && EQUAL(poBaseLayer->GetGeometryColumn(), poStmt->GetColName(iColumn)))
                {
                    nGeomColumnType = MSSQLCOLTYPE_BINARY;
                    pszGeomColumn = CPLStrdup(poStmt->GetColName(iColumn));
                    /* copy spatial reference */
                    if (!poSRS && poBaseLayer->GetSpatialRef())
                        poSRS = poBaseLayer->GetSpatialRef()->Clone();
                    break;
                }
            }
            else if (iImageCol == -1)
                iImageCol = iColumn;
        }
        else if ( EQUAL(poStmt->GetColTypeName( iColumn ), "geometry") )
        {
            nGeomColumnType = MSSQLCOLTYPE_GEOMETRY;
            pszGeomColumn = CPLStrdup(poStmt->GetColName(iColumn));
            break;
        }
        else if ( EQUAL(poStmt->GetColTypeName( iColumn ), "geography") )
        {
            nGeomColumnType = MSSQLCOLTYPE_GEOGRAPHY;
            pszGeomColumn = CPLStrdup(poStmt->GetColName(iColumn));
            break;
        }
        else if ( EQUAL(poStmt->GetColTypeName( iColumn ), "udt") )
        {
            SQLCHAR     szUDTTypeName[256];
            SQLSMALLINT nUDTTypeNameLength = 0;

            SQLColAttribute(poStmt->GetStatement(), (SQLSMALLINT)(iColumn + 1), SQL_CA_SS_UDT_TYPE_NAME,
                                     szUDTTypeName, sizeof(szUDTTypeName),
                                     &nUDTTypeNameLength, nullptr);

            // For some reason on unixODBC, a UCS2 string is returned
            if ( EQUAL((char*)szUDTTypeName, "geometry") ||
                 (nUDTTypeNameLength == 16 &&
                  memcmp(szUDTTypeName, "g\0e\0o\0m\0e\0t\0r\0y", 16) == 0) )
            {
                nGeomColumnType = MSSQLCOLTYPE_GEOMETRY;
                pszGeomColumn = CPLStrdup(poStmt->GetColName(iColumn));
            }
            else if ( EQUAL((char*)szUDTTypeName, "geography") ||
                 (nUDTTypeNameLength == 18 &&
                  memcmp(szUDTTypeName, "g\0e\0o\0g\0r\0a\0p\0h\0y", 18) == 0) )
            {
                nGeomColumnType = MSSQLCOLTYPE_GEOGRAPHY;
                pszGeomColumn = CPLStrdup(poStmt->GetColName(iColumn));
            }
            break;
        }
    }

    if (pszGeomColumn == nullptr && iImageCol >= 0)
    {
        /* set the image col as geometry column as the last resort */
        nGeomColumnType = MSSQLCOLTYPE_BINARY;
        pszGeomColumn = CPLStrdup(poStmt->GetColName(iImageCol));
    }

    BuildFeatureDefn( "SELECT", poStmt );

    if ( GetSpatialRef() && poFeatureDefn->GetGeomFieldCount() == 1)
        poFeatureDefn->GetGeomFieldDefn(0)->SetSpatialRef( poSRS );
}