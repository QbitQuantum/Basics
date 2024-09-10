bool raycast_sphere(Ray3CR ray, SphereCR s)
{
        Vec3 m = ray.pt - s.c;
        real c = m.length_sqr() - s.r*s.r; if( c <= 0 ) return true;  // ray origin in sphere
        real b = m.dot(ray.dir);           if( b >  0 ) return false; // ray pointing away from sphere
        return b*b - c >= 0;
}