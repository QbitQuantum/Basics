CGContextRef
gfxQuartzNativeDrawing::BeginNativeDrawing()
{
  NS_ASSERTION(!mCGContext, "BeginNativeDrawing called when drawing already in progress");

  DrawTarget *dt = mDrawTarget;
  if (dt->IsDualDrawTarget() || dt->IsTiledDrawTarget() ||
      dt->GetBackendType() != BackendType::SKIA || dt->IsRecording()) {
    // We need a DrawTarget that we can get a CGContextRef from:
    Matrix transform = dt->GetTransform();

    mNativeRect = transform.TransformBounds(mNativeRect);
    mNativeRect.RoundOut();
    if (mNativeRect.IsEmpty()) {
      return nullptr;
    }

    mTempDrawTarget =
      Factory::CreateDrawTarget(BackendType::SKIA,
                                IntSize::Truncate(mNativeRect.width, mNativeRect.height),
                                SurfaceFormat::B8G8R8A8);
    if (!mTempDrawTarget) {
      return nullptr;
    }

    transform.PostTranslate(-mNativeRect.x, -mNativeRect.y);
    mTempDrawTarget->SetTransform(transform);

    dt = mTempDrawTarget;
  } else {
    // Clip the DT in case BorrowedCGContext needs to create a new layer.
    // This prevents it from creating a new layer the size of the window.
    // But make sure that this clip is device pixel aligned.
    Matrix transform = dt->GetTransform();

    Rect deviceRect = transform.TransformBounds(mNativeRect);
    deviceRect.RoundOut();
    mNativeRect = transform.Inverse().TransformBounds(deviceRect);
    mDrawTarget->PushClipRect(mNativeRect);
  }

  MOZ_ASSERT(dt->GetBackendType() == BackendType::SKIA);
  mCGContext = mBorrowedContext.Init(dt);

  if (NS_WARN_IF(!mCGContext)) {
    // Failed borrowing CG context, so we need to clean up.
    if (!mTempDrawTarget) {
      mDrawTarget->PopClip();
    }
    return nullptr;
  }

  return mCGContext;
}