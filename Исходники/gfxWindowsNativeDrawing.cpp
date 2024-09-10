void
gfxWindowsNativeDrawing::PaintToContext()
{
    if (mRenderState == RENDER_STATE_NATIVE_DRAWING_DONE) {
        // nothing to do, it already went to the context
        mRenderState = RENDER_STATE_DONE;
    } else if (mRenderState == RENDER_STATE_ALPHA_RECOVERY_WHITE_DONE) {
        RefPtr<gfxImageSurface> black = mBlackSurface->GetAsImageSurface();
        RefPtr<gfxImageSurface> white = mWhiteSurface->GetAsImageSurface();
        if (!gfxAlphaRecovery::RecoverAlpha(black, white)) {
            NS_ERROR("Alpha recovery failure");
            return;
        }
        RefPtr<DataSourceSurface> source =
            Factory::CreateWrappingDataSourceSurface(black->Data(),
                                                     black->Stride(),
                                                     black->GetSize(),
                                                     SurfaceFormat::B8G8R8A8);
        {
            DrawTarget* dt = mContext->GetDrawTarget();
            AutoRestoreTransform autoRestoreTransform(dt);

            Matrix newTransform = dt->GetTransform();
            newTransform.PreTranslate(ToPoint(mNativeRect.TopLeft()));
            dt->SetTransform(newTransform);

            Rect rect(Point(0.0, 0.0), ToSize(mNativeRect.Size()));
            Matrix m = Matrix::Scaling(1.0 / mScale.width, 1.0 / mScale.height);
            Filter filter = (mNativeDrawFlags & DO_NEAREST_NEIGHBOR_FILTERING)
                          ? Filter::LINEAR
                          : Filter::GOOD;
            SurfacePattern pat(source, ExtendMode::CLAMP, m, filter);
            dt->FillRect(rect, pat);
        }

        mRenderState = RENDER_STATE_DONE;
    } else {
        NS_ERROR("Invalid RenderState in gfxWindowsNativeDrawing::PaintToContext");
    }
}