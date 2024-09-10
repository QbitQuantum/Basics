// copyTo() should preserve isOpaque when it makes sense
static void test_isOpaque(skiatest::Reporter* reporter, const SkBitmap& src,
                          SkBitmap::Config dstConfig) {
    SkBitmap bitmap(src);
    SkBitmap dst;

    // we need the lock so that we get a valid colorTable (when available)
    SkAutoLockPixels alp(bitmap);
    SkColorTable* ctable = bitmap.getColorTable();
    unsigned ctableFlags = ctable ? ctable->getFlags() : 0;

    if (canHaveAlpha(bitmap.config()) && canHaveAlpha(dstConfig)) {
        bitmap.setIsOpaque(false);
        if (ctable) {
            ctable->setFlags(ctableFlags & ~SkColorTable::kColorsAreOpaque_Flag);
        }
        REPORTER_ASSERT(reporter, bitmap.copyTo(&dst, dstConfig));
        REPORTER_ASSERT(reporter, dst.config() == dstConfig);
        if (bitmap.isOpaque() != dst.isOpaque()) {
            report_opaqueness(reporter, bitmap, dst);
        }
    }

    bitmap.setIsOpaque(true);
    if (ctable) {
        ctable->setFlags(ctableFlags | SkColorTable::kColorsAreOpaque_Flag);
    }
    REPORTER_ASSERT(reporter, bitmap.copyTo(&dst, dstConfig));
    REPORTER_ASSERT(reporter, dst.config() == dstConfig);
    if (bitmap.isOpaque() != dst.isOpaque()) {
        report_opaqueness(reporter, bitmap, dst);
    }

    if (ctable) {
        ctable->setFlags(ctableFlags);
    }
}