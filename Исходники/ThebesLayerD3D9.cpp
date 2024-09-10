void
ThebesLayerD3D9::DrawRegion(nsIntRegion &aRegion, SurfaceMode aMode,
                            const nsTArray<ReadbackProcessor::Update>& aReadbackUpdates)
{
  HRESULT hr;
  nsIntRect visibleRect = mVisibleRegion.GetBounds();

  nsRefPtr<gfxASurface> destinationSurface;
  nsIntRect bounds = aRegion.GetBounds();
  nsRefPtr<IDirect3DTexture9> tmpTexture;
  OpaqueRenderer opaqueRenderer(aRegion);
  OpaqueRenderer opaqueRendererOnWhite(aRegion);

  switch (aMode)
  {
    case SurfaceMode::SURFACE_OPAQUE:
      destinationSurface = opaqueRenderer.Begin(this);
      break;

    case SurfaceMode::SURFACE_SINGLE_CHANNEL_ALPHA: {
      hr = device()->CreateTexture(bounds.width, bounds.height, 1,
                                   0, D3DFMT_A8R8G8B8,
                                   D3DPOOL_SYSTEMMEM, getter_AddRefs(tmpTexture), nullptr);

      if (FAILED(hr)) {
        ReportFailure(NS_LITERAL_CSTRING("Failed to create temporary texture in system memory."), hr);
        return;
      }

      // XXX - We may consider retaining a SYSTEMMEM texture texture the size
      // of our DEFAULT texture and then use UpdateTexture and add dirty rects
      // to update in a single call.
      nsRefPtr<gfxWindowsSurface> dest = new gfxWindowsSurface(
          gfxIntSize(bounds.width, bounds.height), gfxImageFormat::ARGB32);
      // If the contents of this layer don't require component alpha in the
      // end of rendering, it's safe to enable Cleartype since all the Cleartype
      // glyphs must be over (or under) opaque pixels.
      dest->SetSubpixelAntialiasingEnabled(!(mContentFlags & CONTENT_COMPONENT_ALPHA));
      destinationSurface = dest.forget();
      break;
    }

    case SurfaceMode::SURFACE_COMPONENT_ALPHA: {
      nsRefPtr<gfxWindowsSurface> onBlack = opaqueRenderer.Begin(this);
      nsRefPtr<gfxWindowsSurface> onWhite = opaqueRendererOnWhite.Begin(this);
      if (onBlack && onWhite) {
        FillSurface(onBlack, aRegion, bounds.TopLeft(), gfxRGBA(0.0, 0.0, 0.0, 1.0));
        FillSurface(onWhite, aRegion, bounds.TopLeft(), gfxRGBA(1.0, 1.0, 1.0, 1.0));
        gfxASurface* surfaces[2] = { onBlack.get(), onWhite.get() };
        destinationSurface = new gfxTeeSurface(surfaces, ArrayLength(surfaces));
        // Using this surface as a source will likely go horribly wrong, since
        // only the onBlack surface will really be used, so alpha information will
        // be incorrect.
        destinationSurface->SetAllowUseAsSource(false);
      }
      break;
    }
  }

  if (!destinationSurface)
    return;

  nsRefPtr<gfxContext> context;
  if (gfxPlatform::GetPlatform()->SupportsAzureContentForType(BackendType::CAIRO)) {
     RefPtr<DrawTarget> dt =
        gfxPlatform::GetPlatform()->CreateDrawTargetForSurface(destinationSurface,
                                                               IntSize(destinationSurface->GetSize().width,
                                                                       destinationSurface->GetSize().height));

    context = new gfxContext(dt);
  } else {
    context = new gfxContext(destinationSurface);
  }

  context->Translate(gfxPoint(-bounds.x, -bounds.y));
  LayerManagerD3D9::CallbackInfo cbInfo = mD3DManager->GetCallbackInfo();
  cbInfo.Callback(this, context, aRegion, DrawRegionClip::CLIP_NONE, nsIntRegion(), cbInfo.CallbackData);

  for (uint32_t i = 0; i < aReadbackUpdates.Length(); ++i) {
    NS_ASSERTION(aMode == SurfaceMode::SURFACE_OPAQUE,
                 "Transparent surfaces should not be used for readback");
    const ReadbackProcessor::Update& update = aReadbackUpdates[i];
    nsIntPoint offset = update.mLayer->GetBackgroundLayerOffset();
    nsRefPtr<gfxContext> ctx =
        update.mLayer->GetSink()->BeginUpdate(update.mUpdateRect + offset,
                                              update.mSequenceCounter);
    if (ctx) {
      ctx->Translate(gfxPoint(offset.x, offset.y));
      ctx->SetSource(destinationSurface, gfxPoint(bounds.x, bounds.y));
      ctx->Paint();
      update.mLayer->GetSink()->EndUpdate(ctx, update.mUpdateRect + offset);
    }
  }

  // Release the cairo d3d9 surface before we try to composite it
  context = nullptr;

  nsAutoTArray<IDirect3DTexture9*,2> srcTextures;
  nsAutoTArray<IDirect3DTexture9*,2> destTextures;
  switch (aMode)
  {
    case SurfaceMode::SURFACE_OPAQUE:
      // Must release reference to dest surface before ending drawing
      destinationSurface = nullptr;
      opaqueRenderer.End();
      srcTextures.AppendElement(opaqueRenderer.GetTexture());
      destTextures.AppendElement(mTexture);
      break;

    case SurfaceMode::SURFACE_SINGLE_CHANNEL_ALPHA: {
      LockTextureRectD3D9 textureLock(tmpTexture);
      if (!textureLock.HasLock()) {
        NS_WARNING("Failed to lock ThebesLayer tmpTexture texture.");
        return;
      }

      D3DLOCKED_RECT r = textureLock.GetLockRect();

      nsRefPtr<gfxImageSurface> imgSurface =
        new gfxImageSurface((unsigned char *)r.pBits,
                            bounds.Size(),
                            r.Pitch,
                            gfxImageFormat::ARGB32);

      if (destinationSurface) {
        nsRefPtr<gfxContext> context = new gfxContext(imgSurface);
        context->SetSource(destinationSurface);
        context->SetOperator(gfxContext::OPERATOR_SOURCE);
        context->Paint();
      }

      // Must release reference to dest surface before ending drawing
      destinationSurface = nullptr;
      imgSurface = nullptr;

      srcTextures.AppendElement(tmpTexture);
      destTextures.AppendElement(mTexture);
      break;
    }

    case SurfaceMode::SURFACE_COMPONENT_ALPHA: {
      // Must release reference to dest surface before ending drawing
      destinationSurface = nullptr;
      opaqueRenderer.End();
      opaqueRendererOnWhite.End();
      srcTextures.AppendElement(opaqueRenderer.GetTexture());
      destTextures.AppendElement(mTexture);
      srcTextures.AppendElement(opaqueRendererOnWhite.GetTexture());
      destTextures.AppendElement(mTextureOnWhite);
      break;
    }
  }
  NS_ASSERTION(srcTextures.Length() == destTextures.Length(), "Mismatched lengths");
  

  // Copy to the texture.
  for (uint32_t i = 0; i < srcTextures.Length(); ++i) {
    nsRefPtr<IDirect3DSurface9> srcSurface;
    nsRefPtr<IDirect3DSurface9> dstSurface;

    destTextures[i]->GetSurfaceLevel(0, getter_AddRefs(dstSurface));
    srcTextures[i]->GetSurfaceLevel(0, getter_AddRefs(srcSurface));

    nsIntRegionRectIterator iter(aRegion);
    const nsIntRect *iterRect;
    while ((iterRect = iter.Next())) {
      RECT rect;
      rect.left = iterRect->x - bounds.x;
      rect.top = iterRect->y - bounds.y;
      rect.right = iterRect->XMost() - bounds.x;
      rect.bottom = iterRect->YMost() - bounds.y;

      POINT point;
      point.x = iterRect->x - visibleRect.x;
      point.y = iterRect->y - visibleRect.y;
      device()->UpdateSurface(srcSurface, &rect, dstSurface, &point);
    }
  }
}