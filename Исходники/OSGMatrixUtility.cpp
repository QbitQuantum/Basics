OSG_BASE_DLLMAPPING bool MatrixLookAt(OSG::Matrix &result,
                                      OSG::Real32  fromx,
                                      OSG::Real32  fromy,
                                      OSG::Real32  fromz,
                                      OSG::Real32  atx,
                                      OSG::Real32  aty,
                                      OSG::Real32  atz,
                                      OSG::Real32  upx,
                                      OSG::Real32  upy,
                                      OSG::Real32  upz)
{
    Vec3f view;
    Vec3f right;
    Vec3f newup;
    Vec3f up;

    view.setValues(fromx - atx , fromy - aty, fromz - atz);
    view.normalize();

    up.setValues(upx, upy, upz);

    right = up.cross(view);

    if(right.dot(right) < TypeTraits<Real32>::getDefaultEps())
    {
        return true;
    }

    right.normalize();

    newup = view.cross(right);

    result.setIdentity ();
    result.setTranslate(fromx, fromy, fromz);

    Matrix tmpm;

    tmpm.setValue(right, newup, view);

    result.mult(tmpm);

    return false;
}