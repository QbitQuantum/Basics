static void test_drawText(skiatest::Reporter* reporter) {

    SkPaint paint;
    paint.setColor(SK_ColorGRAY);
    paint.setTextSize(SkIntToScalar(20));

    SkIRect drawTextRect = SkIRect::MakeWH(64, 64);
    SkBitmap drawTextBitmap;
    create(&drawTextBitmap, drawTextRect, SkBitmap::kARGB_8888_Config);
    SkCanvas drawTextCanvas(drawTextBitmap);

    SkIRect drawPosTextRect = SkIRect::MakeWH(64, 64);
    SkBitmap drawPosTextBitmap;
    create(&drawPosTextBitmap, drawPosTextRect, SkBitmap::kARGB_8888_Config);
    SkCanvas drawPosTextCanvas(drawPosTextBitmap);

    for (float offsetY = 0.0f; offsetY < 1.0f; offsetY += (1.0f / 16.0f)) {
        for (float offsetX = 0.0f; offsetX < 1.0f; offsetX += (1.0f / 16.0f)) {
            SkPoint point = SkPoint::Make(SkFloatToScalar(25.0f + offsetX),
                                          SkFloatToScalar(25.0f + offsetY));

            for (int align = 0; align < SkPaint::kAlignCount; ++align) {
                paint.setTextAlign(static_cast<SkPaint::Align>(align));

                for (unsigned int flags = 0; flags < (1 << 3); ++flags) {
                    static const unsigned int antiAliasFlag = 1;
                    static const unsigned int subpixelFlag = 1 << 1;
                    static const unsigned int lcdFlag = 1 << 2;

                    paint.setAntiAlias(SkToBool(flags & antiAliasFlag));
                    paint.setSubpixelText(SkToBool(flags & subpixelFlag));
                    paint.setLCDRenderText(SkToBool(flags & lcdFlag));

                    // Test: drawText and drawPosText draw the same.
                    drawBG(&drawTextCanvas);
                    drawTextCanvas.drawText("A", 1, point.fX, point.fY, paint);

                    drawBG(&drawPosTextCanvas);
                    drawPosTextCanvas.drawPosText("A", 1, &point, paint);

                    REPORTER_ASSERT(reporter,
                        compare(drawTextBitmap, drawTextRect,
                                drawPosTextBitmap, drawPosTextRect));
                }
            }
        }
    }
}