void KoConnectionShapePrivate::normalPath(const qreal MinimumEscapeLength)
{
    // Clear the path to build it again.
    path.clear();
    path.append(handles[KoConnectionShape::StartHandle]);

    QList<QPointF> edges1;
    QList<QPointF> edges2;

    QPointF direction1 = escapeDirection(KoConnectionShape::StartHandle);
    QPointF direction2 = escapeDirection(KoConnectionShape::EndHandle);

    QPointF edgePoint1 = handles[KoConnectionShape::StartHandle] + MinimumEscapeLength * direction1;
    QPointF edgePoint2 = handles[KoConnectionShape::EndHandle] + MinimumEscapeLength * direction2;

    edges1.append(edgePoint1);
    edges2.prepend(edgePoint2);

    if (handleConnected(KoConnectionShape::StartHandle) && handleConnected(KoConnectionShape::EndHandle)) {
        QPointF intersection;
        bool connected = false;
        do {
            // first check if directions from current edge points intersect
            if (intersects(edgePoint1, direction1, edgePoint2, direction2, intersection)) {
                // directions intersect, we have another edge point and be done
                edges1.append(intersection);
                break;
            }

            // check if we are going toward the other handle
            qreal sp = scalarProd(direction1, edgePoint2 - edgePoint1);
            if (sp >= 0.0) {
                // if we are having the same direction, go all the way toward
                // the other handle, else only go half the way
                if (direction1 == direction2)
                    edgePoint1 += sp * direction1;
                else
                    edgePoint1 += 0.5 * sp * direction1;
                edges1.append(edgePoint1);
                // switch direction
                direction1 = perpendicularDirection(edgePoint1, direction1, edgePoint2);
            } else {
                // we are not going into the same direction, so switch direction
                direction1 = perpendicularDirection(edgePoint1, direction1, edgePoint2);
            }
        } while (! connected);
    }

    path.append(edges1);
    path.append(edges2);

    path.append(handles[KoConnectionShape::EndHandle]);
}