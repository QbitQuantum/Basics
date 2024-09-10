void Physics3DComponent::syncPhysicsToNode()
{
    if (_physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::RIGID_BODY
     || _physics3DObj->getObjType() == Physics3DObject::PhysicsObjType::COLLIDER)
    {
        Mat4 parentMat;
        if (_owner->getParent())
            parentMat = _owner->getParent()->getNodeToWorldTransform();
        
        auto mat = parentMat.getInversed() * _physics3DObj->getWorldTransform();
        //remove scale, no scale support for physics
        float oneOverLen = 1.f / sqrtf(mat.m[0] * mat.m[0] + mat.m[1] * mat.m[1] + mat.m[2] * mat.m[2]);
        mat.m[0] *= oneOverLen;
        mat.m[1] *= oneOverLen;
        mat.m[2] *= oneOverLen;
        oneOverLen = 1.f / sqrtf(mat.m[4] * mat.m[4] + mat.m[5] * mat.m[5] + mat.m[6] * mat.m[6]);
        mat.m[4] *= oneOverLen;
        mat.m[5] *= oneOverLen;
        mat.m[6] *= oneOverLen;
        oneOverLen = 1.f / sqrtf(mat.m[8] * mat.m[8] + mat.m[9] * mat.m[9] + mat.m[10] * mat.m[10]);
        mat.m[8] *= oneOverLen;
        mat.m[9] *= oneOverLen;
        mat.m[10] *= oneOverLen;
        
        mat *= _transformInPhysics;
        static Vec3 scale, translation;
        static Quaternion quat;
        mat.decompose(&scale, &quat, &translation);
        _owner->setPosition3D(translation);
        quat.normalize();
        _owner->setRotationQuat(quat);
    }
}