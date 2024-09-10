    virtual void recordCanvas(SkCanvas* canvas) {

        const SkPoint translateDelta = getTranslateDelta();

        for (int i = 0; i < M; i++) {

            SkColor color = SK_ColorYELLOW + (i % 255);
            SkIRect rect = SkIRect::MakeWH(i,i);

            canvas->save();

            // set the clip to the given region
            SkRegion region;
            region.setRect(rect);
            canvas->clipRegion(region);

            // fill the clip with a color
            SkPaint paint;
            paint.setColor(color);
            canvas->drawPaint(paint);

            // set a matrix on the canvas
            SkMatrix matrix;
            matrix.setRotate(SkIntToScalar(i % 360));
            canvas->setMatrix(matrix);

            // create a simple bitmap
            SkBitmap bitmap;
            bitmap.setConfig(SkBitmap::kRGB_565_Config, 10, 10);
            bitmap.allocPixels();

            // draw a single color into the bitmap
            SkCanvas bitmapCanvas(bitmap);
            bitmapCanvas.drawColor(SkColorSetA(color, i % 255));

            // draw the bitmap onto the canvas
            canvas->drawBitmapMatrix(bitmap, matrix);

            canvas->restore();
            canvas->translate(translateDelta.fX, translateDelta.fY);
        }
    }