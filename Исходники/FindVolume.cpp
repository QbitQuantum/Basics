void SphereOfSphereAndPt(Sphere &s, Vect &p)
{
    // Compute squared distance between point and sphere center
    Vect d = p - s.cntr;

    float dist2 = d.dot( d);
    // Only update s if point p is outside it
    if (dist2 > s.rad * s.rad) 
	{
        float dist = sqrtf(dist2);
        float newRadius = (s.rad + dist) * 0.5f;
        float k = (newRadius - s.rad) / dist;
        s.rad = newRadius;
        s.cntr += d * k;
    }
}