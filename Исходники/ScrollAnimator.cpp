void ScrollAnimator::handleWheelEvent(PlatformWheelEvent& e)
{
    Scrollbar* horizontalScrollbar = m_scrollableArea->horizontalScrollbar();
    Scrollbar* verticalScrollbar = m_scrollableArea->verticalScrollbar();

    // Accept the event if we have a scrollbar in that direction and can still
    // scroll any further.
    float deltaX = horizontalScrollbar ? e.deltaX() : 0;
    float deltaY = verticalScrollbar ? e.deltaY() : 0;

    IntSize maxForwardScrollDelta = m_scrollableArea->maximumScrollPosition() - m_scrollableArea->scrollPosition();
    IntSize maxBackwardScrollDelta = m_scrollableArea->scrollPosition() - m_scrollableArea->minimumScrollPosition();
    if ((deltaX < 0 && maxForwardScrollDelta.width() > 0)
        || (deltaX > 0 && maxBackwardScrollDelta.width() > 0)
        || (deltaY < 0 && maxForwardScrollDelta.height() > 0)
        || (deltaY > 0 && maxBackwardScrollDelta.height() > 0)) {
        e.accept();
        if (e.granularity() == ScrollByPageWheelEvent) {
            ASSERT(!e.deltaX());
            bool negative = deltaY < 0;
            deltaY = max(max(static_cast<float>(m_scrollableArea->visibleHeight()) * Scrollbar::minFractionToStepWhenPaging(), static_cast<float>(m_scrollableArea->visibleHeight() - Scrollbar::maxOverlapBetweenPages())), 1.0f);
            if (negative)
                deltaY = -deltaY;
        }

        if (deltaY)
            scroll(VerticalScrollbar, ScrollByPixel, verticalScrollbar->pixelStep(), -deltaY);
        if (deltaX)
            scroll(HorizontalScrollbar, ScrollByPixel, horizontalScrollbar->pixelStep(), -deltaX);
    }
}