static void
GenerateMaskSurface(const nsSVGIntegrationUtils::PaintFramesParams& aParams,
                    float aOpacity, nsStyleContext* aSC,
                    const nsTArray<nsSVGMaskFrame *>& aMaskFrames,
                    const nsPoint& aOffsetToUserSpace,
                    Matrix& aOutMaskTransform,
                    RefPtr<SourceSurface>& aOutMaskSurface)
{
  const nsStyleSVGReset *svgReset = aSC->StyleSVGReset();
  MOZ_ASSERT(aMaskFrames.Length() > 0);

  gfxMatrix cssPxToDevPxMatrix =
    nsSVGIntegrationUtils::GetCSSPxToDevPxMatrix(aParams.frame);

  gfxContext& ctx = aParams.ctx;

  // There is only one SVG mask.
  if (((aMaskFrames.Length() == 1) && aMaskFrames[0])) {
    aOutMaskSurface =
      aMaskFrames[0]->GetMaskForMaskedFrame(&ctx, aParams.frame,
                                            cssPxToDevPxMatrix, aOpacity,
                                            &aOutMaskTransform,
                                            svgReset->mMask.mLayers[0].mMaskMode);
    return;
  }

  IntRect maskSurfaceRect = ComputeMaskGeometry(aParams, svgReset,
                                                aOffsetToUserSpace,
                                                aMaskFrames);
  if (maskSurfaceRect.IsEmpty()) {
    return;
  }

  // Mask composition result on CoreGraphic::A8 surface is not correct
  // when mask-mode is not add(source over). Switch to skia when CG backend
  // detected.
  RefPtr<DrawTarget> maskDT =
    (ctx.GetDrawTarget()->GetBackendType() == BackendType::COREGRAPHICS ||
     ctx.GetDrawTarget()->GetBackendType() == BackendType::DIRECT2D1_1)
    ? Factory::CreateDrawTarget(BackendType::SKIA, maskSurfaceRect.Size(),
                                SurfaceFormat::A8)
    : ctx.GetDrawTarget()->CreateSimilarDrawTarget(maskSurfaceRect.Size(),
                                                   SurfaceFormat::A8);
  if (!maskDT || !maskDT->IsValid()) {
    return;
  }

  RefPtr<gfxContext> maskContext = gfxContext::CreateOrNull(maskDT);
  MOZ_ASSERT(maskContext);

  nsPresContext* presContext = aParams.frame->PresContext();
  gfxPoint devPixelOffsetToUserSpace =
    nsLayoutUtils::PointToGfxPoint(aOffsetToUserSpace,
                                   presContext->AppUnitsPerDevPixel());

  // Set ctx's matrix on maskContext, offset by the maskSurfaceRect's position.
  // This makes sure that we combine the masks in device space.
  gfxMatrix maskSurfaceMatrix =
    ctx.CurrentMatrix() * gfxMatrix::Translation(-maskSurfaceRect.TopLeft());
  maskContext->SetMatrix(maskSurfaceMatrix);

  // Multiple SVG masks interleave with image mask. Paint each layer onto
  // maskDT one at a time.
  for (int i = aMaskFrames.Length() - 1; i >= 0 ; i--) {
    nsSVGMaskFrame *maskFrame = aMaskFrames[i];

    CompositionOp compositionOp = (i == int(aMaskFrames.Length() - 1))
      ? CompositionOp::OP_OVER
      : nsCSSRendering::GetGFXCompositeMode(svgReset->mMask.mLayers[i].mComposite);

    // maskFrame != nullptr means we get a SVG mask.
    // maskFrame == nullptr means we get an image mask.
    if (maskFrame) {
      Matrix svgMaskMatrix;
      RefPtr<SourceSurface> svgMask =
        maskFrame->GetMaskForMaskedFrame(maskContext, aParams.frame,
                                         cssPxToDevPxMatrix, aOpacity,
                                         &svgMaskMatrix,
                                         svgReset->mMask.mLayers[i].mMaskMode);
      if (svgMask) {
        gfxContextMatrixAutoSaveRestore matRestore(maskContext);

        maskContext->Multiply(ThebesMatrix(svgMaskMatrix));
        Rect drawRect = IntRectToRect(IntRect(IntPoint(0, 0), svgMask->GetSize()));
        maskDT->DrawSurface(svgMask, drawRect, drawRect, DrawSurfaceOptions(),
                            DrawOptions(1.0f, compositionOp));
      }
    } else {
      gfxContextMatrixAutoSaveRestore matRestore(maskContext);

      maskContext->Multiply(gfxMatrix::Translation(-devPixelOffsetToUserSpace));
      nsRenderingContext rc(maskContext);
      nsCSSRendering::PaintBGParams  params =
        nsCSSRendering::PaintBGParams::ForSingleLayer(*presContext,
                                                      rc, aParams.dirtyRect,
                                                      aParams.borderArea,
                                                      aParams.frame,
                                                      aParams.builder->GetBackgroundPaintFlags() |
                                                      nsCSSRendering::PAINTBG_MASK_IMAGE,
                                                      i, compositionOp);

      // FIXME We should use the return value, see bug 1258510.
      Unused << nsCSSRendering::PaintBackgroundWithSC(params, aSC,
                                                      *aParams.frame->StyleBorder());
    }
  }

  aOutMaskTransform = ToMatrix(maskSurfaceMatrix);
  if (!aOutMaskTransform.Invert()) {
    return;
  }

  aOutMaskSurface = maskDT->Snapshot();
}