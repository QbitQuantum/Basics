void EMIHead::lookAt(bool entering, const Math::Vector3d &point, float rate, const Math::Matrix4 &matrix) {
	if (!_cost->_emiSkel || !_cost->_emiSkel->_obj)
		return;

	if (_jointName.empty())
		return;

	Joint *joint = _cost->_emiSkel->_obj->getJointNamed(_jointName);
	if (!joint)
		return;

	Math::Quaternion lookAtQuat; // Note: Identity if not looking at anything.

	if (entering) {
		Math::Matrix4 jointToWorld = _cost->getOwner()->getFinalMatrix() * joint->_finalMatrix;
		Math::Vector3d jointWorldPos = jointToWorld.getPosition();
		Math::Matrix4 worldToJoint = jointToWorld;
		worldToJoint.invertAffineOrthonormal();

		Math::Vector3d targetDir = (point + _offset) - jointWorldPos;
		targetDir.normalize();

		const Math::Vector3d worldUp(0, 1, 0);
		Math::Vector3d frontDir = Math::Vector3d(worldToJoint(0, 1), worldToJoint(1, 1), worldToJoint(2, 1)); // Look straight ahead. (+Y)
		Math::Vector3d modelFront(0, 0, 1);
		Math::Vector3d modelUp(0, 1, 0);

		joint->_absMatrix.inverseRotate(&modelFront);
		joint->_absMatrix.inverseRotate(&modelUp);

		// Generate a world-space look at matrix.
		Math::Matrix4 lookAtTM;
		lookAtTM.setToIdentity();

		if (Math::Vector3d::dotProduct(targetDir, worldUp) >= 0.98f) // Avoid singularity if trying to look straight up.
			lookAtTM.buildFromTargetDir(modelFront, targetDir, modelUp, -frontDir); // Instead of orienting head towards scene up, orient head towards character "back",
		else if (Math::Vector3d::dotProduct(targetDir, worldUp) <= -0.98f) // Avoid singularity if trying to look straight down.
			lookAtTM.buildFromTargetDir(modelFront, targetDir, modelUp, frontDir); // Instead of orienting head towards scene down, orient head towards character "front",
		else
			lookAtTM.buildFromTargetDir(modelFront, targetDir, modelUp, worldUp);

		// Convert from world-space to joint-space.
		lookAtTM = worldToJoint * lookAtTM;

		// Apply angle limits.
		Math::Angle p, y, r;
		lookAtTM.getXYZ(&y, &p, &r, Math::EO_ZXY);

		y.clampDegrees(_yawRange);
		p.clampDegrees(_minPitch, _maxPitch);
		r.clampDegrees(30.0f);

		lookAtTM.buildFromXYZ(y, p, r, Math::EO_ZXY);

		lookAtQuat.fromMatrix(lookAtTM.getRotation());
	}

	if (_headRot != lookAtQuat) {
		Math::Quaternion diff = _headRot.inverse() * lookAtQuat;
		float angle = 2 * acos(diff.w());
		if (diff.w() < 0.0f) {
			angle = 2 * (float)M_PI - angle;
		}

		float turnAmount = g_grim->getPerSecond(rate * ((float)M_PI / 180.0f));
		if (turnAmount < angle)
			_headRot = _headRot.slerpQuat(lookAtQuat, turnAmount / angle);
		else
			_headRot = lookAtQuat;
	}

	if (_headRot != Math::Quaternion()) { // If not identity..
		joint->_animMatrix = joint->_animMatrix * _headRot.toMatrix();
		joint->_animQuat = joint->_animQuat * _headRot;
		_cost->_emiSkel->_obj->commitAnim();
	}
}