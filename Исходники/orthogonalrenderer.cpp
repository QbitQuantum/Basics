void OrthogonalRenderer::drawMapObject(QPainter *painter,
                                       const MapObject *object,
                                       const QColor &color) const
{
    painter->save();

    const QRectF bounds = object->bounds();
    QRectF rect(tileToPixelCoords(bounds.topLeft()),
                tileToPixelCoords(bounds.bottomRight()));

    painter->translate(rect.topLeft());
    rect.moveTopLeft(QPointF(0, 0));

  if(object->getPoly()!=NULL)
	{
		Poly* pPoly=object->getPoly();
		unsigned int size=pPoly->getPointCount();
		if(size>1)
		{
			QPainterPath path;
			path.moveTo(pPoly->getPointByIndex(0));
			for(unsigned int i=1;i<size;++i)
			{
				path.lineTo(pPoly->getPointByIndex(i));

			}
			painter->drawPath(path);
		}

	}else  if (object->tile())
    {
        const QPixmap &img = object->tile()->image();
        const QPoint paintOrigin(0, -img.height());
        painter->drawPixmap(paintOrigin, img);

        QPen pen(Qt::SolidLine);
        painter->setPen(pen);
        painter->drawRect(QRect(paintOrigin, img.size()));
        pen.setStyle(Qt::DotLine);
        pen.setColor(color);
        painter->setPen(pen);
        painter->drawRect(QRect(paintOrigin, img.size()));
    }
    else
    {
        if (rect.isNull())
            rect = QRectF(QPointF(-10, -10), QSizeF(20, 20));

        const QFontMetrics fm = painter->fontMetrics();
        QString name = fm.elidedText(object->name(), Qt::ElideRight,
                                     rect.width() + 2);

        painter->setRenderHint(QPainter::Antialiasing);

        // Draw the shadow
        QPen pen(Qt::black, 2);
        painter->setPen(pen);
        painter->drawRect(rect.translated(QPointF(1, 1)));
        if (!name.isEmpty())
            painter->drawText(QPoint(1, -5 + 1), name);

        QColor brushColor = color;
        brushColor.setAlpha(50);
        QBrush brush(brushColor);

        pen.setColor(color);
        painter->setPen(pen);
        painter->setBrush(brush);
        painter->drawRect(rect);
        if (!name.isEmpty())
            painter->drawText(QPoint(0, -5), name);
    }

    painter->restore();
}