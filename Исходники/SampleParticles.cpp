static PxQuat directionToQuaternion(const PxVec3& direction) 
{
    PxVec3 vUp(0.0f, 1.0f, 0.0f);
    PxVec3 vRight = vUp.cross(direction);
    vUp = direction.cross(vRight);

	PxQuat qrot(PxMat33(vRight, vUp, direction));
	qrot.normalize();

    return qrot;
}