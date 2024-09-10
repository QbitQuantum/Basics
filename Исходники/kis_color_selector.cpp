void KisColorSelector::drawLightStrip(QPainter& painter, const QRect& rect)
{
    bool     isVertical = true;
    qreal    penSize    = qreal(qMin(QWidget::width(), QWidget::height())) / 200.0;
    KisColor color(m_selectedColor);
    
    painter.resetTransform();
    
    if (getNumLightPieces() > 1) {
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QBrush(Qt::red), penSize));
        
        QTransform matrix;
        matrix.translate(rect.x(), rect.y());
        matrix.scale(rect.width(), rect.height());
        
        for(int i=0; i<getNumLightPieces(); ++i) {
            float  t1    = float(i)   / float(getNumLightPieces());
            float  t2    = float(i+1) / float(getNumLightPieces());
            float  light = 1.0f - (float(i) / float(getNumLightPieces()-1));
            float  diff  = t2 - t1;// + 0.001;
            QRectF r     = isVertical ? QRectF(0.0, t1, 1.0, diff) : QRect(t1, 0.0, diff, 1.0);
            
            color.setX(getLight(light, color.getH(), m_relativeLight));
            
            r = matrix.mapRect(r);
            painter.fillRect(r, color.getQColor());
            
            if (i == m_selectedLightPiece)
                painter.drawRect(r);
        }
    }
    else {
        int size = isVertical ? rect.height() : rect.width();
        painter.setRenderHint(QPainter::Antialiasing, false);
        
        if (isVertical) {
            for(int i=0; i<size; ++i) {
                int   y     = rect.y() + i;
                float light = 1.0f - (float(i) / float(size-1));
                color.setX(getLight(light, color.getH(), m_relativeLight));
                painter.setPen(color.getQColor());
                painter.drawLine(rect.left(), y, rect.right(), y);
            }
        }
        else {
            for(int i=0; i<size; ++i) {
                int   x     = rect.x() + i;
                float light = 1.0f - (float(i) / float(size-1));
                color.setX(getLight(light, color.getH(), m_relativeLight));
                painter.setPen(color.getQColor());
                painter.drawLine(x, rect.top(), x, rect.bottom());
            }
        }
        
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(QBrush(Qt::red), penSize));
        float t = 1.0f - m_light;
        
        if (isVertical) {
            int y = rect.y() + int(size * t);
            painter.drawLine(rect.left(), y, rect.right(), y);
        }
        else {
            int x = rect.x() + int(size * t);
            painter.drawLine(x, rect.top(), x, rect.bottom());
        }
    }
}