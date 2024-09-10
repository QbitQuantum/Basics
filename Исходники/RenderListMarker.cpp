void RenderListMarker::paint(PaintInfo& paintInfo, int tx, int ty)
{
    if (paintInfo.phase != PaintPhaseForeground)
        return;
    
    if (style()->visibility() != VISIBLE)
        return;

    IntRect marker = getRelativeMarkerRect();
    marker.move(tx, ty);

    IntRect box(tx + m_x, ty + m_y, m_width, m_height);

    if (box.y() > paintInfo.rect.bottom() || box.y() + box.height() < paintInfo.rect.y())
        return;

    if (hasBoxDecorations()) 
        paintBoxDecorations(paintInfo, box.x(), box.y());

    GraphicsContext* context = paintInfo.context;
    context->setFont(style()->font());

    if (isImage()) {
#if PLATFORM(MAC)
        if (style()->highlight() != nullAtom && !paintInfo.context->paintingDisabled())
            paintCustomHighlight(tx, ty, style()->highlight(), true);
#endif
        context->drawImage(m_image->image(), marker.location());
        if (selectionState() != SelectionNone)
            context->fillRect(selectionRect(), selectionBackgroundColor());
        return;
    }

#if PLATFORM(MAC)
    // FIXME: paint gap between marker and list item proper
    if (style()->highlight() != nullAtom && !paintInfo.context->paintingDisabled())
        paintCustomHighlight(tx, ty, style()->highlight(), true);
#endif

    if (selectionState() != SelectionNone)
        context->fillRect(selectionRect(), selectionBackgroundColor());

    const Color color(style()->color());
    context->setStrokeColor(color);
    context->setStrokeStyle(SolidStroke);
    context->setStrokeThickness(1.0f);
    context->setFillColor(color);

    switch (style()->listStyleType()) {
        case DISC:
            context->drawEllipse(marker);
            return;
        case CIRCLE:
            context->setFillColor(Color::transparent);
            context->drawEllipse(marker);
            return;
        case SQUARE:
            context->drawRect(marker);
            return;
        case LNONE:
            return;
        case ARMENIAN:
        case CJK_IDEOGRAPHIC:
        case DECIMAL_LEADING_ZERO:
        case GEORGIAN:
        case HEBREW:
        case HIRAGANA:
        case HIRAGANA_IROHA:
        case KATAKANA:
        case KATAKANA_IROHA:
        case LDECIMAL:
        case LOWER_ALPHA:
        case LOWER_GREEK:
        case LOWER_LATIN:
        case LOWER_ROMAN:
        case UPPER_ALPHA:
        case UPPER_LATIN:
        case UPPER_ROMAN:
            break;
    }
    if (m_text.isEmpty())
        return;

    TextRun textRun(m_text);

    // Text is not arbitrary. We can judge whether it's RTL from the first character,
    // and we only need to handle the direction RightToLeft for now.
    bool textNeedsReversing = direction(m_text[0]) == RightToLeft;
    Vector<UChar> reversedText;
    if (textNeedsReversing) {
        int length = m_text.length();
        reversedText.resize(length);
        for (int i = 0; i < length; ++i)
            reversedText[length - i - 1] = m_text[i];
        textRun = TextRun(reversedText.data(), length);
    }

    const Font& font = style()->font();
    if (style()->direction() == LTR) {
        int width = font.width(textRun);
        context->drawText(textRun, marker.location());
        const UChar periodSpace[2] = { '.', ' ' };
        context->drawText(TextRun(periodSpace, 2), marker.location() + IntSize(width, 0));
    } else {
        const UChar spacePeriod[2] = { ' ', '.' };
        TextRun spacePeriodRun(spacePeriod, 2);
        int width = font.width(spacePeriodRun);
        context->drawText(spacePeriodRun, marker.location());
        context->drawText(textRun, marker.location() + IntSize(width, 0));
    }
}