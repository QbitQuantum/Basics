Vector3 NavigationMesh::Raycast(const Vector3& start, const Vector3& end, const Vector3& extents, const dtQueryFilter* filter,
    Vector3* hitNormal)
{
    if (hitNormal)
        *hitNormal = Vector3::DOWN;

    if (!InitializeQuery())
        return end;

    const Matrix3x4& transform = node_->GetWorldTransform();
    Matrix3x4 inverse = transform.Inverse();

    Vector3 localStart = inverse * start;
    Vector3 localEnd = inverse * end;

    const dtQueryFilter* queryFilter = filter ? filter : queryFilter_.Get();
    dtPolyRef startRef;
    navMeshQuery_->findNearestPoly(&localStart.x_, &extents.x_, queryFilter, &startRef, 0);
    if (!startRef)
        return end;

    Vector3 normal;
    if (!hitNormal)
        hitNormal = &normal;
    float t;
    int numPolys;

    navMeshQuery_->raycast(startRef, &localStart.x_, &localEnd.x_, queryFilter, &t, &hitNormal->x_, pathData_->polys_, &numPolys,
        MAX_POLYS);
    if (t == FLT_MAX)
        t = 1.0f;

    return start.Lerp(end, t);
}