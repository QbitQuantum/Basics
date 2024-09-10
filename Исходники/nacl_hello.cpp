    void Paint() {
        if (!fImage.is_null()) {
            SkPaint paint;
            paint.setAntiAlias(true);
            paint.setTextSize(SkIntToScalar(30));
            paint.setTextAlign(SkPaint::kCenter_Align);
            doDraw(fCanvas, paint, "Hello");

            fDeviceContext.PaintImageData(fImage, pp::Point(0, 0));
            if (!fFlushPending) {
                fFlushPending = true;
                fDeviceContext.Flush(pp::CompletionCallback(&FlushCallback, this));
            } else {
                SkDebugf("A flush is pending... Skipping flush.\n");
            }
        } else {
            SkDebugf("No pixels to write to!\n");
        }
    }