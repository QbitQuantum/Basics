DEF_TEST(Paint_flattening, reporter) {
    const SkFilterQuality levels[] = {
        kNone_SkFilterQuality,
        kLow_SkFilterQuality,
        kMedium_SkFilterQuality,
        kHigh_SkFilterQuality,
    };
    const SkPaint::Hinting hinting[] = {
        SkPaint::kNo_Hinting,
        SkPaint::kSlight_Hinting,
        SkPaint::kNormal_Hinting,
        SkPaint::kFull_Hinting,
    };
    const SkPaint::Align align[] = {
        SkPaint::kLeft_Align,
        SkPaint::kCenter_Align,
        SkPaint::kRight_Align
    };
    const SkPaint::Cap caps[] = {
        SkPaint::kButt_Cap,
        SkPaint::kRound_Cap,
        SkPaint::kSquare_Cap,
    };
    const SkPaint::Join joins[] = {
        SkPaint::kMiter_Join,
        SkPaint::kRound_Join,
        SkPaint::kBevel_Join,
    };
    const SkPaint::TextEncoding encodings[] = {
        SkPaint::kUTF8_TextEncoding,
        SkPaint::kUTF16_TextEncoding,
        SkPaint::kUTF32_TextEncoding,
        SkPaint::kGlyphID_TextEncoding,
    };
    const SkPaint::Style styles[] = {
        SkPaint::kFill_Style,
        SkPaint::kStroke_Style,
        SkPaint::kStrokeAndFill_Style,
    };

#define FOR_SETUP(index, array, setter)                                 \
    for (size_t index = 0; index < SK_ARRAY_COUNT(array); ++index) {    \
        paint.setter(array[index]);                                     \

    SkPaint paint;
    paint.setFlags(0x1234);

    FOR_SETUP(i, levels, setFilterQuality)
    FOR_SETUP(j, hinting, setHinting)
    FOR_SETUP(k, align, setTextAlign)
    FOR_SETUP(l, caps, setStrokeCap)
    FOR_SETUP(m, joins, setStrokeJoin)
    FOR_SETUP(n, encodings, setTextEncoding)
    FOR_SETUP(p, styles, setStyle)

    SkWriteBuffer writer;
    paint.flatten(writer);

    const uint32_t* written = writer.getWriter32()->contiguousArray();
    SkReadBuffer reader(written, writer.bytesWritten());

    SkPaint paint2;
    paint2.unflatten(reader);
    REPORTER_ASSERT(reporter, paint2 == paint);

    }}}}}}}