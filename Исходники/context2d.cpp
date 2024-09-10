void Context2D::beginPainting()
{
    if (!m_painter.isActive()) {
        m_painter.begin(&m_image);
        m_painter.setRenderHint(QPainter::Antialiasing);
        if (!m_state.clipPath.isEmpty())
            m_painter.setClipPath(m_state.clipPath);
        m_painter.setBrush(m_state.fillStyle);
        m_painter.setOpacity(m_state.globalAlpha);
        QPen pen;
        pen.setBrush(m_state.strokeStyle);
        if (pen.style() == Qt::NoPen)
            pen.setStyle(Qt::SolidLine);
        pen.setCapStyle(m_state.lineCap);
        pen.setJoinStyle(m_state.lineJoin);
        pen.setWidthF(m_state.lineWidth);
        pen.setMiterLimit(m_state.miterLimit);
        m_painter.setPen(pen);
    } else {
        if ((m_state.flags & DirtyClippingRegion) && !m_state.clipPath.isEmpty())
            m_painter.setClipPath(m_state.clipPath);
        if (m_state.flags & DirtyFillStyle)
            m_painter.setBrush(m_state.fillStyle);
        if (m_state.flags & DirtyGlobalAlpha)
            m_painter.setOpacity(m_state.globalAlpha);
        if (m_state.flags & DirtyGlobalCompositeOperation)
            m_painter.setCompositionMode(m_state.globalCompositeOperation);
        if (m_state.flags & MDirtyPen) {
            QPen pen = m_painter.pen();
            if (m_state.flags & DirtyStrokeStyle)
                pen.setBrush(m_state.strokeStyle);
            if (m_state.flags & DirtyLineWidth)
                pen.setWidthF(m_state.lineWidth);
            if (m_state.flags & DirtyLineCap)
                pen.setCapStyle(m_state.lineCap);
            if (m_state.flags & DirtyLineJoin)
                pen.setJoinStyle(m_state.lineJoin);
            if (m_state.flags & DirtyMiterLimit)
                pen.setMiterLimit(m_state.miterLimit);
            m_painter.setPen(pen);
        }
        m_state.flags = 0;
    }
}