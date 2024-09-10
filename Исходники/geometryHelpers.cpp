void GetOrthonormalBasisFromNormal(const Vector<float>& normal,
                                   Vector<float>& u, Vector<float>& v,
                                   Vector<float>& w) {
    // u-v-w - Coordinate system - w is along normal
    // determine major direction:
    w = normal;
    int axis = 0;
    float mag = fabs(w.x());
    if (fabs(w.y()) > mag) {
        axis = 1;
        mag = fabs(w.y());
    }
    if (fabs(w.z()) > mag) {
        axis = 2;
        mag = fabs(w.z());
    }

    w.normalize();

    if (axis != 0) {
        v = w.cross(Vector<float>(1, 0, 0));
        v.normalize();
        u = v.cross(w);
    } else if (axis != 1) {
        v = w.cross(Vector<float>(0, 1, 0));
        v.normalize();
        u = v.cross(w);
    } else {
        v = w.cross(Vector<float>(0, 0, 1));
        v.normalize();
        u = v.cross(w);
    }
}