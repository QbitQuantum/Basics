SE_Vector3f SE_SimObject::localToWorld(const SE_Vector3f& v)
{
    SE_Spatial* spatial = getSpatial();
    SE_Matrix4f worldTransform = spatial->getWorldTransform();
    SE_Vector4f v4(v, 1);
    v4 = worldTransform.mul(getLocalMatrix()).map(v4);
    return v4.xyz();
}