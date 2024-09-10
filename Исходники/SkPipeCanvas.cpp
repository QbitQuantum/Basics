/*
 *  Header:
 *      paint flags     : 32
 *      non_def bits    : 16
 *      xfermode enum   : 8
 *      pad zeros       : 8
 */
static void write_paint(SkWriteBuffer& writer, const SkPaint& paint, unsigned usage) {
    uint32_t packedFlags = pack_paint_flags(paint.getFlags(), paint.getHinting(),
                                            paint.getTextAlign(), paint.getFilterQuality(),
                                            paint.getStyle(), paint.getStrokeCap(),
                                            paint.getStrokeJoin(), paint.getTextEncoding());
    writer.write32(packedFlags);

    unsigned nondef = compute_nondef(paint, (PaintUsage)usage);
    const uint8_t pad = 0;
    writer.write32((nondef << 16) | ((unsigned)paint.getBlendMode() << 8) | pad);

    CHECK_WRITE_SCALAR(writer, nondef, paint, TextSize);
    CHECK_WRITE_SCALAR(writer, nondef, paint, TextScaleX);
    CHECK_WRITE_SCALAR(writer, nondef, paint, TextSkewX);
    CHECK_WRITE_SCALAR(writer, nondef, paint, StrokeWidth);
    CHECK_WRITE_SCALAR(writer, nondef, paint, StrokeMiter);

    if (nondef & kColor_NonDef) {
        writer.write32(paint.getColor());
    }
    if (nondef & kTypeface_NonDef) {
        // TODO: explore idea of writing bits indicating "use the prev (or prev N) face"
        // e.g. 1-N bits is an index into a ring buffer of typefaces
        SkTypeface* tf = paint.getTypeface();
        SkASSERT(tf);
        writer.writeTypeface(tf);
    }

    CHECK_WRITE_FLATTENABLE(writer, nondef, paint, PathEffect);
    CHECK_WRITE_FLATTENABLE(writer, nondef, paint, Shader);
    CHECK_WRITE_FLATTENABLE(writer, nondef, paint, MaskFilter);
    CHECK_WRITE_FLATTENABLE(writer, nondef, paint, ColorFilter);
    CHECK_WRITE_FLATTENABLE(writer, nondef, paint, Rasterizer);
    CHECK_WRITE_FLATTENABLE(writer, nondef, paint, ImageFilter);
    CHECK_WRITE_FLATTENABLE(writer, nondef, paint, DrawLooper);
}