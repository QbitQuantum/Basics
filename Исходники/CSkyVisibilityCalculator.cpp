T calcSkyVisibility(const COctreeNode *octree, const Vector3<T> &pos, const Vector3<T> &normal, const Vector3<T> &tangent, const Vector3<T> &bitangent,
                    size_t rayCount)
{
    size_t hitRays = 0;
    for(size_t i = 0; i < rayCount; ++i)
    {
        Vector3<T> rnd(randomFloat<T>(), randomFloat<T>()*T(2.0)-T(1.0), randomFloat<T>()*T(2.0)-T(1.0));
        rnd.Normalize();
        Vector3<T> raydir = normal * rnd.x + tangent * rnd.y + bitangent * rnd.z;
        CRay_t<T> ray(pos + raydir * T(0.01), raydir.Normalize());
        if(octree->rayTriangleCollision(ray))
            hitRays++;
    }
    return calcSkyVisibility(T(hitRays), T(rayCount));
}