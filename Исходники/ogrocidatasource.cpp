OGRErr OGROCIDataSource::DeleteLayer( int iLayer )

{
/* -------------------------------------------------------------------- */
/*      Blow away our OGR structures related to the layer.  This is     */
/*      pretty dangerous if anything has a reference to this layer!     */
/* -------------------------------------------------------------------- */
    CPLString osLayerName =
        papoLayers[iLayer]->GetLayerDefn()->GetName();

    CPLDebug( "OCI", "DeleteLayer(%s)", osLayerName.c_str() );

    delete papoLayers[iLayer];
    memmove( papoLayers + iLayer, papoLayers + iLayer + 1,
             sizeof(void *) * (nLayers - iLayer - 1) );
    nLayers--;

/* -------------------------------------------------------------------- */
/*      Remove from the database.                                       */
/* -------------------------------------------------------------------- */
    OGROCIStatement oCommand( poSession );
    CPLString       osCommand;
    int             nFailures = 0;

    osCommand.Printf( "DROP TABLE \"%s\"", osLayerName.c_str() );
    if( oCommand.Execute( osCommand ) != CE_None )
        nFailures++;

    osCommand.Printf(
        "DELETE FROM USER_SDO_GEOM_METADATA WHERE TABLE_NAME = UPPER('%s')",
        osLayerName.c_str() );

    if( oCommand.Execute( osCommand ) != CE_None )
        nFailures++;

    if( nFailures == 0 )
        return OGRERR_NONE;
    else
        return OGRERR_FAILURE;
}