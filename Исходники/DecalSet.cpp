static void ClipPolygon(PODVector<DecalVertex>& dest, const PODVector<DecalVertex>& src, const Plane& plane, bool skinned)
{
    unsigned last = 0;
    float lastDistance = 0.0f;
    dest.Clear();

    if (src.Empty())
        return;

    for (unsigned i = 0; i < src.Size(); ++i)
    {
        float distance = plane.Distance(src[i].position_);
        if (distance >= 0.0f)
        {
            if (lastDistance < 0.0f)
                dest.Push(ClipEdge(src[last], src[i], lastDistance, distance, skinned));

            dest.Push(src[i]);
        }
        else
        {
            if (lastDistance >= 0.0f && i != 0)
                dest.Push(ClipEdge(src[last], src[i], lastDistance, distance, skinned));
        }

        last = i;
        lastDistance = distance;
    }

    // Recheck the distances of the last and first vertices and add the final clipped vertex if applicable
    float distance = plane.Distance(src[0].position_);
    if ((lastDistance < 0.0f && distance >= 0.0f) || (lastDistance >= 0.0f && distance < 0.0f))
        dest.Push(ClipEdge(src[last], src[0], lastDistance, distance, skinned));
}