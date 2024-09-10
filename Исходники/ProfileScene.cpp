void ProfileScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (!isProfileSelected) {
        return;
    }

    if (isVertexMoving) {
        QPoint mousePos = event->lastScenePos().toPoint();
        float x = mousePos.x();
        float y = mousePos.y();

        // enforce the monotonicity constraints
        Vertex* neighbor1 = currentlyMovingVertex->getNeighbor1();
        if (neighbor1 != 0){
            if (neighbor1->getEllipse()->rect().center().ry() - 1 <= y) {
                return;
            }
        }

        // enforce the monotonicity constraints
        Vertex* neighbor2 = currentlyMovingVertex->getNeighbor2();
        if (neighbor2 != 0){
            if (neighbor2->getEllipse()->rect().center().ry() + 1 >= y) {
                return;
            }
        }

        //update the ellipse coordinate of the currently moving vertex
        QGraphicsEllipseItem* ellipse = currentlyMovingVertex->getEllipse();
        ellipse->setRect(x - vertexRadius, y - vertexRadius, vertexRadius * 2.0f, vertexRadius * 2.0f);

        //update the coordinate of the two edges of the currently moving vertex
        if (neighbor1 != 0){
            Edge* edge1 = currentlyMovingVertex->getEdge1();
            edge1->getLineItem()->setLine(ellipse->rect().center().rx(), ellipse->rect().center().ry(),
                       neighbor1->getEllipse()->rect().center().rx(), neighbor1->getEllipse()->rect().center().ry());
        }

        if (neighbor2 != 0) {
            Edge* edge2 = currentlyMovingVertex->getEdge2();
            edge2->getLineItem()->setLine(ellipse->rect().center().rx(), ellipse->rect().center().ry(),
                       neighbor2->getEllipse()->rect().center().rx(), neighbor2->getEllipse()->rect().center().ry());
        }

        //update the coordinate of the currently moving vertex
        QRectF thisSize = this->sceneRect();
        Utils::adjustCoordinatesSceneTo3D(x, y, thisSize.width(), thisSize.height());
        currentlyMovingVertex->setX(x);
        currentlyMovingVertex->setY(y);
    }
}