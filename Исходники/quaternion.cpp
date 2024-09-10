 Quaternion Quaternion::Squad(
    float t, 
    const Quaternion &p,
    const Quaternion &a, 
    const Quaternion &b,
    const Quaternion &q, 
    bool shortestPath)
 {
    float slerpT = 2.0f * t * (1.0f - t);
    Quaternion slerpP = Slerp(t, p, q, shortestPath);
    Quaternion slerpQ = Slerp(t, a, b);
    return Slerp(slerpT, slerpP ,slerpQ);
 }