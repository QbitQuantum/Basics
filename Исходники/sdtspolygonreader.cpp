void SDTSPolygonReader::AssembleRings( SDTSTransfer * poTransfer,
                                       int iPolyLayer )

{
    if( bRingsAssembled )
        return;

    bRingsAssembled = TRUE;

/* -------------------------------------------------------------------- */
/*      To write polygons we need to build them from their related      */
/*      arcs.  We don't know off hand which arc (line) layers           */
/*      contribute so we process all line layers, attaching them to     */
/*      polygons as appropriate.                                        */
/* -------------------------------------------------------------------- */
    for( int iLineLayer = 0;
         iLineLayer < poTransfer->GetLayerCount();
         iLineLayer++ )
    {
        if( poTransfer->GetLayerType(iLineLayer) != SLTLine )
            continue;

        SDTSLineReader *poLineReader = reinterpret_cast<SDTSLineReader *>(
            poTransfer->GetLayerIndexedReader( iLineLayer ) );
        if( poLineReader == nullptr )
            continue;

        poLineReader->AttachToPolygons( poTransfer, iPolyLayer );
        poLineReader->Rewind();
    }

    if( !IsIndexed() )
        return;

/* -------------------------------------------------------------------- */
/*      Scan all polygons indexed on this reader, and assemble their    */
/*      rings.                                                          */
/* -------------------------------------------------------------------- */
    Rewind();

    SDTSFeature *poFeature = nullptr;
    while( (poFeature = GetNextFeature()) != nullptr )
    {
        SDTSRawPolygon  *poPoly
            = reinterpret_cast<SDTSRawPolygon *>( poFeature );

        poPoly->AssembleRings();
    }

    Rewind();
}