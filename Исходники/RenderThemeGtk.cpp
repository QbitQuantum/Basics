bool RenderThemeGtk::paintMediaSliderTrack(const RenderObject& o, const PaintInfo& paintInfo, const IntRect& r)
{
    HTMLMediaElement* mediaElement = parentMediaElement(o);
    if (!mediaElement)
        return false;

    GraphicsContext* context = paintInfo.context;
    context->save();
    context->setStrokeStyle(NoStroke);

    float mediaDuration = mediaElement->duration();
    float totalTrackWidth = r.width();
    RenderStyle* style = &o.style();
    RefPtr<TimeRanges> timeRanges = mediaElement->buffered();
    for (unsigned index = 0; index < timeRanges->length(); ++index) {
        float start = timeRanges->start(index, IGNORE_EXCEPTION);
        float end = timeRanges->end(index, IGNORE_EXCEPTION);
        float startRatio = start / mediaDuration;
        float lengthRatio = (end - start) / mediaDuration;
        if (!lengthRatio)
            continue;

        IntRect rangeRect(r);
        rangeRect.setWidth(lengthRatio * totalTrackWidth);
        if (index)
            rangeRect.move(startRatio * totalTrackWidth, 0);
        context->fillRoundedRect(FloatRoundedRect(rangeRect, borderRadiiFromStyle(style)), style->visitedDependentColor(CSSPropertyColor), style->colorSpace());
    }

    context->restore();
    return false;
}