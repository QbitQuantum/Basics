void SkTextBox::draw(SkCanvas* canvas, const char text[], size_t len, const SkPaint& paint)
{
    SkASSERT(canvas && &paint && (text || len == 0));

    SkScalar marginWidth = fBox.width();

    if (marginWidth <= 0 || len == 0)
        return;

    const char* textStop = text + len;

    SkScalar                x, y, scaledSpacing, height, fontHeight;
    SkPaint::FontMetrics    metrics;

    switch (paint.getTextAlign()) {
    case SkPaint::kLeft_Align:
        x = 0;
        break;
    case SkPaint::kCenter_Align:
        x = SkScalarHalf(marginWidth);
        break;
    default:
        x = marginWidth;
        break;
    }
    x += fBox.fLeft;

    fontHeight = paint.getFontMetrics(&metrics);
    scaledSpacing = SkScalarMul(fontHeight, fSpacingMul) + fSpacingAdd;
    height = fBox.height();

    //  compute Y position for first line
    {
        SkScalar textHeight = fontHeight;

        if (fMode == kLineBreak_Mode && fSpacingAlign != kStart_SpacingAlign)
        {
            int count = SkTextLineBreaker::CountLines(text, textStop - text, paint, marginWidth);
            SkASSERT(count > 0);
            textHeight += scaledSpacing * (count - 1);
        }

        switch (fSpacingAlign) {
        case kStart_SpacingAlign:
            y = 0;
            break;
        case kCenter_SpacingAlign:
            y = SkScalarHalf(height - textHeight);
            break;
        default:
            SkASSERT(fSpacingAlign == kEnd_SpacingAlign);
            y = height - textHeight;
            break;
        }
        y += fBox.fTop - metrics.fAscent;
    }

    for (;;)
    {
        len = linebreak(text, textStop, paint, marginWidth);
        if (y + metrics.fDescent + metrics.fLeading > 0)
            canvas->drawText(text, len, x, y, paint);
        text += len;
        if (text >= textStop)
            break;
        y += scaledSpacing;
        if (y + metrics.fAscent >= height)
            break;
    } 
}