OGRErr OGRCARTODataSource::DeleteLayer(int iLayer)
{
    if (!bReadWrite)
    {
        CPLError(CE_Failure, CPLE_AppDefined,
                 "Operation not available in read-only mode");
        return OGRERR_FAILURE;
    }

    if( iLayer < 0 || iLayer >= nLayers )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Layer %d not in legal range of 0 to %d.",
                  iLayer, nLayers-1 );
        return OGRERR_FAILURE;
    }

/* -------------------------------------------------------------------- */
/*      Blow away our OGR structures related to the layer.  This is     */
/*      pretty dangerous if anything has a reference to this layer!     */
/* -------------------------------------------------------------------- */
    CPLString osLayerName = papoLayers[iLayer]->GetLayerDefn()->GetName();

    CPLDebug( "CARTO", "DeleteLayer(%s)", osLayerName.c_str() );

    int bDeferredCreation = papoLayers[iLayer]->GetDeferredCreation();
    papoLayers[iLayer]->CancelDeferredCreation();
    delete papoLayers[iLayer];
    memmove( papoLayers + iLayer, papoLayers + iLayer + 1,
             sizeof(void *) * (nLayers - iLayer - 1) );
    nLayers--;

    if (osLayerName.size() == 0)
        return OGRERR_NONE;

    if( !bDeferredCreation )
    {
        CPLString osSQL;
        osSQL.Printf("DROP TABLE %s",
                    OGRCARTOEscapeIdentifier(osLayerName).c_str());

        json_object* poObj = RunSQL(osSQL);
        if( poObj == NULL )
            return OGRERR_FAILURE;
        json_object_put(poObj);
    }

    return OGRERR_NONE;
}