void RoutePresenter::showRouteSegment(QTreeWidgetItem* routeItem, const QGeoRouteSegment &segment)
{
    QTreeWidgetItem* segmentItem = new QTreeWidgetItem(routeItem);
    segmentItem->setText(0, "segment");

    QTreeWidgetItem* durationItem = new QTreeWidgetItem(segmentItem);
    durationItem->setText(0, "duration");
    durationItem->setText(1, QString().setNum(segment.travelTime()));

    QTreeWidgetItem* distanceItem = new QTreeWidgetItem(segmentItem);
    distanceItem->setText(0, "distance");
    distanceItem->setText(1, QString().setNum(segment.distance()));

    // add back in when more qgeoinstruction classes are made available
    /*
        QString s = segment->turn();

        if (!s.isEmpty()) {
            propItem = new QTreeWidgetItem(maneuverItem);
            propItem->setText(0, "turn");
            propItem->setText(1, s);
        }

        s = segment->streetName();

        if (!s.isEmpty()) {
            propItem = new QTreeWidgetItem(maneuverItem);
            propItem->setText(0, "street name");
            propItem->setText(1, s);
        }

        s = segment->routeName();

        if (!s.isEmpty()) {
            propItem = new QTreeWidgetItem(maneuverItem);
            propItem->setText(0, "route name");
            propItem->setText(1, s);
        }

        s = segment->nextStreetName();

        if (!s.isEmpty()) {
            propItem = new QTreeWidgetItem(maneuverItem);
            propItem->setText(0, "next street name");
            propItem->setText(1, s);
        }

        s = segment->signPost();

        if (!s.isEmpty()) {
            propItem = new QTreeWidgetItem(maneuverItem);
            propItem->setText(0, "sign post");
            propItem->setText(1, s);
        }

        propItem = new QTreeWidgetItem(maneuverItem);
        propItem->setText(0, "traffic direction");
        propItem->setText(1, QString().setNum(segment->trafficDirection()));
    */
    QTreeWidgetItem* pathItem = new QTreeWidgetItem(segmentItem);
    pathItem->setText(0, "path");
    showPoints(pathItem, segment.path());

    if (!segment.maneuver().instructionText().isEmpty()) {
        QTreeWidgetItem* instructionItem = new QTreeWidgetItem(segmentItem);
        instructionItem->setText(0, "instruction");

        QTreeWidgetItem* positionItem = new QTreeWidgetItem(instructionItem);
        positionItem->setText(0, "position");
        QList<QGeoCoordinate> points;
        points.append(segment.maneuver().position());
        showPoints(positionItem, points);

        QTreeWidgetItem* instructionTextItem = new QTreeWidgetItem(instructionItem);
        instructionTextItem->setText(0, "text");
        instructionTextItem->setText(1, segment.maneuver().instructionText());
    }
}