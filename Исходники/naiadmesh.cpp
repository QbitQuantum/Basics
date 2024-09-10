bool NaiadTriangle::IntersectP(const Ray &ray) const {
    PBRT_RAY_TRIANGLE_INTERSECTIONP_TEST(const_cast<Ray *>(&ray), const_cast<NaiadTriangle *>(this));
    // Compute $\VEC{s}_1$

    // Get NaiadTriangle vertices in _p1_, _p2_, and _p3_
    const Point &p1 = mesh->p[v[0]];
    const Point &p2 = mesh->p[v[1]];
    const Point &p3 = mesh->p[v[2]];
    Vector e1 = p2 - p1;
    Vector e2 = p3 - p1;
    Vector s1 = Cross(ray.d, e2);
    float divisor = Dot(s1, e1);
    
    if (divisor == 0.)
        return false;
    float invDivisor = 1.f / divisor;

    // Compute first barycentric coordinate
    Vector d = ray.o - p1;
    float b1 = Dot(d, s1) * invDivisor;
    if (b1 < 0. || b1 > 1.)
        return false;

    // Compute second barycentric coordinate
    Vector s2 = Cross(d, e1);
    float b2 = Dot(ray.d, s2) * invDivisor;
    if (b2 < 0. || b1 + b2 > 1.)
        return false;

    // Compute _t_ to intersection point
    float t = Dot(e2, s2) * invDivisor;
    if (t < ray.mint || t > ray.maxt)
        return false;

    // Test shadow ray intersection against alpha texture, if present
    if (ray.depth != -1 && mesh->alphaTexture) {
        // Compute NaiadTriangle partial derivatives
        Vector dpdu, dpdv;
        float uvs[3][2];
        GetUVs(uvs);

        // Compute deltas for NaiadTriangle partial derivatives
        float du1 = uvs[0][0] - uvs[2][0];
        float du2 = uvs[1][0] - uvs[2][0];
        float dv1 = uvs[0][1] - uvs[2][1];
        float dv2 = uvs[1][1] - uvs[2][1];
        Vector dp1 = p1 - p3, dp2 = p2 - p3;
        float determinant = du1 * dv2 - dv1 * du2;
        if (determinant == 0.f) {
            // Handle zero determinant for NaiadTriangle partial derivative matrix
            CoordinateSystem(Normalize(Cross(e2, e1)), &dpdu, &dpdv);
        }
        else {
            float invdet = 1.f / determinant;
            dpdu = ( dv2 * dp1 - dv1 * dp2) * invdet;
            dpdv = (-du2 * dp1 + du1 * dp2) * invdet;
        }

        // Interpolate $(u,v)$ NaiadTriangle parametric coordinates
        float b0 = 1 - b1 - b2;
        float tu = b0*uvs[0][0] + b1*uvs[1][0] + b2*uvs[2][0];
        float tv = b0*uvs[0][1] + b1*uvs[1][1] + b2*uvs[2][1];
        DifferentialGeometry dgLocal(ray(t), dpdu, dpdv,
                                     Normal(0,0,0), Normal(0,0,0),
                                     tu, tv, this);
        if (mesh->alphaTexture->Evaluate(dgLocal) == 0.f)
            return false;
    }
    PBRT_RAY_TRIANGLE_INTERSECTIONP_HIT(const_cast<Ray *>(&ray), t);
    return true;
}