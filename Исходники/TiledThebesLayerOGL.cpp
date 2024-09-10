void
TiledThebesLayerOGL::ProcessUploadQueue()
{
  if (mRegionToUpload.IsEmpty())
    return;

  gfxSize resolution(1, 1);
  if (mReusableTileStore) {
    // Work out render resolution by multiplying the resolution of our ancestors.
    // Only container layers can have frame metrics, so we start off with a
    // resolution of 1, 1.
    // XXX For large layer trees, it would be faster to do this once from the
    //     root node upwards and store the value on each layer.
    for (ContainerLayer* parent = GetParent(); parent; parent = parent->GetParent()) {
      const FrameMetrics& metrics = parent->GetFrameMetrics();
      resolution.width *= metrics.mResolution.width;
      resolution.height *= metrics.mResolution.height;
    }

    mReusableTileStore->HarvestTiles(this,
                                     &mVideoMemoryTiledBuffer,
                                     mVideoMemoryTiledBuffer.GetValidRegion(),
                                     mMainMemoryTiledBuffer.GetValidRegion(),
                                     mVideoMemoryTiledBuffer.GetResolution(),
                                     resolution);
  }

  // If we coalesce uploads while the layers' valid region is changing we will
  // end up trying to upload area outside of the valid region. (bug 756555)
  mRegionToUpload.And(mRegionToUpload, mMainMemoryTiledBuffer.GetValidRegion());

  mVideoMemoryTiledBuffer.Upload(&mMainMemoryTiledBuffer,
                                 mMainMemoryTiledBuffer.GetValidRegion(),
                                 mRegionToUpload, resolution);
  mValidRegion = mVideoMemoryTiledBuffer.GetValidRegion();

  mMainMemoryTiledBuffer.ReadUnlock();
  // Release all the tiles by replacing the tile buffer with an empty
  // tiled buffer. This will prevent us from doing a double unlock when
  // calling  ~TiledThebesLayerOGL.
  // FIXME: This wont be needed when we do progressive upload and lock
  // tile by tile.
  mMainMemoryTiledBuffer = BasicTiledLayerBuffer();
  mRegionToUpload = nsIntRegion();

}