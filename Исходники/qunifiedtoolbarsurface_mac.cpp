void QUnifiedToolbarSurface::renderToolbar(QWidget *widget, bool forceFlush)
{
    QWidget *toolbar = widget->d_func()->toolbar_ancestor;

    updateToolbarOffset(toolbar);
    QRect beginPaintRect(toolbar->d_func()->toolbar_offset.x(), toolbar->d_func()->toolbar_offset.y(), toolbar->geometry().width(), toolbar->geometry().height());
    QRegion beginPaintRegion(beginPaintRect);

    beginPaint(beginPaintRegion);
    toolbar->render(paintDevice(), toolbar->d_func()->toolbar_offset, QRegion(toolbar->geometry()), QWidget::DrawChildren);
    toolbar->d_func()->flushRequested = true;

    if (forceFlush)
        flush(toolbar);
}