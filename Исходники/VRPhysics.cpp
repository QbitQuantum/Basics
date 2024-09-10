btCollisionShape* VRPhysics::getConvexShape() {
    btConvexHullShape* shape = new btConvexHullShape();

    OSG::Matrix m;
    OSG::Matrix M = vr_obj->getWorldMatrix();
    M.invert();

    vector<OSG::VRObject*> geos = vr_obj->getObjectListByType("Geometry");
	for (auto g : geos) {
        OSG::VRGeometry* geo = (OSG::VRGeometry*)g;
        if (geo == 0) continue;
        if (geo->getMesh() == 0) continue;
        OSG::GeoVectorPropertyRecPtr pos = geo->getMesh()->getPositions();
        if (pos == 0) continue;

        if (geo != vr_obj) {
            m = geo->getWorldMatrix();
            m.multLeft(M);
        }

		for (unsigned int i = 0; i<pos->size(); i++) {
            OSG::Pnt3f p;
            pos->getValue(p,i);
            if (geo != vr_obj) m.mult(p,p);
            for (int i=0; i<3; i++) p[i] *= scale[i];
            shape->addPoint(btVector3(p[0], p[1], p[2]));
        }
    }

    shape->setMargin(collisionMargin);

    //cout << "\nConstruct Convex shape for " << vr_obj->getName() << endl;
    return shape;
}