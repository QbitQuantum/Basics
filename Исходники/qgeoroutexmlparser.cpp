bool QGeoRouteXmlParser::postProcessRoute(QGeoRoute *route)
{
    QList<QGeoRouteSegment> routeSegments;

    int maneuverIndex = 0;
    for (int i = 0; i < segments.count(); ++i) {
        while ((maneuverIndex < maneuvers.size()) && maneuvers.at(maneuverIndex).toId.isEmpty()) {
            QGeoRouteSegment segment;
            segment.setManeuver(maneuvers.at(maneuverIndex).maneuver);
            QList<QGeoCoordinate> path; // use instruction position as one point segment path
            path.append(maneuvers.at(maneuverIndex).maneuver.position());
            segment.setPath(path);
            routeSegments.append(segment);
            ++maneuverIndex;
        }
        QGeoRouteSegment segment = segments.at(i).segment;
        if ((maneuverIndex < maneuvers.size()) && segments.at(i).id == maneuvers.at(maneuverIndex).toId) {
            segment.setManeuver(maneuvers.at(maneuverIndex).maneuver);
            ++maneuverIndex;
        }
        routeSegments.append(segment);
    }


    QList<QGeoRouteSegment> compactedRouteSegments;
    compactedRouteSegments.append(routeSegments.first());
    routeSegments.removeFirst();

    while (routeSegments.size() > 0) {
        QGeoRouteSegment segment = routeSegments.first();
        routeSegments.removeFirst();

        QGeoRouteSegment lastSegment = compactedRouteSegments.last();

        if (lastSegment.maneuver().isValid())
            compactedRouteSegments.append(segment);
        else {
            compactedRouteSegments.removeLast();
            lastSegment.setDistance(lastSegment.distance() + segment.distance());
            lastSegment.setTravelTime(lastSegment.travelTime() + segment.travelTime());
            QList<QGeoCoordinate> path = lastSegment.path();
            path.append(segment.path());
            lastSegment.setPath(path);
            lastSegment.setManeuver(segment.maneuver());
            compactedRouteSegments.append(lastSegment);
        }
    }

//    //Add the first instruction as starting point
//    if (maneuvers.count() > 0) {
//        QGeoRouteSegment segment;
//        segment.setManeuver(maneuvers[0].maneuver);
//        QList<QGeoCoordinate> path; // use instruction position as one point segment path
//        path.append(maneuvers[0].maneuver.position());
//        segment.setPath(path);
//        routesegments.append(segment);
//        maneuvers.removeAt(0);
//    }

//    for (int i = 0; i < segments.count(); ++i) {
//        if (segments[i].maneuverId.isEmpty()) {
//            routesegments.append(segments[i].segment);
//        } else {
//            for (int j = 0; j < maneuvers.count(); ++j) {
//                if (maneuvers[j].id == segments[i].maneuverId
//                        && segments[i].segment.maneuver().instructionText().isEmpty()) {
//                    segments[i].segment.setManeuver(maneuvers[j].maneuver);
//                    routesegments.append(segments[i].segment);
//                    maneuvers.removeAt(j);
//                    break;
//                } else {
//                    //Add orphan instruction into new empty segment
//                    QGeoRouteSegment segment;
//                    segment.setManeuver(maneuvers[j].maneuver);
//                    QList<QGeoCoordinate> path; // use instruction position as one point segment path
//                    path.append(maneuvers[j].maneuver.position());
//                    segment.setPath(path);
//                    routesegments.append(segment);
//                    maneuvers.removeAt(j);
//                    --j;
//                }
//            }
//        }
//    }

    if (compactedRouteSegments.size() > 0) {
        route->setFirstRouteSegment(compactedRouteSegments.at(0));
        for (int i = 0; i < compactedRouteSegments.size() - 1; ++i)
            compactedRouteSegments[i].setNextRouteSegment(compactedRouteSegments.at(i + 1));
    }

    maneuvers.clear();
    segments.clear();
    return true;
}