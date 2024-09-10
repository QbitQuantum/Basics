// Blurs a small surface and creates the mask.
static already_AddRefed<SourceSurface>
CreateBlurMask(const IntSize& aRectSize,
               RectCornerRadii* aCornerRadii,
               gfxIntSize aBlurRadius,
               IntMargin& aExtendDestBy,
               IntMargin& aSliceBorder,
               DrawTarget& aDestDrawTarget)
{
  IntMargin slice;
  gfxAlphaBoxBlur blur;
  IntSize minSize =
    ComputeMinSizeForShadowShape(aCornerRadii, aBlurRadius, slice, aRectSize);
  IntRect minRect(IntPoint(), minSize);

  gfxContext* blurCtx = blur.Init(ThebesRect(Rect(minRect)), gfxIntSize(),
                                  aBlurRadius, nullptr, nullptr);

  if (!blurCtx) {
    return nullptr;
  }

  DrawTarget* blurDT = blurCtx->GetDrawTarget();
  ColorPattern black(Color(0.f, 0.f, 0.f, 1.f));

  if (aCornerRadii) {
    RefPtr<Path> roundedRect =
      MakePathForRoundedRect(*blurDT, Rect(minRect), *aCornerRadii);
    blurDT->Fill(roundedRect, black);
  } else {
    blurDT->FillRect(Rect(minRect), black);
  }

  IntPoint topLeft;
  RefPtr<SourceSurface> result = blur.DoBlur(&aDestDrawTarget, &topLeft);
  if (!result) {
    return nullptr;
  }

  IntRect expandedMinRect(topLeft, result->GetSize());
  aExtendDestBy = expandedMinRect - minRect;
  aSliceBorder = slice + aExtendDestBy;

  MOZ_ASSERT(aSliceBorder.LeftRight() <= expandedMinRect.width);
  MOZ_ASSERT(aSliceBorder.TopBottom() <= expandedMinRect.height);

  return result.forget();
}