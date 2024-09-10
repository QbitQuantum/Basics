void QWebFramePrivate::renderRelativeCoords(GraphicsContext* context, QWebFrame::RenderLayer layer, const QRegion& clip)
{
    if (!frame->view() || !frame->contentRenderer())
        return;

    QVector<QRect> vector = clip.rects();
    if (vector.isEmpty())
        return;

    QPainter* painter = context->platformContext();

    WebCore::FrameView* view = frame->view();
    view->layoutIfNeededRecursive();

    for (int i = 0; i < vector.size(); ++i) {
        const QRect& clipRect = vector.at(i);

        QRect intersectedRect = clipRect.intersected(view->frameRect());

        painter->save();
        painter->setClipRect(clipRect, Qt::IntersectClip);

        int x = view->x();
        int y = view->y();

        if (layer & QWebFrame::ContentsLayer) {
            context->save();

            int scrollX = view->scrollX();
            int scrollY = view->scrollY();

            QRect rect = intersectedRect;
            context->translate(x, y);
            rect.translate(-x, -y);
            context->translate(-scrollX, -scrollY);
            rect.translate(scrollX, scrollY);
            context->clip(view->visibleContentRect());

            view->paintContents(context, rect);

            context->restore();
        }

        if (layer & QWebFrame::ScrollBarLayer
            && !view->scrollbarsSuppressed()
            && (view->horizontalScrollbar() || view->verticalScrollbar())) {
            context->save();

            QRect rect = intersectedRect;
            context->translate(x, y);
            rect.translate(-x, -y);

            view->paintScrollbars(context, rect);

            context->restore();
        }

#if ENABLE(PAN_SCROLLING)
        if (layer & QWebFrame::PanIconLayer)
            view->paintPanScrollIcon(context);
#endif

        painter->restore();
    }
}