json_object* OGRCARTODBTableLayer::FetchNewFeatures(GIntBig iNext)
{
    if( osFIDColName.size() > 0 )
    {
        CPLString osSQL;
        osSQL.Printf("%s WHERE %s%s >= " CPL_FRMT_GIB " ORDER BY %s ASC LIMIT %d",
                     osSELECTWithoutWHERE.c_str(),
                     ( osWHERE.size() ) ? CPLSPrintf("%s AND ", osWHERE.c_str()) : "",
                     OGRCARTODBEscapeIdentifier(osFIDColName).c_str(),
                     iNext,
                     OGRCARTODBEscapeIdentifier(osFIDColName).c_str(),
                     GetFeaturesToFetch());
        return poDS->RunSQL(osSQL);
    }
    else
        return OGRCARTODBLayer::FetchNewFeatures(iNext);
}