void
ClientSingleTiledLayerBuffer::PaintThebes(const nsIntRegion& aNewValidRegion,
                                          const nsIntRegion& aPaintRegion,
                                          const nsIntRegion& aDirtyRegion,
                                          LayerManager::DrawPaintedLayerCallback aCallback,
                                          void* aCallbackData,
                                          bool aIsProgressive)
{
  mWasLastPaintProgressive = aIsProgressive;

  // Compare layer valid region size to current backbuffer size, discard if not matching.
  gfx::IntSize size = aNewValidRegion.GetBounds().Size();
  gfx::IntPoint origin = aNewValidRegion.GetBounds().TopLeft();
  nsIntRegion paintRegion = aPaintRegion;

  RefPtr<TextureClient> discardedFrontBuffer = nullptr;
  RefPtr<TextureClient> discardedFrontBufferOnWhite = nullptr;
  nsIntRegion discardedValidRegion;

  if (mSize != size ||
      mTilingOrigin != origin) {
    discardedFrontBuffer = mTile.mFrontBuffer;
    discardedFrontBufferOnWhite = mTile.mFrontBufferOnWhite;
    discardedValidRegion = mValidRegion;

    TILING_LOG("TILING %p: Single-tile valid region changed. Discarding buffers.\n", &mPaintedLayer)
;
    ResetPaintedAndValidState();
    mSize = size;
    mTilingOrigin = origin;
    paintRegion = aNewValidRegion;
  }

  SurfaceMode mode;
  gfxContentType content = GetContentType(&mode);
  mFormat = gfxPlatform::GetPlatform()->OptimalFormatForContent(content);

  if (mTile.IsPlaceholderTile()) {
    mTile.SetTextureAllocator(this);
  }

  // The dirty region relative to the top-left of the tile.
  nsIntRegion tileDirtyRegion = paintRegion.MovedBy(-mTilingOrigin);

  nsIntRegion extraPainted;
  RefPtr<TextureClient> backBufferOnWhite;
  RefPtr<TextureClient> backBuffer =
    mTile.GetBackBuffer(mCompositableClient,
                        tileDirtyRegion,
                        content, mode,
                        extraPainted,
                        &backBufferOnWhite);

  mTile.mUpdateRect = tileDirtyRegion.GetBounds().Union(extraPainted.GetBounds());

  extraPainted.MoveBy(mTilingOrigin);
  extraPainted.And(extraPainted, aNewValidRegion);
  mPaintedRegion.OrWith(paintRegion);
  mPaintedRegion.OrWith(extraPainted);

  if (!backBuffer) {
    return;
  }

  RefPtr<gfx::DrawTarget> dt = backBuffer->BorrowDrawTarget();
  RefPtr<gfx::DrawTarget> dtOnWhite;
  if (backBufferOnWhite) {
    dtOnWhite = backBufferOnWhite->BorrowDrawTarget();
  }

  if (mode != SurfaceMode::SURFACE_OPAQUE) {
    for (auto iter = tileDirtyRegion.RectIter(); !iter.Done(); iter.Next()) {
      const gfx::IntRect& rect = iter.Get();
      if (dtOnWhite) {
        dt->FillRect(gfx::Rect(rect.x, rect.y, rect.width, rect.height),
                     gfx::ColorPattern(gfx::Color(0.0, 0.0, 0.0, 1.0)));
        dtOnWhite->FillRect(gfx::Rect(rect.x, rect.y, rect.width, rect.height),
                            gfx::ColorPattern(gfx::Color(1.0, 1.0, 1.0, 1.0)));
      } else {
        dt->ClearRect(gfx::Rect(rect.x, rect.y, rect.width, rect.height));
      }
    }
  }

  // If the old frontbuffer was discarded then attempt to copy what we
  // can from it to the new backbuffer.
  if (discardedFrontBuffer) {
    nsIntRegion copyableRegion;
    copyableRegion.And(aNewValidRegion, discardedValidRegion);
    copyableRegion.SubOut(aDirtyRegion);

    if (!copyableRegion.IsEmpty()) {
      TextureClientAutoLock frontLock(discardedFrontBuffer,
                                      OpenMode::OPEN_READ);
      if (frontLock.Succeeded()) {
        for (auto iter = copyableRegion.RectIter(); !iter.Done(); iter.Next()) {
          const gfx::IntRect rect = iter.Get() - discardedValidRegion.GetBounds().TopLeft();
          const gfx::IntPoint dest = iter.Get().TopLeft() - mTilingOrigin;
          discardedFrontBuffer->CopyToTextureClient(backBuffer, &rect, &dest);
        }
      }

      if (discardedFrontBufferOnWhite && backBufferOnWhite) {
        TextureClientAutoLock frontOnWhiteLock(discardedFrontBufferOnWhite,
                                               OpenMode::OPEN_READ);
        if (frontOnWhiteLock.Succeeded()) {
          for (auto iter = copyableRegion.RectIter(); !iter.Done(); iter.Next()) {
            const gfx::IntRect rect = iter.Get() - discardedValidRegion.GetBounds().TopLeft();
            const gfx::IntPoint dest = iter.Get().TopLeft() - mTilingOrigin;

            discardedFrontBufferOnWhite->CopyToTextureClient(backBufferOnWhite,
                                                             &rect, &dest);
          }
        }
      }

      TILING_LOG("TILING %p: Region copied from discarded frontbuffer %s\n", &mPaintedLayer, Stringify(copyableRegion).c_str());

      // We don't need to repaint valid content that was just copied.
      paintRegion.SubOut(copyableRegion);
    }
  }

  if (dtOnWhite) {
    dt = gfx::Factory::CreateDualDrawTarget(dt, dtOnWhite);
    dtOnWhite = nullptr;
  }

  {
    RefPtr<gfxContext> ctx = gfxContext::CreateOrNull(dt);
    if (!ctx) {
      gfxDevCrash(gfx::LogReason::InvalidContext) << "SingleTiledContextClient context problem " << gfx::hexa(dt);
      return;
    }
    ctx->SetMatrix(ctx->CurrentMatrix().Translate(-mTilingOrigin.x, -mTilingOrigin.y));

    aCallback(&mPaintedLayer, ctx, paintRegion, paintRegion, DrawRegionClip::DRAW, nsIntRegion(), aCallbackData);
  }

  // Mark the area we just drew into the back buffer as invalid in the front buffer as they're
  // now out of sync.
  mTile.mInvalidFront.OrWith(tileDirtyRegion);

  // The new buffer is now validated, remove the dirty region from it.
  mTile.mInvalidBack.SubOut(tileDirtyRegion);

  dt = nullptr;

  mTile.Flip();
  UnlockTile(mTile);

  if (backBuffer->HasIntermediateBuffer()) {
    // If our new buffer has an internal buffer, we don't want to keep another
    // TextureClient around unnecessarily, so discard the back-buffer.
    mTile.DiscardBackBuffer();
  }

  mValidRegion = aNewValidRegion;
  mLastPaintSurfaceMode = mode;
  mLastPaintContentType = content;
}