// Basic test of the SkSpecialImage public API (e.g., peekTexture, peekPixels & draw)
static void test_image(const sk_sp<SkSpecialImage>& img, skiatest::Reporter* reporter,
                       GrContext* context, bool isGPUBacked,
                       int offset, int size) {
    const SkIRect subset = img->subset();
    REPORTER_ASSERT(reporter, offset == subset.left());
    REPORTER_ASSERT(reporter, offset == subset.top());
    REPORTER_ASSERT(reporter, kSmallerSize == subset.width());
    REPORTER_ASSERT(reporter, kSmallerSize == subset.height());

    //--------------
    // Test that isTextureBacked reports the correct backing type
    REPORTER_ASSERT(reporter, isGPUBacked == img->isTextureBacked());

#if SK_SUPPORT_GPU
    //--------------
    // Test asTextureProxyRef - as long as there is a context this should succeed
    if (context) {
        sk_sp<GrTextureProxy> proxy(img->asTextureProxyRef(context));
        REPORTER_ASSERT(reporter, proxy);
    }
#endif

    //--------------
    // Test getROPixels - this should always succeed regardless of backing store
    SkBitmap bitmap;
    REPORTER_ASSERT(reporter, img->getROPixels(&bitmap));
    if (context) {
        REPORTER_ASSERT(reporter, kSmallerSize == bitmap.width());
        REPORTER_ASSERT(reporter, kSmallerSize == bitmap.height());
    } else {
        REPORTER_ASSERT(reporter, size == bitmap.width());
        REPORTER_ASSERT(reporter, size == bitmap.height());
    }

    //--------------
    // Test that draw restricts itself to the subset
    SkImageFilter::OutputProperties outProps(img->getColorSpace());
    sk_sp<SkSpecialSurface> surf(img->makeSurface(outProps, SkISize::Make(kFullSize, kFullSize),
                                                  kPremul_SkAlphaType));

    SkCanvas* canvas = surf->getCanvas();

    canvas->clear(SK_ColorBLUE);
    img->draw(canvas, SkIntToScalar(kPad), SkIntToScalar(kPad), nullptr);

    SkBitmap bm;
    bm.allocN32Pixels(kFullSize, kFullSize, false);

    bool result = canvas->readPixels(bm.info(), bm.getPixels(), bm.rowBytes(), 0, 0);
    SkASSERT_RELEASE(result);

    // Only the center (red) portion should've been drawn into the canvas
    REPORTER_ASSERT(reporter, SK_ColorBLUE == bm.getColor(kPad-1, kPad-1));
    REPORTER_ASSERT(reporter, SK_ColorRED  == bm.getColor(kPad, kPad));
    REPORTER_ASSERT(reporter, SK_ColorRED  == bm.getColor(kSmallerSize+kPad-1,
                                                          kSmallerSize+kPad-1));
    REPORTER_ASSERT(reporter, SK_ColorBLUE == bm.getColor(kSmallerSize+kPad,
                                                          kSmallerSize+kPad));

    //--------------
    // Test that asImage & makeTightSurface return appropriately sized objects
    // of the correct backing type
    SkIRect newSubset = SkIRect::MakeWH(subset.width(), subset.height());
    {
        sk_sp<SkImage> tightImg(img->asImage(&newSubset));

        REPORTER_ASSERT(reporter, tightImg->width() == subset.width());
        REPORTER_ASSERT(reporter, tightImg->height() == subset.height());
        REPORTER_ASSERT(reporter, isGPUBacked == tightImg->isTextureBacked());
        SkPixmap tmpPixmap;
        REPORTER_ASSERT(reporter, isGPUBacked != !!tightImg->peekPixels(&tmpPixmap));
    }
    {
        SkImageFilter::OutputProperties outProps(img->getColorSpace());
        sk_sp<SkSurface> tightSurf(img->makeTightSurface(outProps, subset.size()));

        REPORTER_ASSERT(reporter, tightSurf->width() == subset.width());
        REPORTER_ASSERT(reporter, tightSurf->height() == subset.height());
        REPORTER_ASSERT(reporter, isGPUBacked ==
                     !!tightSurf->getTextureHandle(SkSurface::kDiscardWrite_BackendHandleAccess));
        SkPixmap tmpPixmap;
        REPORTER_ASSERT(reporter, isGPUBacked != !!tightSurf->peekPixels(&tmpPixmap));
    }
}