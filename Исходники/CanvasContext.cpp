void CanvasContext::draw() {
    LOG_ALWAYS_FATAL_IF(!mCanvas || mEglSurface == EGL_NO_SURFACE,
            "drawRenderNode called on a context with no canvas or surface!");

    profiler().markPlaybackStart();

    SkRect dirty;
    mDamageAccumulator.finish(&dirty);

    EGLint width, height;
    mEglManager.beginFrame(mEglSurface, &width, &height);
    if (width != mCanvas->getViewportWidth() || height != mCanvas->getViewportHeight()) {
        mCanvas->setViewport(width, height);
        dirty.setEmpty();
    } else if (!mDirtyRegionsEnabled || mHaveNewSurface) {
        dirty.setEmpty();
    } else {
        if (!dirty.isEmpty() && !dirty.intersect(0, 0, width, height)) {
            ALOGW("Dirty " RECT_STRING " doesn't intersect with 0 0 %d %d ?",
                    SK_RECT_ARGS(dirty), width, height);
            dirty.setEmpty();
        }
        profiler().unionDirty(&dirty);
    }

    status_t status;
    if (!dirty.isEmpty()) {
        status = mCanvas->prepareDirty(dirty.fLeft, dirty.fTop,
                dirty.fRight, dirty.fBottom, mOpaque);
    } else {
        status = mCanvas->prepare(mOpaque);
    }

    Rect outBounds;
    status |= mCanvas->drawRenderNode(mRootRenderNode.get(), outBounds);

    profiler().draw(mCanvas);

    mCanvas->finish();

    profiler().markPlaybackEnd();

    if (status & DrawGlInfo::kStatusDrew) {
        swapBuffers();
    }

    profiler().finishFrame();
}