void WCTSRecurseAndTransform( CPLXMLNode *psTree, 
                              OGRCoordinateTransformation *poCT )

{
    if( psTree == NULL )
        return;

/* -------------------------------------------------------------------- */
/*      If this isn't a geometry mode just recurse.                     */
/* -------------------------------------------------------------------- */
    if( !WCTSIsGeometryElement( psTree ) )
    {
        WCTSRecurseAndTransform( psTree->psChild, poCT );
        WCTSRecurseAndTransform( psTree->psNext, poCT );
        return;
    }
    
/* -------------------------------------------------------------------- */
/*      Convert this node, and it's children (but not it's sibling)     */
/*      into serialized XML form for feeding to the GML geometry        */
/*      parser.                                                         */
/* -------------------------------------------------------------------- */
    CPLXMLNode *psNext = psTree->psNext;
    OGRGeometry *poGeometry;

    psTree->psNext = NULL;
    poGeometry = (OGRGeometry *) OGR_G_CreateFromGMLTree( psTree );
    psTree->psNext = psNext;

    if( poGeometry == NULL )
    {
        /* should we raise an exception?  For now, no.*/
        WCTSRecurseAndTransform( psTree->psNext, poCT );
        return;
    }

/* -------------------------------------------------------------------- */
/*      Attempt to transform the geometry (inplace).                    */
/* -------------------------------------------------------------------- */
    if( poGeometry->transform( poCT ) != OGRERR_NONE )
        WCTSEmitServiceException( "Unable to transform some geometries." );

/* -------------------------------------------------------------------- */
/*      Convert back to XML Tree format.                                */
/* -------------------------------------------------------------------- */
    CPLXMLNode *psAltered, sTempCopy;

    if( strstr(psTree->pszValue,"Box") == NULL )
        psAltered = OGR_G_ExportToGMLTree( (OGRGeometryH) poGeometry );
    else
        psAltered = OGR_G_ExportEnvelopeToGMLTree( (OGRGeometryH) poGeometry );

    OGRGeometryFactory::destroyGeometry( poGeometry );
    
/* -------------------------------------------------------------------- */
/*      do fancy swap to copy contents of altered tree in over the      */
/*      node being changed.  We do this in such a funky way because     */
/*      we can't change the nodes that point to psTree to point to      */
/*      psAltered.                                                      */
/* -------------------------------------------------------------------- */
    CPLAssert( psAltered->psNext == NULL );

    memcpy( &sTempCopy, psTree, sizeof(CPLXMLNode));
    memcpy( psTree, psAltered, sizeof(CPLXMLNode));
    memcpy( psAltered, &sTempCopy, sizeof(CPLXMLNode));

    psTree->psNext = psAltered->psNext;
    psAltered->psNext = NULL;

    CPLDestroyXMLNode( psAltered );
    
/* -------------------------------------------------------------------- */
/*      Continue on to sibling nodes, but do no further travelling      */
/*      to this nodes children.                                         */
/* -------------------------------------------------------------------- */
    WCTSRecurseAndTransform( psTree->psNext, poCT );
}