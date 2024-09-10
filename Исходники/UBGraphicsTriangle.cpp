void UBGraphicsTriangle::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
 
    if (!mResizing1 && !mResizing2 && !mRotating)
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
    else
    {
        QPoint currPos = sceneTransform().inverted().map(event->screenPos());

        if (mResizing1)
        {
            if (mOrientation == TopLeft || mOrientation == BottomLeft)
            {
                int deltaX = currPos.x() - lastPos.x();
                if (lastRect.width() + deltaX < sMinWidth)
                    deltaX = sMinWidth - lastRect.width();

                setRect(QRectF(lastRect.left(), lastRect.top(),
                    lastRect.width() + deltaX, lastRect.height()), mOrientation);
            }
            else
            {
                int deltaX = lastPos.x() - currPos.x();
                if (lastRect.width() + deltaX < sMinWidth)
                    deltaX = sMinWidth - lastRect.width();

                setRect(QRectF(lastRect.left() - deltaX, lastRect.top(),
                    lastRect.width() + deltaX, lastRect.height()), mOrientation);
            }
        }

        //-----------------------------------------------//

        if (mResizing2)
        {
            if (mOrientation == BottomRight || mOrientation == BottomLeft)
            {
                int deltaY = lastPos.y() - currPos.y();
                if (lastRect.height() + deltaY < sMinHeight)
                    deltaY = sMinHeight - lastRect.height();

                setRect(QRectF(lastRect.left(), lastRect.top() - deltaY,
                        lastRect.width(), lastRect.height() + deltaY), mOrientation);
            }
            else
            {
                int deltaY = currPos.y() - lastPos.y();
                if (lastRect.height() + deltaY < sMinHeight)
                    deltaY = sMinHeight - lastRect.height();

                setRect(QRectF(lastRect.left(), lastRect.top(),
                        lastRect.width(), lastRect.height() + deltaY), mOrientation);
            }

        }

        //-----------------------------------------------//

        if (mRotating)
        {
            QLineF currentLine(rotationCenter(), event->pos());
            QLineF lastLine(rotationCenter(), event->lastPos());
            rotateAroundCenter(currentLine.angleTo(lastLine));
        }

        //-----------------------------------------------//

        event->accept();
    }
}