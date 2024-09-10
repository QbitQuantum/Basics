bool
XipGeomUtils::isInside(const SbVec3f &u, const SbMatrix &model)
{
    SbMatrix inv = model.inverse();

    SbVec3f v;

    inv.multVecMatrix(u, v);

    if ( v[0]<0.0f || v[1]<0.0f || v[2]<0.0f ) return false;

    if ( v[0]>1.0f || v[1]>1.0f || v[2]>1.0f ) return false;

    return true;
}