Quaternion Deserializer::ReadPackedQuaternion()
{
    short coords[4];
    Quaternion ret;
    
    Read(&coords[0], sizeof coords);
    ret.w_ = coords[0] * invQ;
    ret.x_ = coords[1] * invQ;
    ret.y_ = coords[2] * invQ;
    ret.z_ = coords[3] * invQ;
    ret.Normalize();
    return ret;
}