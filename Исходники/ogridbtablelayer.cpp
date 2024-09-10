OGRSpatialReference *OGRIDBTableLayer::GetSpatialRef()

{
    if( nSRSId == -2 )
    {
        nSRSId = -1;

        if ( ! pszGeomColumn )
            return NULL;

        CPLString osCmd;
        osCmd.Printf( " SELECT FIRST 1 srid, trim(srtext)"
                      " FROM spatial_ref_sys, %s"
                      " WHERE srid = ST_Srid(%s) ",
                      poFeatureDefn->GetName(), pszGeomColumn );

        ITCursor oSridCur( *poDS->GetConnection() );

        if( oSridCur.Prepare( osCmd.c_str() )&&
            oSridCur.Open( ITCursor::ReadOnly ) )
        {
            ITRow * row = static_cast<ITRow *>( oSridCur.NextRow() );
            if ( row && ! row->IsNull() )
            {
                nSRSId = atoi(row->Column(0)->Printable());
                const char * wkt = row->Column(1)->Printable();

                if ( poSRS )
                {
                    // Hmm ... it should be null
                    delete poSRS;
                }
                poSRS = new OGRSpatialReference();
                if ( poSRS->importFromWkt( (char **)&wkt ) != OGRERR_NONE )
                {
                    CPLError( CE_Warning, CPLE_AppDefined,
                              "Error parse srs wkt: %s", wkt );
                    delete poSRS;
                    poSRS = NULL;
                }
            }
        }
    }

    return OGRIDBLayer::GetSpatialRef();
}