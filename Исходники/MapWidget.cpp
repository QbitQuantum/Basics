void MapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRectF rectf(0, 0, width(), height());
    QPointF vpTopLeft = mViewportPos + mDragOffset;

    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    painter.fillRect(rectf, Qt::black);

    painter.save();
    painter.translate(vpTopLeft);
    painter.scale(mScale, mScale);

    if (mTileSize.isValid()) {
        int i, j, tile_indx;
        QPoint visAreaBeg = getCellUnderMouse(QPoint(0,0)); // TODO: this is just viewport coords / width-height!
        clipCellCoord(visAreaBeg);
        QPoint visAreaEnd = getCellUnderMouse(visAreaBeg + QPoint(this->width(), this->height()));
        clipCellCoord(visAreaEnd);

        for(i = visAreaBeg.x(); i <= visAreaEnd.x(); ++i) {
            for(j = visAreaBeg.y(); j <= visAreaEnd.y(); ++j) {
                tile_indx = mCells.at(i + j * mCols);
                if (tile_indx >= 0)
                    painter.drawImage(i * mTileSize.width(), j * mTileSize.height(), mTiles[tile_indx].im);
            }
        }

        // highlight cursor
        switch (mEditMode) {
        case NORMAL:
            if (mSelectionBegin && !mSelectionEnd) {
                QRect frame = getSelectedArea(*mSelectionBegin, mCellUnderMouse);
                painter.fillRect(
                    frame.left() * mTileSize.width(),
                    frame.top() * mTileSize.height(),
                    frame.width() * mTileSize.width(),
                    frame.height() * mTileSize.height(),
                    QColor(127, 127, 255, 50));
            } else if (isValidCell(mCellUnderMouse)) {
                int x = mCellUnderMouse.x() * mTileSize.width();
                int y = mCellUnderMouse.y() * mTileSize.height();
                painter.fillRect(x, y, mTileSize.width(), mTileSize.height(), QColor(127, 127, 255, 50));
            }
            break;

        case GRAB:
        case DUPLICATE:
            {
                QRect selArea = getSelectedArea(*mSelectionBegin, *mSelectionEnd);
                QRect frame(
                    mCellUnderMouse.x() - mGrabOrigin.x(),
                    mCellUnderMouse.y() - mGrabOrigin.y(),
                    selArea.width(),
                    selArea.height());
                painter.fillRect(
                    frame.left() * mTileSize.width(),
                    frame.top() * mTileSize.height(),
                    frame.width() * mTileSize.width(),
                    frame.height() * mTileSize.height(),
                    QColor(127, 127, 255, 50));
            }
            break;
        }

        // highlight selected
        if (mSelectionBegin && mSelectionEnd) {
            QRect frame = getSelectedArea(*mSelectionBegin, *mSelectionEnd);
            painter.fillRect(
                frame.left() * mTileSize.width(),
                frame.top() * mTileSize.height(),
                frame.width() * mTileSize.width(),
                frame.height() * mTileSize.height(),
                QColor(0, 255, 0, 75));
        }

        painter.setPen(Qt::red);
        painter.drawRect(-1, -1, mCols * mTileSize.width(), mRows * mTileSize.height());
    } else {
        painter.setPen(Qt::red);
        painter.drawLine(-10, 0, 10, 0);
        painter.drawLine(0, -10, 0, 10);
    }
    painter.restore();

    painter.setPen(Qt::green);
    painter.drawRect(rectf);
}