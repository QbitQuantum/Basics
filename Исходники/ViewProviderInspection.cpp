float calcArea (const SbVec3f& v1, const SbVec3f& v2, const SbVec3f& v3)
{
    SbVec3f a = v2-v1;
    SbVec3f b = v3-v1;
    return a.cross(b).length()/2.0f;
}