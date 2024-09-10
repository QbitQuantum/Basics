void RenderSlider::layout()
{
    ASSERT(needsLayout());

    RenderBox* thumb = m_thumb ? toRenderBox(m_thumb->renderer()) : 0;

    IntSize baseSize(borderLeft() + paddingLeft() + paddingRight() + borderRight(),
        borderTop() + paddingTop() + paddingBottom() + borderBottom());

    if (thumb) {
        // Allow the theme to set the size of the thumb.
        if (thumb->style()->hasAppearance()) {
            // FIXME: This should pass the style, not the renderer, to the theme.
            theme()->adjustSliderThumbSize(thumb);
        }

        baseSize.expand(thumb->style()->width().calcMinValue(0), thumb->style()->height().calcMinValue(0));
    }

    LayoutRepainter repainter(*this, checkForRepaintDuringLayout());

    IntSize oldSize = size();

    setSize(baseSize);
    calcWidth();
    calcHeight();

    IntRect overflowRect(IntPoint(), size());

    if (thumb) {
        if (oldSize != size())
            thumb->setChildNeedsLayout(true, false);

        LayoutStateMaintainer statePusher(view(), this, size());

        IntRect oldThumbRect = thumb->frameRect();

        thumb->layoutIfNeeded();

        IntRect thumbRect;

        thumbRect.setWidth(thumb->style()->width().calcMinValue(contentWidth()));
        thumbRect.setHeight(thumb->style()->height().calcMinValue(contentHeight()));

        double fraction = sliderPosition(static_cast<HTMLInputElement*>(node()));
        IntRect contentRect = contentBoxRect();
        if (style()->appearance() == SliderVerticalPart) {
            thumbRect.setX(contentRect.x() + (contentRect.width() - thumbRect.width()) / 2);
            thumbRect.setY(contentRect.y() + static_cast<int>(nextafter((contentRect.height() - thumbRect.height()) + 1, 0) * (1 - fraction)));
        } else {
            thumbRect.setX(contentRect.x() + static_cast<int>(nextafter((contentRect.width() - thumbRect.width()) + 1, 0) * fraction));
            thumbRect.setY(contentRect.y() + (contentRect.height() - thumbRect.height()) / 2);
        }

        thumb->setFrameRect(thumbRect);

        if (thumb->checkForRepaintDuringLayout())
            thumb->repaintDuringLayoutIfMoved(oldThumbRect);

        statePusher.pop();

        IntRect thumbOverflowRect = thumb->overflowRect();
        thumbOverflowRect.move(thumb->x(), thumb->y());
        overflowRect.unite(thumbOverflowRect);
    }

    // FIXME: m_overflowWidth and m_overflowHeight should be renamed
    // m_overflowRight and m_overflowBottom.
    m_overflowLeft = overflowRect.x();
    m_overflowTop = overflowRect.y();
    m_overflowWidth = overflowRect.right();
    m_overflowHeight = overflowRect.bottom();

    repainter.repaintAfterLayout();    

    setNeedsLayout(false);
}