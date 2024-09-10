void EditorArea::paintMeshEls(QPainter& painter)
{
    QVector<int> nodesIds = workspace->getNodesIds();
    QVector<int> edgesIds = workspace->getEdgesIds();
    bool showMesh = workspace->getShowMeshStatus();
    int selectedTool = workspace->getSelectedTool();
    bool firstTime = true;
    bool firstTimeNode = true;

    qreal radius = size2screen(9);
    float fontSize = size2screen(12);

    qreal width = radius * 2;
    qreal height = radius * 2;

    painter.setFont(QFont("Arial", fontSize));
    for (int i = 0; i < nodesIds.size(); i++) {
        QString nodeMTypeString = workspace->getNodeMType(nodesIds[i]);
        QString elementType;
        elementType.clear();
        if (!nodeMTypeString.isEmpty()) {
            if (nodeMTypeString == "Anastomosis") {
                elementType = "a";
            } else if (nodeMTypeString == "Windkessel") {
                elementType = "w";
            } else if (nodeMTypeString == "Resistance") {
                elementType = "r";
            } else if (nodeMTypeString == "WavePropagation")
                elementType = "p";
        }

        if (!nodeMTypeString.isNull()) {
            QPointF nodePos = graph2screen(workspace->getNodePosition(nodesIds[i]));
            int nodeMElementId = workspace->getNodeMElementId(nodesIds[i]);

            meshElsPos.insert(nodeMElementId, nodePos);
            meshElsType.insert(nodeMElementId, elementType);
            meshId2GraphId.insert(nodeMElementId, QPoint(1, nodesIds[i]));

            QPainterPath path;
            QPainterPath text;

            path.arcTo(QRectF(-radius*1.2, -radius*1.2, width*1.2, height*1.2), 0, 360);
            text.addText(-radius / 2.0, radius / 2.0, QFont("Arial", fontSize), elementType);
            path.translate(nodePos);
            text.translate(nodePos);

            if (showMesh) {
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::gray);
                painter.drawPath(path);
                painter.setPen(Qt::yellow);
                painter.setBrush(Qt::yellow);
                painter.drawPath(text);
            } else {
                qreal dotR = size2screen(2);
                QPainterPath dotPath;
                painter.setPen(Qt::gray);
                painter.setBrush(Qt::gray);
                dotPath.arcTo(QRectF(-dotR, -dotR, dotR * 2, dotR * 2), 0, 360);
                dotPath.translate(nodePos);
                painter.drawPath(dotPath);
            }

            QPainterPath mousePath;
            mousePath.arcTo(QRectF(-1, -1, 1, 1), 0, 360);
            mousePath.translate(mouseCurrentPos);

            if (path.intersects(mousePath) && selectedTool == 7) {
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::gray);
                painter.drawPath(path);
                painter.setPen(Qt::yellow);
                painter.setBrush(Qt::yellow);
                painter.drawPath(text);

                if (firstTimeNode) {
                    firstTimeNode = false;
                    hitMeshEls.clear();
                }

                QPoint temp(1, nodeMElementId);
                hitMeshEls.append(temp);
            }
        }
    }

    for (int j = 0; j < edgesIds.size(); j++) {
        QVector<float> sCoord = workspace->getEdgeMs(edgesIds[j]);
        QVector<QString> edgeMTypes = workspace->getEdgeMTypes(edgesIds[j]);
        QVector<int> edgeMElementsId = workspace->getEdgeMElementsId(edgesIds[j]);

        for (int h = 0; h < sCoord.size(); h++) {
            float s;
            if (h == sCoord.size() - 1.0) {
                s = (1.0 - sCoord[h]) / 2.0 + sCoord[h];
            } else {
                s = (sCoord[h + 1] - sCoord[h]) / 2.0 + sCoord[h];
            }

            int t = 0;
            while (sOnBezier.value(edgesIds[j]).at(t) < s) {
                t = t + 1;
            }
            float deltaS = s - float(t - 1) / edgeDiscretization;

            float m = float(t - 1) / edgeDiscretization + deltaS;

            QString elementType;
            elementType.clear();
            if (!edgeMTypes[h].isEmpty()) {
                if (edgeMTypes[h] == "Resistance") {
                    elementType = "r";
                } else if (edgeMTypes[h] == "WavePropagation") {
                    elementType = "p";
                } else if (edgeMTypes[h] == "Anastomosis") {
                    elementType = "a";
                } else if (edgeMTypes[h] == "Windkessel") {
                    elementType = "w";
                }
            }

            QPoint nodesOfEdge = workspace->getNodesOfEdge(edgesIds[j]);
            QPointF screenXYFirst = graph2screen(workspace->getNodePosition(nodesOfEdge.x()));
            QPointF screenXYSecond = graph2screen(workspace->getNodePosition(nodesOfEdge.y()));
            QPointF screenMidPoint = graph2screen(workspace->getThirdPointPos(edgesIds[j]));

            QPointF pointPos = (1 - m) * (1 - m) * screenXYFirst + 2 * (1 - m) * m * screenMidPoint + m * m * screenXYSecond;

            meshElsPos.insert(edgeMElementsId[h], pointPos);
            meshElsType.insert(edgeMElementsId[h], elementType);
            meshId2GraphId.insert(edgeMElementsId[h], QPoint(2, edgesIds[j]));

            QPainterPath path;
            QPainterPath text;

            path.arcTo(QRectF(-radius, -radius, width, height), 0, 360);
            text.addText(-radius / 2.0, radius / 2.0, QFont("Arial", fontSize), elementType);
            path.translate(pointPos);
            text.translate(pointPos);
            if (showMesh) {
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::darkCyan);
                painter.drawPath(path);
                painter.setPen(Qt::yellow);
                painter.setBrush(Qt::yellow);
                painter.drawPath(text);
            } else {
                qreal dotR = size2screen(1);
                QPainterPath dotPath;
                painter.setPen(Qt::black);
                painter.setBrush(Qt::black);
                dotPath.arcTo(QRectF(-dotR, -dotR, dotR * 2, dotR * 2), 0, 360);
                dotPath.translate(pointPos);
                painter.drawPath(dotPath);
            }

            QPainterPath mousePath;
            mousePath.arcTo(QRectF(-1, -1, 1, 1), 0, 360);
            mousePath.translate(mouseCurrentPos);

            if (path.intersects(mousePath) && selectedTool == 7) {
                painter.setPen(Qt::NoPen);
                painter.setBrush(Qt::darkCyan);
                painter.drawPath(path);
                painter.setPen(Qt::yellow);
                painter.setBrush(Qt::yellow);
                painter.drawPath(text);

                if (firstTime) {
                    firstTime = false;
                    hitMeshEls.clear();
                }

                QPoint temp(2, edgeMElementsId[h]);
                hitMeshEls.append(temp);
            }
        }
    }
}