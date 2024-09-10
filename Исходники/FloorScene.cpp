void FloorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (isVertexMoving) {
        QPoint mousePos = event->lastScenePos().toPoint();
        float x = mousePos.x();
        float y = mousePos.y();

        //update the ellipse coordinate of the currently moving vertex
        QGraphicsEllipseItem* ellipse = currentlyMovingVertex->getEllipse();
        ellipse->setRect(x - vertexRadius, y - vertexRadius, vertexRadius * 2.0f, vertexRadius * 2.0f);

        //update the coordinate of the two edges of the currently moving vertex
        FloorVertex* neighbor1 = (FloorVertex*)currentlyMovingVertex->getNeighbor1();
        QGraphicsLineItem* edge1 = currentlyMovingVertex->getEdge1();
        edge1->setLine(ellipse->rect().center().rx(), ellipse->rect().center().ry(),
                       neighbor1->getEllipse()->rect().center().rx(), neighbor1->getEllipse()->rect().center().ry());

        FloorVertex* neighbor2 = (FloorVertex*)currentlyMovingVertex->getNeighbor2();
        QGraphicsLineItem* edge2 = currentlyMovingVertex->getEdge2();
        edge2->setLine(ellipse->rect().center().rx(), ellipse->rect().center().ry(),
                       neighbor2->getEllipse()->rect().center().rx(), neighbor2->getEllipse()->rect().center().ry());

        //update the coordinate of the currently moving vertex
        QRectF thisSize = this->sceneRect();
        Utils::adjustCoordinatesSceneTo3D(x, y, thisSize.width(), thisSize.height());
        currentlyMovingVertex->setX(x);
        currentlyMovingVertex->setY(y);

        //update the normals
        currentlyMovingVertex->computeNormal();
        neighbor1->computeNormal();
        neighbor2->computeNormal();
    }
}