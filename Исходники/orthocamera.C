// Constructor
OrthographicCamera::OrthographicCamera(Vec3f &c, Vec3f &p, Vec3f &u,
                                       float sz) {
    size = sz;
    center = c;
    p.Normalize();
    projection = p;
    Vec3f::Cross3(horizontal, u, p);
    horizontal.Normalize();
    Vec3f::Cross3(up, p, horizontal);
}