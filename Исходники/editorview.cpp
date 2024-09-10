void EditorView::drawForeground(QPainter *painter, const QRectF& rect)
{
    if(enableoutline_ && showoutline_ && outlinesize_>1) {
        const QRectF outline(prevpoint_-QPointF(outlinesize_,outlinesize_),
                             QSizeF(dia_, dia_));
        if(rect.intersects(outline)) {
            //painter->setClipRect(0,0,board_->width(),board_->height()); // default
            //painter->setClipRect(outline.adjusted(-7, -7, 7, 7)); // smaller clipping
            //painter->setRenderHint(QPainter::Antialiasing, true); // default
            QPen pen(background_);
            painter->setPen(pen);
            painter->drawEllipse(outline);
            pen.setColor(foreground_);
            pen.setStyle(Qt::DashLine);
            painter->setPen(pen);
            painter->drawEllipse(outline);
        }
    }
}