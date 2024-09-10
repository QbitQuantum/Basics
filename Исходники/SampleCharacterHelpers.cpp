bool Character::faceToward(const PxVec3& targetDir, PxReal angleLimitPerFrame)
{
	PxVec3 oldDir = mCharacterPose.q.rotate(PxVec3(0,0,1));
	PxVec3 up(0,1,0);
	PxVec3 newDir = PxVec3(targetDir.x, 0, targetDir.z).getNormalized();
	PxVec3 right = -1.0f * oldDir.cross(up);

	PxReal cos = newDir.dot(oldDir);
	PxReal sin = newDir.dot(right);
	PxReal angle = atan2(sin, cos);

	PxReal limit = angleLimitPerFrame * (PxPi / 180.0f);
	if (angle > limit) angle = limit;
	else if (angle < -limit) angle = -limit;

	PxQuat qdel(angle, up);

	mCharacterPose.q = qdel * mCharacterPose.q;

	return true;
}