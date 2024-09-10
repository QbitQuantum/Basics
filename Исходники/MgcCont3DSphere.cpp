//----------------------------------------------------------------------------
Sphere Mgc::ContSphereOfAABB (int iQuantity, const Vector3* akPoint)
{
    Vector3 kMin = akPoint[0], kMax = kMin;
    for (int i = 1; i < iQuantity; i++)
    {
        if ( akPoint[i].x < kMin.x )
            kMin.x = akPoint[i].x;
        else if ( akPoint[i].x > kMax.x )
            kMax.x = akPoint[i].x;

        if ( akPoint[i].y < kMin.y )
            kMin.y = akPoint[i].y;
        else if ( akPoint[i].y > kMax.y )
            kMax.y = akPoint[i].y;

        if ( akPoint[i].z < kMin.z )
            kMin.z = akPoint[i].z;
        else if ( akPoint[i].z > kMax.z )
            kMax.z = akPoint[i].z;
    }

    Sphere kSphere;
    kSphere.Center() = 0.5f*(kMax + kMin);
    Vector3 kHalfDiagonal = 0.5f*(kMax - kMin);
    kSphere.Radius() = kHalfDiagonal.Length();

    return kSphere;
}