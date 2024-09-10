//See notes to look at how the routine below was determined
double Sphere::intersect(const Ray &r) const
{
    //pos is the center of circle and op connects origin of ray to center
    //of circle
    Vec3 op = pos - r.o;
    double t, eps = 1e-4;   //eps is our tolerance for hitting
    double b = op.dot(r.d);   //1/2 b from quad. eq.
    double det = b * b - op.dot(op) + rad * rad;   //(b^2-4ac):a=1 by norm

    if (det < 0) return 0;
    else det = sqrt(det);
    //return smallest positive t since this is the point the camera can see
    return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
}