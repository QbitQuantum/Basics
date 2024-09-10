Matrix3 plMaxNodeBase::GetWorldToLocal(TimeValue t)
{
    Matrix3 l2w = GetLocalToWorld(t);
    Matrix3 w2l = Inverse(l2w);
    return w2l;
}