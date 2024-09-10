void VertexList::Reorder( TriangleBatch& pUnorderedStrip )
{
#if GD_PLATFORM == GD_PLATFORM_WIN32
    Vector3f*   newPositions    = NULL;
    Vector3f*   newNormals      = NULL;
    Color4f*    newColors       = NULL;
    Vector2f*   newTexCoords    = NULL;
    Vector2f*   newTexCoords_2  = NULL;

    PrimitiveGroup  unorderedPrimitiveGroup;
    PrimitiveGroup* orderedPrimitiveGroup;

    unorderedPrimitiveGroup.type        = pUnorderedStrip.GetBatchType() == TriangleBatch::TriangleStrip? PT_STRIP :
    pUnorderedStrip.GetBatchType() == TriangleBatch::TriangleList ? PT_LIST : PT_FAN;

    unorderedPrimitiveGroup.numIndices  = pUnorderedStrip.GetIndicesCount();
    unorderedPrimitiveGroup.indices     = GD_NEW_ARRAY(UInt16, unorderedPrimitiveGroup.numIndices, this, "Engine::Graphic::VertexList");
    memcpy( unorderedPrimitiveGroup.indices, pUnorderedStrip.GetIndices(), sizeof(UInt16)*unorderedPrimitiveGroup.numIndices );

    // Remap!
    RemapIndices( &unorderedPrimitiveGroup, 1, mVertexCount, &orderedPrimitiveGroup );

    UInt16*     oldIndices = unorderedPrimitiveGroup.indices;
    UInt16*     newIndices = orderedPrimitiveGroup->indices;

    if( mPositions )
        newPositions = GD_NEW_ARRAY(Vector3f, mVertexCount, this, "Engine::Graphic::VertexList::Positions");

    if( mNormals )
        newNormals = GD_NEW_ARRAY(Vector3f, mVertexCount, this, "Engine::Graphic::VertexList::Normals");

    if( mColors )
        newColors = GD_NEW_ARRAY(Color4f, mVertexCount, this, "Engine::Graphic::VertexList::Colors");

    if( mTexCoords )
        newTexCoords = GD_NEW_ARRAY(Vector2f, mVertexCount, this, "Engine::Graphic::VertexList::TexCoords");

    if( mTexCoords_2 )
        newTexCoords_2 = GD_NEW_ARRAY(Vector2f, mVertexCount, this, "Engine::Graphic::VertexList::TexCoords");

    for( UInt32 iIndex = 0; iIndex < orderedPrimitiveGroup->numIndices; iIndex++ )
    {
        // Grab old index.
        UInt16 oldIndex = oldIndices[iIndex];

        // Grab new index.
        UInt16 newIndex = newIndices[iIndex];

        if( mPositions )
            newPositions[newIndex] = mPositions[oldIndex];

        if( mNormals )
            newNormals[newIndex] = mNormals[oldIndex];

        if( mColors )
            newColors[newIndex] = mColors[oldIndex];

        if( mTexCoords )
            newTexCoords[newIndex] = mTexCoords[oldIndex];

        if( mTexCoords_2 )
            newTexCoords_2[newIndex] = mTexCoords_2[oldIndex];
    }

    if( mPositions )
    {
        GD_DELETE_ARRAY(mPositions);
        mPositions = newPositions;
    }

    if( mNormals )
    {
        GD_DELETE_ARRAY(mNormals);
        mNormals = newNormals;
    }

    if( mColors )
    {
        GD_DELETE_ARRAY(mColors);
        mColors = newColors;
    }

    if( mTexCoords )
    {
        GD_DELETE_ARRAY(mTexCoords);
        mTexCoords = newTexCoords;
    }

    if( mTexCoords_2 )
    {
        GD_DELETE_ARRAY(mTexCoords_2);
        mTexCoords_2 = newTexCoords_2;
    }

    // Return the ordered triangle strip.
    memcpy( pUnorderedStrip.GetIndices(), orderedPrimitiveGroup->indices, orderedPrimitiveGroup->numIndices*sizeof(UInt16) );

    //    GD_DELETE(orderedPrimitiveGroup);
#else
	debugBreak();
#endif
}