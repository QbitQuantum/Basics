/*
 * The following is assumed:
 *   (hadj && vadj) || (!hadj && !vadj)
 */
void ScrollView::setGtkAdjustments(GtkAdjustment* hadj, GtkAdjustment* vadj, bool resetValues)
{
    ASSERT(!hadj == !vadj);

    m_horizontalAdjustment = hadj;
    m_verticalAdjustment = vadj;

    // Reset the adjustments to a sane default
    if (m_horizontalAdjustment) {
        ScrollbarGtk* hScrollbar = reinterpret_cast<ScrollbarGtk*>(horizontalScrollbar());
        if (hScrollbar)
            hScrollbar->attachAdjustment(m_horizontalAdjustment);

        ScrollbarGtk* vScrollbar = reinterpret_cast<ScrollbarGtk*>(verticalScrollbar());
        if (vScrollbar)
            vScrollbar->attachAdjustment(m_verticalAdjustment);

        // We used to reset everything to 0 here, but when page cache
        // is enabled we reuse FrameViews that are cached. Since their
        // size is not going to change when being restored, (which is
        // what would cause the upper limit in the adjusments to be
        // set in the normal case), we make sure they are up-to-date
        // here. This is needed for the parent scrolling widget to be
        // able to report correct values.
        m_horizontalAdjustment->lower = 0;
        m_horizontalAdjustment->upper = resetValues ? 0 : frameRect().width();
        m_horizontalAdjustment->value = resetValues ? 0 : scrollOffset().width();
        gtk_adjustment_changed(m_horizontalAdjustment);
        gtk_adjustment_value_changed(m_horizontalAdjustment);

        m_verticalAdjustment->lower = 0;
        m_verticalAdjustment->upper = resetValues ? 0 : frameRect().height();
        m_verticalAdjustment->value = resetValues ? 0 : scrollOffset().height();
        gtk_adjustment_changed(m_verticalAdjustment);
        gtk_adjustment_value_changed(m_verticalAdjustment);
    } else {
        ScrollbarGtk* hScrollbar = reinterpret_cast<ScrollbarGtk*>(horizontalScrollbar());
        if (hScrollbar)
            hScrollbar->detachAdjustment();

        ScrollbarGtk* vScrollbar = reinterpret_cast<ScrollbarGtk*>(verticalScrollbar());
        if (vScrollbar)
            vScrollbar->detachAdjustment();
    }

    /* reconsider having a scrollbar */
    setHasVerticalScrollbar(false);
    setHasHorizontalScrollbar(false);
}