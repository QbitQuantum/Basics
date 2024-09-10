//----------------------------------------------------------------------------
SEPlane3f::SEPlane3f(const SEVector3f& rNormal, const SEVector3f& rP0)
    : Normal(rNormal)
{
    Constant = rNormal.Dot(rP0);
}