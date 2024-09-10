void
BasicCompositor::DrawQuad(const gfx::Rect& aRect,
                          const gfx::Rect& aClipRect,
                          const EffectChain &aEffectChain,
                          gfx::Float aOpacity,
                          const gfx::Matrix4x4& aTransform,
                          const gfx::Rect& aVisibleRect)
{
  RefPtr<DrawTarget> buffer = mRenderTarget->mDrawTarget;

  // For 2D drawing, |dest| and |buffer| are the same surface. For 3D drawing,
  // |dest| is a temporary surface.
  RefPtr<DrawTarget> dest = buffer;

  buffer->PushClipRect(aClipRect);
  AutoRestoreTransform autoRestoreTransform(dest);

  Matrix newTransform;
  Rect transformBounds;
  Matrix4x4 new3DTransform;
  IntPoint offset = mRenderTarget->GetOrigin();

  if (aTransform.Is2D()) {
    newTransform = aTransform.As2D();
  } else {
    // Create a temporary surface for the transform.
    dest = gfxPlatform::GetPlatform()->CreateOffscreenContentDrawTarget(RoundOut(aRect).Size(), SurfaceFormat::B8G8R8A8);
    if (!dest) {
      return;
    }

    dest->SetTransform(Matrix::Translation(-aRect.x, -aRect.y));

    // Get the bounds post-transform.
    transformBounds = aTransform.TransformAndClipBounds(aRect, Rect(offset.x, offset.y, buffer->GetSize().width, buffer->GetSize().height));
    transformBounds.RoundOut();

    // Propagate the coordinate offset to our 2D draw target.
    newTransform = Matrix::Translation(transformBounds.x, transformBounds.y);

    // When we apply the 3D transformation, we do it against a temporary
    // surface, so undo the coordinate offset.
    new3DTransform = Matrix4x4::Translation(aRect.x, aRect.y, 0) * aTransform;
  }

  newTransform.PostTranslate(-offset.x, -offset.y);
  buffer->SetTransform(newTransform);

  RefPtr<SourceSurface> sourceMask;
  Matrix maskTransform;
  if (aEffectChain.mSecondaryEffects[EffectTypes::MASK]) {
    EffectMask *effectMask = static_cast<EffectMask*>(aEffectChain.mSecondaryEffects[EffectTypes::MASK].get());
    sourceMask = effectMask->mMaskTexture->AsSourceBasic()->GetSurface(dest);
    MOZ_ASSERT(effectMask->mMaskTransform.Is2D(), "How did we end up with a 3D transform here?!");
    MOZ_ASSERT(!effectMask->mIs3D);
    maskTransform = effectMask->mMaskTransform.As2D();
    maskTransform.PreTranslate(-offset.x, -offset.y);
  }

  CompositionOp blendMode = CompositionOp::OP_OVER;
  if (Effect* effect = aEffectChain.mSecondaryEffects[EffectTypes::BLEND_MODE].get()) {
    blendMode = static_cast<EffectBlendMode*>(effect)->mBlendMode;
  }

  switch (aEffectChain.mPrimaryEffect->mType) {
    case EffectTypes::SOLID_COLOR: {
      EffectSolidColor* effectSolidColor =
        static_cast<EffectSolidColor*>(aEffectChain.mPrimaryEffect.get());

      FillRectWithMask(dest, aRect, effectSolidColor->mColor,
                       DrawOptions(aOpacity, blendMode), sourceMask, &maskTransform);
      break;
    }
    case EffectTypes::RGB: {
      TexturedEffect* texturedEffect =
          static_cast<TexturedEffect*>(aEffectChain.mPrimaryEffect.get());
      TextureSourceBasic* source = texturedEffect->mTexture->AsSourceBasic();

      if (texturedEffect->mPremultiplied) {
          DrawSurfaceWithTextureCoords(dest, aRect,
                                       source->GetSurface(dest),
                                       texturedEffect->mTextureCoords,
                                       texturedEffect->mFilter,
                                       DrawOptions(aOpacity, blendMode),
                                       sourceMask, &maskTransform);
      } else {
          RefPtr<DataSourceSurface> srcData = source->GetSurface(dest)->GetDataSurface();

          // Yes, we re-create the premultiplied data every time.
          // This might be better with a cache, eventually.
          RefPtr<DataSourceSurface> premultData = gfxUtils::CreatePremultipliedDataSurface(srcData);

          DrawSurfaceWithTextureCoords(dest, aRect,
                                       premultData,
                                       texturedEffect->mTextureCoords,
                                       texturedEffect->mFilter,
                                       DrawOptions(aOpacity, blendMode),
                                       sourceMask, &maskTransform);
      }
      break;
    }
    case EffectTypes::YCBCR: {
      NS_RUNTIMEABORT("Can't (easily) support component alpha with BasicCompositor!");
      break;
    }
    case EffectTypes::RENDER_TARGET: {
      EffectRenderTarget* effectRenderTarget =
        static_cast<EffectRenderTarget*>(aEffectChain.mPrimaryEffect.get());
      RefPtr<BasicCompositingRenderTarget> surface
        = static_cast<BasicCompositingRenderTarget*>(effectRenderTarget->mRenderTarget.get());
      RefPtr<SourceSurface> sourceSurf = surface->mDrawTarget->Snapshot();

      DrawSurfaceWithTextureCoords(dest, aRect,
                                   sourceSurf,
                                   effectRenderTarget->mTextureCoords,
                                   effectRenderTarget->mFilter,
                                   DrawOptions(aOpacity, blendMode),
                                   sourceMask, &maskTransform);
      break;
    }
    case EffectTypes::COMPONENT_ALPHA: {
      NS_RUNTIMEABORT("Can't (easily) support component alpha with BasicCompositor!");
      break;
    }
    default: {
      NS_RUNTIMEABORT("Invalid effect type!");
      break;
    }
  }

  if (!aTransform.Is2D()) {
    dest->Flush();

    RefPtr<SourceSurface> snapshot = dest->Snapshot();
    RefPtr<DataSourceSurface> source = snapshot->GetDataSurface();
    RefPtr<DataSourceSurface> temp =
      Factory::CreateDataSourceSurface(RoundOut(transformBounds).Size(), SurfaceFormat::B8G8R8A8
#ifdef MOZ_ENABLE_SKIA
        , true
#endif
        );
    if (NS_WARN_IF(!temp)) {
      buffer->PopClip();
      return;
    }

    Transform(temp, source, new3DTransform, transformBounds.TopLeft());

    transformBounds.MoveTo(0, 0);
    buffer->DrawSurface(temp, transformBounds, transformBounds);
  }

  buffer->PopClip();
}