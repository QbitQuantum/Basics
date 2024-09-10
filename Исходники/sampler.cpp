HemisphereSampler::HemisphereSampler(Vec3 normal, int us, int ts)
    : _max_us(us), _max_ts(ts), _us(0), _ts(0), _normal(normal) {

    Vec3 up = Vec3(0,1,0);
    Vec3 w = normal;
    Vec3 u;
    Vec3 v;
    w.norm();
    //w = w * -1;

    if(w.y() >= 0.9995 || w.y() <= -0.995) {
        u = Vec3(1,0,0);
        v = Vec3(0,0,1);
    } else {
        up.cross(w, &u);
        u.norm();
        w.cross(u, &v);
    }

    //cout << "Camera Loc: " << endl << m1 << endl;

    MyMat m = MyMat(u.x(), v.x(), w.x(), 0,
                    u.y(), v.y(), w.y(), 0,
                    u.z(), v.z(), w.z(), 0,
                    0, 0, 0, 1);

    _matrix = m;
    //cout << "UVW: " << endl << m2 << endl;

    //_matrix = m.inverse();
}