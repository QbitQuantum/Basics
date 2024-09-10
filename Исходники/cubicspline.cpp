bool CubicSpline::intersects(const CubicSpline &rt, VectorF ignoreAxis) const
{
#if 1
    vector<VectorF> path1 = getSplinePoints(*this);
    vector<VectorF> path2 = getSplinePoints(rt);
    for(size_t i = 1; i < path1.size(); i++)
    {
        for(size_t j = 1; j < path2.size(); j++)
        {
            if(linesIntersect(path1[i - 1], path1[i], path2[j - 1], path2[j], 0))
                return true;
        }
    }
    return false;
#else
    const int splitCount = 50; // number of line segments to split spline into
    ignoreAxis = normalize(ignoreAxis);

    for(int segmentNumber = 0; segmentNumber < splitCount; segmentNumber++)
    {
        float startT = (float)(segmentNumber) / splitCount;
        float endT = (float)(segmentNumber + 1) / splitCount;
        VectorF startP = rt.evaluate(startT);
        startP -= ignoreAxis * dot(ignoreAxis, startP); // move to plane normal to ignoreAxis
        VectorF endP = rt.evaluate(endT);
        endP -= ignoreAxis * dot(ignoreAxis, endP); // move to plane normal to ignoreAxis
        VectorF delta = endP - startP;

        if(absSquared(delta) < eps * eps) // if delta is too small
        {
            continue;
        }

        // solve dot(evaluate(t), cross(ignoreAxis, delta)) == 0 and it intersects if dot(evaluate(t) - startP, delta) / dot(delta, delta) is in [0, 1] and t is in [0, 1]
        VectorF normal = cross(ignoreAxis, delta);
        float cubic = dot(getCubic(), normal);
        float quadratic = dot(getQuadratic(), normal);
        float linear = dot(getLinear(), normal);
        float constant = dot(getConstant(), normal);
        float intersections[3];
        int intersectionCount = solveCubic(constant, linear, quadratic, cubic, intersections);

        for(int i = 0; i < intersectionCount; i++)
        {
            float t = intersections[i];

            if(t < 0 || t > 1)
            {
                continue;
            }

            float v = dot(evaluate(t) - startP, delta) / dot(delta, delta);

            if(v < 0 || v > 1)
            {
                continue;
            }

            return true;
        }
    }

    return false;
#endif
}