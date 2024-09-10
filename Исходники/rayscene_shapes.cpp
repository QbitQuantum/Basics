Intersection Triangle::intersects(Ray ray) {
    Intersection is(ray, this);

    Vect p = ray.getOrigin();
    Vect d = ray.getDirection();
    Vect v0 = getA();
    Vect v1 = getB();
    Vect v2 = getC();

    Vect e1, e2, h, s, q;
    float a0, f, u, v;

    e1 = v1 - v0;
    e2 = v2 - v0;

    h = d.crossProduct(e2);
    a0 = e1.dotProduct(h);

    if (a0 > -0.00001 && a0 < 0.00001)
        return is;

    f = 1 / a0;
    s = p - v0;
    u = f * (s.dotProduct(h));

    if (u < 0.0 || u > 1.0)
        return is;

    q = s.crossProduct(e1);
    v = f * d.dotProduct(q);

    if (v < 0.0 || u + v > 1.0)
        return is;

    // at this stage we can compute t to find out where
    // the intersection point is on the line
    float t = f * e2.dotProduct(q);

    if (t > 0.00001) { // ray intersection
        is.setIntersectionPoint(t);
        return is;
    }

    else // this means that there is a line intersection
         // but not a ray intersection
         return is;
}