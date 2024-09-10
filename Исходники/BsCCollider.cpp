	void CCollider::updateTransform()
	{
		Vector3 myScale = SO()->getWorldScale();

		if (mParent != nullptr)
		{
			Vector3 parentPos = mParent->SO()->getWorldPosition();
			Quaternion parentRot = mParent->SO()->getWorldRotation();

			Vector3 myPos = SO()->getWorldPosition();
			Quaternion myRot = SO()->getWorldRotation();

			Vector3 scale = mParent->SO()->getWorldScale();
			Vector3 invScale = scale;
			if (invScale.x != 0) invScale.x = 1.0f / invScale.x;
			if (invScale.y != 0) invScale.y = 1.0f / invScale.y;
			if (invScale.z != 0) invScale.z = 1.0f / invScale.z;

			Quaternion invRotation = parentRot.inverse();

			Vector3 relativePos = invRotation.rotate(myPos - parentPos) *  invScale;
			Quaternion relativeRot = invRotation * myRot;

			relativePos = relativePos + myRot.rotate(mLocalPosition * scale);
			relativeRot = relativeRot * mLocalRotation;

			mInternal->setTransform(relativePos, relativeRot);
			mParent->_updateMassDistribution();
		}
		else
		{
			Quaternion myRot = SO()->getWorldRotation();
			Vector3 myPos = SO()->getWorldPosition() + myRot.rotate(mLocalPosition * myScale);
			myRot = myRot * mLocalRotation;

			mInternal->setTransform(myPos, myRot);
		}

		mInternal->setScale(myScale);
	}