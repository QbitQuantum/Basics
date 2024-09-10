void
DrawTargetD2D1::PushClipRect(const Rect &aRect)
{
  if (!mTransform.IsRectilinear()) {
    // Whoops, this isn't a rectangle in device space, Direct2D will not deal
    // with this transform the way we want it to.
    // See remarks: http://msdn.microsoft.com/en-us/library/dd316860%28VS.85%29.aspx

    RefPtr<PathBuilder> pathBuilder = CreatePathBuilder();
    pathBuilder->MoveTo(aRect.TopLeft());
    pathBuilder->LineTo(aRect.TopRight());
    pathBuilder->LineTo(aRect.BottomRight());
    pathBuilder->LineTo(aRect.BottomLeft());
    pathBuilder->Close();
    RefPtr<Path> path = pathBuilder->Finish();
    return PushClip(path);
  }

  PushedClip clip;
  Rect rect = mTransform.TransformBounds(aRect);
  IntRect intRect;
  clip.mIsPixelAligned = rect.ToIntRect(&intRect);

  // Do not store the transform, just store the device space rectangle directly.
  clip.mBounds = D2DRect(rect);

  mPushedClips.push_back(clip);

  mDC->SetTransform(D2D1::IdentityMatrix());
  mTransformDirty = true;

  if (mClipsArePushed) {
    mDC->PushAxisAlignedClip(clip.mBounds, clip.mIsPixelAligned ? D2D1_ANTIALIAS_MODE_ALIASED : D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
  }
}