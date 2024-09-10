OGRDB2SelectLayer::OGRDB2SelectLayer( OGRDB2DataSource *poDSIn,
                                      OGRDB2Statement * poStmtIn )

{

    SQLCHAR     szTableName[256];
    SQLCHAR     szSchemaName[256];
    SQLSMALLINT nNameLength = 0;
    OGRDB2Layer *poBaseLayer = NULL;
    poDS = poDSIn;

    iNextShapeId = 0;
    nSRSId = -1;
    poFeatureDefn = NULL;

    m_poStmt = poStmtIn;
    pszBaseStatement = CPLStrdup( poStmtIn->GetCommand() );
    CPLDebug("OGR_DB2SelectLayer::OGRDB2SelectLayer", "SQL: '%s'",
             pszBaseStatement);

    pszGeomColumn = NULL;

    /* get schema and table names for first column, column 1 */
    SQLColAttribute(m_poStmt->GetStatement(), (SQLSMALLINT)(1),
                    SQL_DESC_SCHEMA_NAME,
                    szSchemaName, sizeof(szSchemaName),
                    &nNameLength, NULL);
    /* The schema name is sometimes right padded with blanks */
    /* Replace blanks with nulls to terminate string for sprintf below */
    for (int i = 0; i < nNameLength; i++) {
        if (szSchemaName[i] == ' ') szSchemaName[i] = 0;
    };
    SQLColAttribute(m_poStmt->GetStatement(), (SQLSMALLINT)(1),
                    SQL_DESC_TABLE_NAME,
                    szTableName, sizeof(szTableName),
                    &nNameLength, NULL);
    CPLDebug("OGR_DB2SelectLayer::OGRDB2SelectLayer",
             "szSchemaName: '%s'; szTableName: '%s'",
             szSchemaName, szTableName);
    if (nNameLength > 0)
    {
        char szLayerName[512];
        sprintf(szLayerName, "%s.%s",szSchemaName, szTableName);
        poBaseLayer = (OGRDB2Layer *) poDS->GetLayerByName((const char*)
                      szLayerName);
        if (poBaseLayer != NULL)
            CPLDebug("OGR_DB2SelectLayer::OGRDB2SelectLayer",
                     "base geom col: '%s'", poBaseLayer->GetGeometryColumn());
        else CPLDebug("OGR_DB2SelectLayer::OGRDB2SelectLayer",
                          "base layer not found");
    }

    /* identify the geometry column */
    for ( int iColumn = 0; iColumn < m_poStmt->GetColCount(); iColumn++ )
    {
        if ( EQUAL(m_poStmt->GetColTypeName( iColumn ), "CLOB") ||
                EQUAL(m_poStmt->GetColTypeName( iColumn ),
                      "VARCHAR () FOR BIT DATA"))
        {
            if (poBaseLayer != NULL
                    && EQUAL(poBaseLayer->GetGeometryColumn(),
                             m_poStmt->GetColName(iColumn)))
            {
                pszGeomColumn = CPLStrdup(m_poStmt->GetColName(iColumn));
                /* copy spatial reference */
                if (!poSRS && poBaseLayer->GetSpatialRef())
                    poSRS = poBaseLayer->GetSpatialRef()->Clone();
                nSRSId = poBaseLayer->GetSRSId();
                break;
            }
        }
    }

    BuildFeatureDefn( "SELECT", m_poStmt );

    if ( GetSpatialRef() && poFeatureDefn->GetGeomFieldCount() == 1)
        poFeatureDefn->GetGeomFieldDefn(0)->SetSpatialRef( poSRS );
}