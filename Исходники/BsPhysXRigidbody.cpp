void PhysXRigidbody::addForceAtPoint(const Vector3& force, const Vector3& position, PointForceMode mode)
{
    const PxVec3& pxForce = toPxVector(force);
    const PxVec3& pxPos = toPxVector(position);

    const PxTransform globalPose = mInternal->getGlobalPose();
    PxVec3 centerOfMass = globalPose.transform(mInternal->getCMassLocalPose().p);

    PxForceMode::Enum pxMode = toPxForceMode(mode);

    PxVec3 torque = (pxPos - centerOfMass).cross(pxForce);
    mInternal->addForce(pxForce, pxMode);
    mInternal->addTorque(torque, pxMode);
}