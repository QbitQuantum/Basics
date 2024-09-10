Path PathUtilities::pathWithShrinkWrappedRects(const Vector<FloatRect>& rects, float radius)
{
    Path path;

    if (rects.isEmpty())
        return path;

    if (rects.size() > 20) {
        path.addRoundedRect(unionRect(rects), FloatSize(radius, radius));
        return path;
    }

    Vector<FloatRect> sortedRects = rects;

    std::sort(sortedRects.begin(), sortedRects.end(), [](FloatRect a, FloatRect b) { return b.y() > a.y(); });

    FloatPointGraph graph;
    Vector<FloatPointGraph::Polygon> rectPolygons;
    rectPolygons.reserveInitialCapacity(sortedRects.size());

    for (auto& rect : sortedRects) {
        bool isContained = false;
        for (auto& otherRect : sortedRects) {
            if (&rect == &otherRect)
                continue;
            if (otherRect.contains(rect)) {
                isContained = true;
                break;
            }
        }

        if (!isContained)
            rectPolygons.append(edgesForRect(rect, graph));
    }

    Vector<FloatPointGraph::Polygon> polys = unitePolygons(rectPolygons, graph);

    if (polys.isEmpty()) {
        path.addRoundedRect(unionRect(sortedRects), FloatSize(radius, radius));
        return path;
    }

    for (auto& poly : polys) {
        for (unsigned i = 0; i < poly.size(); i++) {
            FloatPointGraph::Edge& toEdge = poly[i];
            // Connect the first edge to the last.
            FloatPointGraph::Edge& fromEdge = (i > 0) ? poly[i - 1] : poly[poly.size() - 1];

            FloatPoint fromEdgeVec = toFloatPoint(*fromEdge.second - *fromEdge.first);
            FloatPoint toEdgeVec = toFloatPoint(*toEdge.second - *toEdge.first);

            // Clamp the radius to no more than half the length of either adjacent edge,
            // because we want a smooth curve and don't want unequal radii.
            float clampedRadius = std::min(radius, fabsf(fromEdgeVec.x() ? fromEdgeVec.x() : fromEdgeVec.y()) / 2);
            clampedRadius = std::min(clampedRadius, fabsf(toEdgeVec.x() ? toEdgeVec.x() : toEdgeVec.y()) / 2);

            FloatPoint fromEdgeNorm = fromEdgeVec;
            fromEdgeNorm.normalize();
            FloatPoint toEdgeNorm = toEdgeVec;
            toEdgeNorm.normalize();

            // Project the radius along the incoming and outgoing edge.
            FloatSize fromOffset = clampedRadius * toFloatSize(fromEdgeNorm);
            FloatSize toOffset = clampedRadius * toFloatSize(toEdgeNorm);

            if (!i)
                path.moveTo(*fromEdge.second - fromOffset);
            else
                path.addLineTo(*fromEdge.second - fromOffset);
            path.addArcTo(*fromEdge.second, *toEdge.first + toOffset, clampedRadius);
        }

        path.closeSubpath();
    }

    return path;
}