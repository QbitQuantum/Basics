Vec2f VRIntersect_computeTexel(VRIntersection& ins, NodeRecPtr node) {
    if (!ins.hit) return Vec2f(0,0);
    if (node == 0) return Vec2f(0,0);

    GeometryRefPtr geo = dynamic_cast<Geometry*>( node->getCore() );
    if (geo == 0) return Vec2f(0,0);
    auto texcoords = geo->getTexCoords();
    if (texcoords == 0) return Vec2f(0,0);
    TriangleIterator iter = geo->beginTriangles(); iter.seek( ins.triangle );


    Matrix m = node->getToWorld();
    m.invert();
    Pnt3f local_pnt; m.mult(ins.point, local_pnt);

    Pnt3f p0 = iter.getPosition(0);
    Pnt3f p1 = iter.getPosition(1);
    Pnt3f p2 = iter.getPosition(2);
    Vec3f cr = (p1 - p0).cross(p2 - p0);
    Vec3f n = cr; n.normalize();

    float areaABC = n.dot(cr);
    float areaPBC = n.dot((p1 - local_pnt).cross(p2 - local_pnt));
    float areaPCA = n.dot((p2 - local_pnt).cross(p0 - local_pnt));
    float a = areaPBC / areaABC;
    float b = areaPCA / areaABC;
    float c = 1.0f - a - b;

    return iter.getTexCoords(0) * a + iter.getTexCoords(1) * b + iter.getTexCoords(2) * c;
}