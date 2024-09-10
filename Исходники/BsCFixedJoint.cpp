	void CFixedJoint::getLocalTransform(JointBody body, Vector3& position, Quaternion& rotation)
	{
		position = mPositions[(int)body];
		rotation = mRotations[(int)body];

		HRigidbody rigidbody = mBodies[(int)body];
		if (rigidbody == nullptr) // Get world space transform if no relative to any body
		{
			Quaternion worldRot = SO()->getWorldRotation();

			rotation = worldRot*rotation;
			position = worldRot.rotate(position) + SO()->getWorldPosition();
		}
		else
		{
			// Find world space transform
			Quaternion worldRot = rigidbody->SO()->getWorldRotation();

			rotation = worldRot * rotation;
			position = worldRot.rotate(position) + rigidbody->SO()->getWorldPosition();

			// Get transform of the joint local to the object
			Quaternion invRotation = rotation.inverse();

			position = invRotation.rotate(SO()->getWorldPosition() - position);
			rotation = invRotation * SO()->getWorldRotation();
		}
	}