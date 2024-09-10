void RDirNode::checkFrustum(const Frustum& frustum) {

    in_frustum = frustum.intersects(quadItemBounds);

    for(std::list<RDirNode*>::const_iterator it = children.begin(); it != children.end(); it++) {
        RDirNode* node = (*it);
        node->checkFrustum(frustum);
    }
}