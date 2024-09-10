void TriangleBatch::Stripify( TriangleBatch& pNewBatch )
{
#if GD_PLATFORM == GD_PLATFORM_WIN32
	GD_ASSERT( mIndices );

    PrimitiveGroup* strip;
    UInt16          numGroups;

    SetCacheSize(CACHESIZE_GEFORCE1_2);
    SetStitchStrips(true);
    SetMinStripSize(0);
    SetListsOnly(false);

    // Stripify!
    GenerateStrips( mIndices, mIndicesCount, &strip, &numGroups );

    GD_ASSERT( numGroups == 1 );

    // Copy the result in our triangle batch.
    pNewBatch.Allocate( TriangleStrip, strip->numIndices );
    memcpy( pNewBatch.GetIndices(), strip->indices, strip->numIndices*sizeof(UInt16) ); 

    //GD_DELETE_ARRAY(strip);
#else
	debugBreak();
#endif
}