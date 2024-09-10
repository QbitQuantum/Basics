PassRefPtr<JSONObject> LoggingCanvas::objectForSkPaint(const SkPaint& paint)
{
    RefPtr<JSONObject> paintItem = JSONObject::create();
    paintItem->setNumber("textSize", paint.getTextSize());
    paintItem->setNumber("textScaleX", paint.getTextScaleX());
    paintItem->setNumber("textSkewX", paint.getTextSkewX());
    if (SkShader* shader = paint.getShader())
        paintItem->setObject("shader", objectForSkShader(*shader));
    paintItem->setString("color", stringForSkColor(paint.getColor()));
    paintItem->setNumber("strokeWidth", paint.getStrokeWidth());
    paintItem->setNumber("strokeMiter", paint.getStrokeMiter());
    paintItem->setString("flags", stringForSkPaintFlags(paint));
    paintItem->setString("filterLevel", filterQualityName(paint.getFilterQuality()));
    paintItem->setString("textAlign", textAlignName(paint.getTextAlign()));
    paintItem->setString("strokeCap", strokeCapName(paint.getStrokeCap()));
    paintItem->setString("strokeJoin", strokeJoinName(paint.getStrokeJoin()));
    paintItem->setString("styleName", styleName(paint.getStyle()));
    paintItem->setString("textEncoding", textEncodingName(paint.getTextEncoding()));
    paintItem->setString("hinting", hintingName(paint.getHinting()));
    return paintItem.release();
}