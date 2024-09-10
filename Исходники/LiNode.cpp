int
LiNode::subdivide() {

    Vec3 size = (_max - _min) * 0.5;

    if(size.length() < 0.00000001) {
        printf("SIZE: %d\n", _surfelCount);
        for(int i = 0; i < _surfelCount; i++) {
            Surfel surf = *_surfelData[i];
            printf("\t%s\n", surf.position().str());
        }
        printf("ERROR\n\tMIN: %s\n\tMAX: %s\n", _min.str(), _max.str());
        exit(1);
    }
    assert(size.length() > 0.00000001);
    Vec3 min, max;
    int x,y,z;

    // Loop over children
    for(int i = 0; i < 8; i++) {
        // Find out which child this is (in terms of what quadrant)
        x = i%2;
        y = (i/2)%2;
        z = (i/4);

        // Define minimum by which quadrant it is in
        min = Vec3(_min.x() + (size.x() * x),
                     _min.y() + (size.y() * y),
                     _min.z() + (size.z() * z));

        // Max is always the minimum plus the size of the node
        max = min + size;

        
        m_children[i] = new LiNode(min, max);
    }

    int surfCount = _surfelCount;

    //_surfelCount = 0;

    // Iterate over all existing surfel data
    for(int i = 0; i < surfCount; i++) {
        //printf("Re-Adding %s!\n", _surfelData[i]->position().str());
        // Re-add the surfel, allowing it to recurse into the children
        add(_surfelData[i]);
    }
    // Clear all surfel data in this node
    return 0;
}