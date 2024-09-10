void
NIImporter_SUMO::addJunction(const SUMOSAXAttributes& attrs) {
    // get the id, report an error if not given or empty...
    bool ok = true;
    std::string id = attrs.getStringReporting(SUMO_ATTR_ID, 0, ok);
    if (!ok) {
        return;
    }
    if (id[0] == ':') { // internal node
        return;
    }
    SumoXMLNodeType type = attrs.getNodeType(ok);
    if (ok) {
        if (type == NODETYPE_DEAD_END_DEPRECATED) { // patch legacy type
            type = NODETYPE_DEAD_END;
        }
    } else {
        WRITE_WARNING("Unknown node type for junction '" + id + "'.");
    }
    Position pos = readPosition(attrs, id, ok);
    NILoader::transformCoordinates(pos, true, myLocation);
    // the network may have non-default edge geometry.
    // accurate reconstruction of legacy networks is not possible. We ought to warn about this
    if (attrs.hasAttribute(SUMO_ATTR_SHAPE)) {
        PositionVector shape = attrs.getShapeReporting(SUMO_ATTR_SHAPE, id.c_str(), ok, true);
        if (shape.size() > 0) {
            shape.push_back_noDoublePos(shape[0]); // need closed shape
            if (!shape.around(pos) && shape.distance(pos) > 1) { // MAGIC_THRESHOLD
                // WRITE_WARNING("Junction '" + id + "': distance between pos and shape is " + toString(shape.distance(pos)));
                mySuspectKeepShape = true;
            }
        }
    }
    NBNode* node = new NBNode(id, pos, type);
    if (!myNodeCont.insert(node)) {
        WRITE_ERROR("Problems on adding junction '" + id + "'.");
        delete node;
        return;
    }
}