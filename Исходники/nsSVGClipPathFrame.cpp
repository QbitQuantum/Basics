already_AddRefed<SourceSurface>
nsSVGClipPathFrame::GetClipMask(gfxContext& aReferenceContext,
                                nsIFrame* aClippedFrame,
                                const gfxMatrix& aMatrix,
                                Matrix* aMaskTransform,
                                SourceSurface* aExtraMask,
                                const Matrix& aExtraMasksTransform)
{
  MOZ_ASSERT(!IsTrivial(), "Caller needs to use ApplyClipPath");

  DrawTarget& aReferenceDT = *aReferenceContext.GetDrawTarget();

  // A clipPath can reference another clipPath.  We re-enter this method for
  // each clipPath in a reference chain, so here we limit chain length:
  static int16_t sRefChainLengthCounter = AutoReferenceLimiter::notReferencing;
  AutoReferenceLimiter
    refChainLengthLimiter(&sRefChainLengthCounter,
                          MAX_SVG_CLIP_PATH_REFERENCE_CHAIN_LENGTH);
  if (!refChainLengthLimiter.Reference()) {
    return nullptr; // Reference chain is too long!
  }

  // And to prevent reference loops we check that this clipPath only appears
  // once in the reference chain (if any) that we're currently processing:
  AutoReferenceLimiter refLoopDetector(&mReferencing, 1);
  if (!refLoopDetector.Reference()) {
    return nullptr; // Reference loop!
  }

  IntRect devSpaceClipExtents;
  {
    gfxContextMatrixAutoSaveRestore autoRestoreMatrix(&aReferenceContext);

    aReferenceContext.SetMatrix(gfxMatrix());
    gfxRect rect = aReferenceContext.GetClipExtents();
    devSpaceClipExtents = RoundedOut(ToRect(rect));
    if (devSpaceClipExtents.IsEmpty()) {
      // We don't need to create a mask surface, all drawing is clipped anyway.
      return nullptr;
    }
  }

  RefPtr<DrawTarget> maskDT =
    aReferenceDT.CreateSimilarDrawTarget(devSpaceClipExtents.Size(),
                                         SurfaceFormat::A8);

  gfxMatrix mat = aReferenceContext.CurrentMatrix() *
                    gfxMatrix::Translation(-devSpaceClipExtents.TopLeft());

  // Paint this clipPath's contents into maskDT:
  {
    RefPtr<gfxContext> ctx = new gfxContext(maskDT);
    ctx->SetMatrix(mat);

    // We need to set mMatrixForChildren here so that under the PaintSVG calls
    // on our children (below) our GetCanvasTM() method will return the correct
    // transform.
    mMatrixForChildren = GetClipPathTransform(aClippedFrame) * aMatrix;

    // Check if this clipPath is itself clipped by another clipPath:
    nsSVGClipPathFrame* clipPathThatClipsClipPath =
      nsSVGEffects::GetEffectProperties(this).GetClipPathFrame(nullptr);
    bool clippingOfClipPathRequiredMasking;
    if (clipPathThatClipsClipPath) {
      ctx->Save();
      clippingOfClipPathRequiredMasking = !clipPathThatClipsClipPath->IsTrivial();
      if (!clippingOfClipPathRequiredMasking) {
        clipPathThatClipsClipPath->ApplyClipPath(*ctx, aClippedFrame, aMatrix);
      } else {
        Matrix maskTransform;
        RefPtr<SourceSurface> mask =
          clipPathThatClipsClipPath->GetClipMask(*ctx, aClippedFrame,
                                                 aMatrix, &maskTransform);
        ctx->PushGroupForBlendBack(gfxContentType::ALPHA, 1.0,
                                   mask, maskTransform);
        // The corresponding PopGroupAndBlend call below will mask the
        // blend using |mask|.
      }
    }

    // Paint our children into the mask:
    for (nsIFrame* kid = mFrames.FirstChild(); kid;
         kid = kid->GetNextSibling()) {
      nsISVGChildFrame* SVGFrame = do_QueryFrame(kid);
      if (SVGFrame) {
        // The CTM of each frame referencing us can be different.
        SVGFrame->NotifySVGChanged(nsISVGChildFrame::TRANSFORM_CHANGED);

        bool isOK = true;
        // Children of this clipPath may themselves be clipped.
        nsSVGClipPathFrame *clipPathThatClipsChild =
          nsSVGEffects::GetEffectProperties(kid).GetClipPathFrame(&isOK);
        if (!isOK) {
          continue;
        }

        bool childsClipPathRequiresMasking;

        if (clipPathThatClipsChild) {
          childsClipPathRequiresMasking = !clipPathThatClipsChild->IsTrivial();
          ctx->Save();
          if (!childsClipPathRequiresMasking) {
            clipPathThatClipsChild->ApplyClipPath(*ctx, aClippedFrame, aMatrix);
          } else {
            Matrix maskTransform;
            RefPtr<SourceSurface> mask =
              clipPathThatClipsChild->GetClipMask(*ctx, aClippedFrame,
                                                  aMatrix, &maskTransform);
            ctx->PushGroupForBlendBack(gfxContentType::ALPHA, 1.0,
                                       mask, maskTransform);
            // The corresponding PopGroupAndBlend call below will mask the
            // blend using |mask|.
          }
        }

        gfxMatrix toChildsUserSpace = mMatrixForChildren;
        nsIFrame* child = do_QueryFrame(SVGFrame);
        nsIContent* childContent = child->GetContent();
        if (childContent->IsSVGElement()) {
          toChildsUserSpace =
            static_cast<const nsSVGElement*>(childContent)->
              PrependLocalTransformsTo(mMatrixForChildren, eUserSpaceToParent);
        }

        // Our children have NS_STATE_SVG_CLIPPATH_CHILD set on them, and
        // nsSVGPathGeometryFrame::Render checks for that state bit and paints
        // only the geometry (opaque black) if set.
        SVGFrame->PaintSVG(*ctx, toChildsUserSpace);

        if (clipPathThatClipsChild) {
          if (childsClipPathRequiresMasking) {
            ctx->PopGroupAndBlend();
          }
          ctx->Restore();
        }
      }
    }


    if (clipPathThatClipsClipPath) {
      if (clippingOfClipPathRequiredMasking) {
        ctx->PopGroupAndBlend();
      }
      ctx->Restore();
    }
  }

  // Moz2D transforms in the opposite direction to Thebes
  mat.Invert();

  if (aExtraMask) {
    // We could potentially due this more efficiently with OPERATOR_IN
    // but that operator does not work well on CG or D2D
    RefPtr<SourceSurface> currentMask = maskDT->Snapshot();
    Matrix transform = maskDT->GetTransform();
    maskDT->SetTransform(Matrix());
    maskDT->ClearRect(Rect(0, 0,
                           devSpaceClipExtents.width,
                           devSpaceClipExtents.height));
    maskDT->SetTransform(aExtraMasksTransform * transform);
    // draw currentMask with the inverse of the transform that we just so that
    // it ends up in the same spot with aExtraMask transformed by aExtraMasksTransform
    maskDT->MaskSurface(SurfacePattern(currentMask, ExtendMode::CLAMP, aExtraMasksTransform.Inverse() * ToMatrix(mat)),
                        aExtraMask,
                        Point(0, 0));
  }

  *aMaskTransform = ToMatrix(mat);
  return maskDT->Snapshot();
}