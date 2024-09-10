float3 EC_WaterPlane::GetPointOnPlane(const float3 &point) const 
{
    if (node_ == 0)
        return float3::nan;

    Ogre::Quaternion rot = node_->_getDerivedOrientation();
    Ogre::Vector3 trans = node_->_getDerivedPosition();
    Ogre::Vector3 scale = node_->_getDerivedScale();

    Ogre::Matrix4 worldTM;
    worldTM.makeTransform(trans, scale, rot);

    // In Ogre 1.7.1 we could simply use the following line, but since we're also supporting Ogre 1.6.4 for now, the above
    // lines are used instead, which work in both.
    // Ogre::Matrix4 worldTM = node_->_getFullTransform(); // local->world. 

    Ogre::Matrix4 inv = worldTM.inverse(); // world->local
    Ogre::Vector4 local = inv * Ogre::Vector4(point.x, point.y, point.z, 1.f);
 
    local.y = 0;
    Ogre::Vector4 world = worldTM * local;
    return float3(world.x, world.y, world.z);
}