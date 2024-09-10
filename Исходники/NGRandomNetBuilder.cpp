bool
NGRandomNetBuilder::canConnect(NGNode* baseNode, NGNode* newNode) {
    bool connectable = true;
    const PositionVector n(baseNode->getPosition(), newNode->getPosition());

    // check for range between Basenode and Newnode
    if (connectable) {
        SUMOReal dist = n.length();
        if ((dist < myMinDistance) || (dist > myMaxDistance)) {
            connectable = false;
        }
    }

    // check for angle restrictions
    if (connectable) {
        connectable = checkAngles(baseNode);
    }
    if (connectable) {
        connectable = checkAngles(newNode);
    }

    // check for intersections and range restrictions with outer links
    if (connectable) {
        NGEdgeList::iterator li;
        li = myOuterLinks.begin();
        while (connectable && (li != myOuterLinks.end())) {
            // check intersection only if links don't share a node
            const NGNode* const start = (*li)->getStartNode();
            const NGNode* const end = (*li)->getEndNode();
            const Position& p1 = start->getPosition();
            const Position& p2 = end->getPosition();
            if ((baseNode != start) && (baseNode != end) && (newNode != start) && (newNode != end)) {
                connectable = !n.intersects(p1, p2);
            }
            // check NewNode-To-Links distance only, if NewNode isn't part of link
            if (connectable && (newNode != start) && (newNode != end)) {
                const SUMOReal offset = GeomHelper::nearest_offset_on_line_to_point2D(p1, p2, n[1]);
                if (offset != GeomHelper::INVALID_OFFSET) {
                    const Position p = PositionVector(p1, p2).positionAtOffset2D(offset);
                    const SUMOReal dist = p.distanceTo2D(n[1]);
                    if (dist < myMinDistance) {
                        connectable = false;
                    }
                }
            }
            ++li;
        }
    }
    return connectable;
}