void VRMesure::processBar(Vec3f p1, Vec3f p2) {
    //p1 -= l->getWorldPosition();
    //p2 -= l->getWorldPosition();
    Vec3f d = p2-p1;

    Vec3f t1, t2;
    if (d[1] < d[0]) t1 = d.cross(Vec3f(0,1,0));//take the biggest axis
    else t1 = d.cross(Vec3f(1,0,0));
    t2 = d.cross(t1);

    t1.normalize();
    t1 *= 0.01;
    t2.normalize();
    t2 *= 0.01;

    GeometryRecPtr geo = l->getMesh();
    GeoPnt3fPropertyRecPtr pos = dynamic_cast<GeoPnt3fProperty*>(geo->getPositions());
    GeoVec3fPropertyRecPtr norms = dynamic_cast<GeoVec3fProperty*>(geo->getNormals());

    pos->setValue(p1+t1, 5);
    pos->setValue(p1+t1, 12);
    pos->setValue(p1+t1, 20);

    pos->setValue(p1+t2, 4);
    pos->setValue(p1+t2, 9);
    pos->setValue(p1+t2, 21);

    pos->setValue(p1-t1, 6);
    pos->setValue(p1-t1, 11);
    pos->setValue(p1-t1, 19);

    pos->setValue(p1-t2, 7);
    pos->setValue(p1-t2, 14);
    pos->setValue(p1-t2, 18);

    pos->setValue(p2+t1, 0);
    pos->setValue(p2+t1, 13);
    pos->setValue(p2+t1, 22);

    pos->setValue(p2+t2, 1);
    pos->setValue(p2+t2, 8);
    pos->setValue(p2+t2, 23);

    pos->setValue(p2-t1, 3);
    pos->setValue(p2-t1, 10);
    pos->setValue(p2-t1, 17);

    pos->setValue(p2-t2, 2);
    pos->setValue(p2-t2, 15);
    pos->setValue(p2-t2, 16);

    norms->setValue(p1+t1, 5);
    norms->setValue(p1+t1, 12);
    norms->setValue(p1+t1, 20);

    norms->setValue(p1+t2, 4);
    norms->setValue(p1+t2, 9);
    norms->setValue(p1+t2, 21);

    norms->setValue(p1-t1, 6);
    norms->setValue(p1-t1, 11);
    norms->setValue(p1-t1, 19);

    norms->setValue(p1-t2, 7);
    norms->setValue(p1-t2, 14);
    norms->setValue(p1-t2, 18);

    norms->setValue(p2+t1, 0);
    norms->setValue(p2+t1, 13);
    norms->setValue(p2+t1, 22);

    norms->setValue(p2+t2, 1);
    norms->setValue(p2+t2, 8);
    norms->setValue(p2+t2, 23);

    norms->setValue(p2-t1, 3);
    norms->setValue(p2-t1, 10);
    norms->setValue(p2-t1, 17);

    norms->setValue(p2-t2, 2);
    norms->setValue(p2-t2, 15);
    norms->setValue(p2-t2, 16);
}