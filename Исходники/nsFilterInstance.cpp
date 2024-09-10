nsresult
nsFilterInstance::BuildSourcePaint(SourceInfo *aSource,
                                   DrawTarget* aTargetDT)
{
  MOZ_ASSERT(mTargetFrame);
  nsIntRect neededRect = aSource->mNeededBounds;

  RefPtr<DrawTarget> offscreenDT =
    gfxPlatform::GetPlatform()->CreateOffscreenContentDrawTarget(
      neededRect.Size(), SurfaceFormat::B8G8R8A8);
  if (!offscreenDT || !offscreenDT->IsValid()) {
    return NS_ERROR_OUT_OF_MEMORY;
  }

  gfxMatrix deviceToFilterSpace = GetFilterSpaceToDeviceSpaceTransform();
  if (!deviceToFilterSpace.Invert()) {
    return NS_ERROR_FAILURE;
  }

  if (!mPaintTransform.IsSingular()) {
    RefPtr<gfxContext> gfx = gfxContext::CreateOrNull(offscreenDT);
    MOZ_ASSERT(gfx); // already checked the draw target above
    gfx->Save();
    gfx->Multiply(mPaintTransform *
                  deviceToFilterSpace *
                  gfxMatrix::Translation(-neededRect.TopLeft()));
    GeneralPattern pattern;
    if (aSource == &mFillPaint) {
      nsSVGUtils::MakeFillPatternFor(mTargetFrame, gfx, &pattern);
    } else if (aSource == &mStrokePaint) {
      nsSVGUtils::MakeStrokePatternFor(mTargetFrame, gfx, &pattern);
    }
    if (pattern.GetPattern()) {
      offscreenDT->FillRect(ToRect(FilterSpaceToUserSpace(ThebesRect(neededRect))),
                            pattern);
    }
    gfx->Restore();
  }

  aSource->mSourceSurface = offscreenDT->Snapshot();
  aSource->mSurfaceRect = neededRect;

  return NS_OK;
}