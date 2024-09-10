void ScrollView::adjustOverlappingScrollbarCount(int overlapDelta)
{
    int oldCount = m_data->m_scrollbarsAvoidingResizer;
    m_data->m_scrollbarsAvoidingResizer += overlapDelta;
    if (parent() && parent()->isFrameView())
        static_cast<FrameView*>(parent())->adjustOverlappingScrollbarCount(overlapDelta);
    else if (!m_data->m_scrollbarsSuppressed) {
        // If we went from n to 0 or from 0 to n and we're the outermost view,
        // we need to invalidate the windowResizerRect(), since it will now need to paint
        // differently.
        if (oldCount > 0 && m_data->m_scrollbarsAvoidingResizer == 0 ||
            oldCount == 0 && m_data->m_scrollbarsAvoidingResizer > 0)
            invalidateRect(windowResizerRect());
    }
}