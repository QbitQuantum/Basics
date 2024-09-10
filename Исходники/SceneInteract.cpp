float3 SceneInteract::RaycastFurthestIntersect(const float3 &from, const Vector<float3> &to, unsigned layerMask) const
{
    float3 intersection = float3::nan;
    Scene* scene = framework->Module<UrhoRenderer>()->MainCameraScene();
    GraphicsWorld* world = scene ? scene->Subsystem<GraphicsWorld>().Get() : nullptr;
    if (!world)
        return intersection;

    Ray ray;
    ray.pos = from;

    float furthest = 0.0f;
    for (int i=0, len=to.Size(); i<len; ++i)
    {
        ray.dir = to[i].Sub(from).Normalized();

        // We use raycast all as there might be multiple entities in between 'from' and 'to'
        // and this function should return the closest hit to the 'to' target.
        float maxDistance = from.Distance(to[i]);
        RayQueryResultVector results = world->RaycastAll(ray, layerMask, maxDistance);
        if (!results.Empty())
        {
            // Last result is picked as the results are already ordered by distance.
            RayQueryResult& result = results.Back();
            if (result.t > furthest)
            {
                furthest = result.t;
                intersection = result.pos;
            }
        }
    }
    return intersection;
}