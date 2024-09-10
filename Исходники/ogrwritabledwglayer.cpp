OGRErr OGRWritableDWGLayer::CreateFeature( OGRFeature *poFeature )

{
    OGRGeometry *poGeom = poFeature->GetGeometryRef();
    OGRErr eErr;

    if( poGeom == NULL )
        return OGRERR_FAILURE;

/* -------------------------------------------------------------------- */
/*      Keep track of file extents.                                     */
/* -------------------------------------------------------------------- */
    poDS->ExtendExtent( poGeom );

/* -------------------------------------------------------------------- */
/*      Translate geometry.                                             */
/* -------------------------------------------------------------------- */
    OdDbObjectPtr pObject;

    eErr = WriteEntity( poGeom, &pObject );
    if( eErr != OGRERR_NONE )
        return eErr;

/* -------------------------------------------------------------------- */
/*      Append attributes.                                              */
/* -------------------------------------------------------------------- */
    OdResBufPtr xIter = OdResBuf::newRb( 1001 ); 
    xIter->setString( "ACAD" );

    OdResBufPtr temp = xIter;
        
    for( int iField = 0; iField < poFeature->GetFieldCount(); iField++ )
    {
        if( !poFeature->IsFieldSet( iField ) )
            continue;

        CPLString sNameValue;
        const char *pszValue = poFeature->GetFieldAsString( iField );
        
        while( *pszValue == ' ' )
            pszValue++;

        sNameValue.Printf( "%s=%s", 
                           poFeature->GetFieldDefnRef( iField )->GetNameRef(),
                           pszValue );

        OdResBufPtr newRB = OdResBuf::newRb( 1000 );
        newRB->setString( sNameValue.c_str() );

        temp->setNext( newRB );
        temp = temp->next();
    }
    
    if( pObject != (const void *) NULL )
        pObject->setXData( xIter );

    return OGRERR_NONE;
}