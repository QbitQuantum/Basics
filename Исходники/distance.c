double distance2(struct point* p, struct point* p1, struct point* p2)
{
    struct point proj;
    double length2;
    double tangent;


    length2 = length_squared(p1, p2);

    if ( length2 == 0.0 ) {
        // p1 == p2
        return length_squared(p, p1);
    }

    tangent = dot(p, p1, p2);
    tangent = tangent / length2;

    if ( tangent < 0.0 ) {
        // Beyond p1
        return length_squared(p, p1);
    } else if ( tangent > 1.0 ) {
        // Beyond p2
        return length_squared(p, p2);
    }

    projection(&proj, p1, p2, tangent);

    return length_squared(p, &proj);
}