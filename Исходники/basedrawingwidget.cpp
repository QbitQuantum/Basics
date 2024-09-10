void BaseDrawingWidget::handleDrawingState(DrawingState state, QPointF lastPoint)
{
    // handle drawing start/update/end events for the current drawing mode

    QPainter::CompositionMode prevCompMode;

    if(state == DRAWINGSTATE_START) {
        // start a new series of paint operations on the picture
        picturePainter.begin(&picture);
        // set the drawing style for the painter
        picturePainter.setPen(drawingPen);
        picturePainter.setBrush(drawingBrush);
    }

    switch(drawingMode) {
        case DRAWINGMODE_FREEHAND:
            if(state == DRAWINGSTATE_START) {
                QGraphicsLineItem * newLine = new QGraphicsLineItem(QLineF(lastPoint, lastPoint), 0, getDrawingData());
                currentItem = newLine;
                newLine->setPen(drawingPen);
            }

            else if(state == DRAWINGSTATE_UPDATE) {
                QGraphicsLineItem * newLine = new QGraphicsLineItem(currentItem, getDrawingData());
                newLine->setLine(QLineF(mousePrevPoint, lastPoint));
                newLine->setPen(drawingPen);
                picturePainter.drawLine(mousePrevPoint, lastPoint);
            }

            else {
                QGraphicsLineItem * newLine = new QGraphicsLineItem(currentItem, getDrawingData());
                newLine->setLine(QLineF(mousePrevPoint, lastPoint));
                newLine->setPen(drawingPen);
                // remove the temporary QGraphicsItem
                getDrawingData()->removeItem(currentItem);
                picturePainter.drawLine(mousePrevPoint, lastPoint);
             }

            break;

        case DRAWINGMODE_RECTANGLE:
            if(state == DRAWINGSTATE_START) {
                // create a temporary QGraphicsItem
                // will be committed to the drawing when the mouse is released
                QGraphicsRectItem * newRect = new QGraphicsRectItem(lastPoint.x(), lastPoint.y(),0,0);
                currentItem = (QGraphicsItem *) newRect;
                newRect->setPen(drawingPen);
                newRect->setBrush(drawingBrush);
                drawingData->addItem(currentItem);
            }

            else if(state == DRAWINGSTATE_UPDATE)
                // update the temporary QGraphicsItem
                ((QGraphicsRectItem*)currentItem)->setRect(QRectF(mouseDownPoint,lastPoint).normalized());

            else {
                // remove the temporary QGraphicsItem
                getDrawingData()->removeItem(currentItem);
                // commit the drawing to the stage pixmap
                picturePainter.drawRect(QRectF(mouseDownPoint,lastPoint).normalized());
            }
            break;

        case DRAWINGMODE_STRAIGHTLINE:
            if(state == DRAWINGSTATE_START) {
                // create a temporary QGraphicsItem
                // will be committed to the drawing when the mouse is released
                QGraphicsLineItem * newLine = new QGraphicsLineItem(QLineF(lastPoint, lastPoint));
                currentItem = (QGraphicsItem*) newLine;
                newLine->setPen(drawingPen);
                getDrawingData()->addItem(newLine);
            }

            else if(state == DRAWINGSTATE_UPDATE) {
                // update the temporary QGraphicsItem
                ((QGraphicsLineItem*)currentItem)->setLine(QLineF(mouseDownPoint, lastPoint));
            }

            else {
                // remove the temporary QGraphicsItem
                getDrawingData()->removeItem(currentItem);
                // commit the drawing to the stage pixmap
                picturePainter.drawLine(QLineF(mouseDownPoint, lastPoint));
            }
            break;

        case DRAWINGMODE_ELLIPSE:
            if(state == DRAWINGSTATE_START) {
                // create a temporary QGraphicsItem
                // will be committed to the drawing when the mouse is released
                QGraphicsEllipseItem * newRect = new QGraphicsEllipseItem(lastPoint.x(), lastPoint.y(),0,0);
                currentItem = (QGraphicsItem *) newRect;
                newRect->setPen(drawingPen);
                newRect->setBrush(drawingBrush);
                drawingData->addItem(currentItem);
            }

            else if(state == DRAWINGSTATE_UPDATE)
                // update the temporary QGraphicsItem
                ((QGraphicsRectItem*)currentItem)->setRect(QRectF(mouseDownPoint,lastPoint).normalized());

            else {
                // remove the temporary QGraphicsItem
                getDrawingData()->removeItem(currentItem);
                // commit the drawing to the stage pixmap
                picturePainter.drawEllipse(QRectF(mouseDownPoint,lastPoint).normalized());
            }
            break;

        case DRAWINGMODE_ERASER:
            if(state == DRAWINGSTATE_START) {
                QGraphicsRectItem * newEraseRect = new QGraphicsRectItem(QRectF(lastPoint, QSizeF(drawingPen.width()+5, drawingPen.width()+5)), 0, getDrawingData());
                currentItem = newEraseRect;
                newEraseRect->setPen(QPen(Qt::transparent));
                newEraseRect->setBrush(QBrush(Qt::white));
            }

            else if(state == DRAWINGSTATE_UPDATE) {
                QGraphicsRectItem * newEraseRect = new QGraphicsRectItem(currentItem, getDrawingData());
                newEraseRect->setRect(QRectF(lastPoint, QSizeF(drawingPen.width()+5, drawingPen.width()+5)));
                newEraseRect->setPen(QPen(Qt::transparent));
                newEraseRect->setBrush(QBrush(Qt::white));
            }

            else {
                QGraphicsRectItem * newEraseRect = new QGraphicsRectItem(currentItem, getDrawingData());
                newEraseRect->setRect(QRectF(lastPoint, QSizeF(drawingPen.width()+5, drawingPen.width()+5)));
                newEraseRect->setPen(QPen(Qt::transparent));
                newEraseRect->setBrush(QBrush(Qt::white));
                // remove the temporary QGraphicsItem
                getDrawingData()->removeItem(currentItem);
             }
            // common in all cases for the eraser:
            // we have to set a specific composition mode for the eraser
            // back up the current value
            prevCompMode = picturePainter.compositionMode();
            picturePainter.setCompositionMode(QPainter::CompositionMode_SourceIn);
            // fill the region to be erased with transparent color
            picturePainter.fillRect(QRectF(lastPoint, QSizeF(drawingPen.width()+5, drawingPen.width()+5)),Qt::transparent);
            // restore the old composition mode
            picturePainter.setCompositionMode(prevCompMode);
            break;

        case DRAWINGMODE_ARROW:
            // TODO not yet implemented - implement this as well
        break;

    }

    if(state == DRAWINGSTATE_END) {
        // finalize the painting on the QPicture
        picturePainter.end();
        commitDrawing(picture);
    }
}