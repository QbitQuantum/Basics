void SkFlatPaint::dump() const {
    SkPaint defaultPaint;
    SkFlattenableReadBuffer buffer(fPaintData);
    SkTypeface* typeface = (SkTypeface*) buffer.readPtr();
    char pBuffer[DUMP_BUFFER_SIZE];
    char* bufferPtr = pBuffer;
    bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
        "paint: ");
    if (typeface != defaultPaint.getTypeface())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "typeface:%p ", typeface);
    SkScalar textSize = buffer.readScalar();
    if (textSize != defaultPaint.getTextSize())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "textSize:%g ", SkScalarToFloat(textSize));
    SkScalar textScaleX = buffer.readScalar();
    if (textScaleX != defaultPaint.getTextScaleX())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "textScaleX:%g ", SkScalarToFloat(textScaleX));
    SkScalar textSkewX = buffer.readScalar();
    if (textSkewX != defaultPaint.getTextSkewX())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "textSkewX:%g ", SkScalarToFloat(textSkewX));
    const SkPathEffect* pathEffect = (const SkPathEffect*) buffer.readFlattenable();
    if (pathEffect != defaultPaint.getPathEffect())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "pathEffect:%p ", pathEffect);
    SkDELETE(pathEffect);
    const SkShader* shader = (const SkShader*) buffer.readFlattenable();
    if (shader != defaultPaint.getShader())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "shader:%p ", shader);
    SkDELETE(shader);
    const SkXfermode* xfermode = (const SkXfermode*) buffer.readFlattenable();
    if (xfermode != defaultPaint.getXfermode())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "xfermode:%p ", xfermode);
    SkDELETE(xfermode);
    const SkMaskFilter* maskFilter = (const SkMaskFilter*) buffer.readFlattenable();
    if (maskFilter != defaultPaint.getMaskFilter())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "maskFilter:%p ", maskFilter);
    SkDELETE(maskFilter);
    const SkColorFilter* colorFilter = (const SkColorFilter*) buffer.readFlattenable();
    if (colorFilter != defaultPaint.getColorFilter())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "colorFilter:%p ", colorFilter);
    SkDELETE(colorFilter);
    const SkRasterizer* rasterizer = (const SkRasterizer*) buffer.readFlattenable();
    if (rasterizer != defaultPaint.getRasterizer())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "rasterizer:%p ", rasterizer);
    SkDELETE(rasterizer);
    const SkDrawLooper* drawLooper = (const SkDrawLooper*) buffer.readFlattenable();
    if (drawLooper != defaultPaint.getLooper())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "drawLooper:%p ", drawLooper);
    SkDELETE(drawLooper);
    unsigned color = buffer.readU32();
    if (color != defaultPaint.getColor())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "color:0x%x ", color);
    SkScalar strokeWidth = buffer.readScalar();
    if (strokeWidth != defaultPaint.getStrokeWidth())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "strokeWidth:%g ", SkScalarToFloat(strokeWidth));
    SkScalar strokeMiter = buffer.readScalar();
    if (strokeMiter != defaultPaint.getStrokeMiter())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "strokeMiter:%g ", SkScalarToFloat(strokeMiter));
    unsigned flags = buffer.readU16();
    if (flags != defaultPaint.getFlags())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "flags:0x%x ", flags);
    int align = buffer.readU8();
    if (align != defaultPaint.getTextAlign())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "align:0x%x ", align);
    int strokeCap = buffer.readU8();
    if (strokeCap != defaultPaint.getStrokeCap())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "strokeCap:0x%x ", strokeCap);
    int strokeJoin = buffer.readU8();
    if (strokeJoin != defaultPaint.getStrokeJoin())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "align:0x%x ", strokeJoin);
    int style = buffer.readU8();
    if (style != defaultPaint.getStyle())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "style:0x%x ", style);
    int textEncoding = buffer.readU8();
    if (textEncoding != defaultPaint.getTextEncoding())
        bufferPtr += snprintf(bufferPtr, DUMP_BUFFER_SIZE - (bufferPtr - pBuffer), 
            "textEncoding:0x%x ", textEncoding);
    SkDebugf("%s\n", pBuffer);
}