/**
 * Given either a SkStream or a SkData, try to decode the encoded
 * image using the specified options and report errors.
 */
static void test_options(skiatest::Reporter* reporter,
                         const SkDecodingImageGenerator::Options& opts,
                         SkStreamRewindable* encodedStream,
                         SkData* encodedData,
                         bool useData,
                         const SkString& path) {
    SkBitmap bm;
    bool success = false;
    if (useData) {
        if (NULL == encodedData) {
            return;
        }
        success = SkInstallDiscardablePixelRef(
            SkDecodingImageGenerator::Create(encodedData, opts), &bm);
    } else {
        if (NULL == encodedStream) {
            return;
        }
        success = SkInstallDiscardablePixelRef(
            SkDecodingImageGenerator::Create(encodedStream->duplicate(), opts), &bm);
    }
    if (!success) {
        if (opts.fUseRequestedColorType
            && (kARGB_4444_SkColorType == opts.fRequestedColorType)) {
            return;  // Ignore known conversion inabilities.
        }
        // If we get here, it's a failure and we will need more
        // information about why it failed.
        ERRORF(reporter, "Bounds decode failed [sampleSize=%d dither=%s "
               "colorType=%s %s]", opts.fSampleSize, yn(opts.fDitherImage),
               options_colorType(opts), path.c_str());
        return;
    }
    #if defined(SK_BUILD_FOR_ANDROID) || defined(SK_BUILD_FOR_UNIX)
    // Android is the only system that use Skia's image decoders in
    // production.  For now, we'll only verify that samplesize works
    // on systems where it already is known to work.
    REPORTER_ASSERT(reporter, check_rounding(bm.height(), kExpectedHeight,
                                             opts.fSampleSize));
    REPORTER_ASSERT(reporter, check_rounding(bm.width(), kExpectedWidth,
                                             opts.fSampleSize));
    // The ImageDecoder API doesn't guarantee that SampleSize does
    // anything at all, but the decoders that this test excercises all
    // produce an output size in the following range:
    //    (((sample_size * out_size) > (in_size - sample_size))
    //     && out_size <= SkNextPow2(((in_size - 1) / sample_size) + 1));
    #endif  // SK_BUILD_FOR_ANDROID || SK_BUILD_FOR_UNIX
    SkAutoLockPixels alp(bm);
    if (bm.getPixels() == NULL) {
        ERRORF(reporter, "Pixel decode failed [sampleSize=%d dither=%s "
               "colorType=%s %s]", opts.fSampleSize, yn(opts.fDitherImage),
               options_colorType(opts), path.c_str());
        return;
    }

    SkColorType requestedColorType = opts.fRequestedColorType;
    REPORTER_ASSERT(reporter,
                    (!opts.fUseRequestedColorType)
                    || (bm.colorType() == requestedColorType));

    // Condition under which we should check the decoding results:
    if ((kN32_SkColorType == bm.colorType())
        && (!path.endsWith(".jpg"))  // lossy
        && (opts.fSampleSize == 1)) {  // scaled
        const SkColor* correctPixels = kExpectedPixels;
        SkASSERT(bm.height() == kExpectedHeight);
        SkASSERT(bm.width() == kExpectedWidth);
        int pixelErrors = 0;
        for (int y = 0; y < bm.height(); ++y) {
            for (int x = 0; x < bm.width(); ++x) {
                if (*correctPixels != bm.getColor(x, y)) {
                    ++pixelErrors;
                }
                ++correctPixels;
            }
        }
        if (pixelErrors != 0) {
            ERRORF(reporter, "Pixel-level mismatch (%d of %d) "
                   "[sampleSize=%d dither=%s colorType=%s %s]",
                   pixelErrors, kExpectedHeight * kExpectedWidth,
                   opts.fSampleSize, yn(opts.fDitherImage),
                   options_colorType(opts), path.c_str());
        }
    }
}