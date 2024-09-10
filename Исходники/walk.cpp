void Walk::onGameLoop() {
	if (!_path->hasSteps()) {
		// There is no path to the destination
		stop();
		return;
	}

	Resources::Floor *floor = StarkGlobal->getCurrent()->getFloor();

	// Get the target to walk to
	Math::Vector3d currentPosition = _item3D->getPosition3D();
	Math::Vector3d target = _path->computeWalkTarget(currentPosition);

	// Compute the direction to walk into
	Math::Vector3d direction = target - currentPosition;
	direction.z() = 0;
	direction.normalize();

	// Compute the angle with the current character direction
	Math::Vector3d currentDirection = _item3D->getDirectionVector();
	float directionDeltaAngle = computeAngleBetweenVectorsXYPlane(currentDirection, direction);

	// If the angle between the current direction and the new one is too high,
	// make the character turn on itself until the angle is low enough
	if (ABS(directionDeltaAngle) > getAngularSpeed() + 0.1f) {
		_turnDirection = directionDeltaAngle < 0 ? kTurnLeft : kTurnRight;
	} else {
		_turnDirection = kTurnNone;
	}

	float distancePerGameloop = computeDistancePerGameLoop();

	Math::Vector3d newPosition;
	if (_turnDirection == kTurnNone) {
		// Compute the new position using the distance per gameloop
		if (currentPosition.getDistanceTo(target) > distancePerGameloop) {
			newPosition = currentPosition + direction * distancePerGameloop;
		} else {
			newPosition = target;
		}
	} else {
		// The character does not change position when it is turning
		newPosition = currentPosition;
		direction = currentDirection;

		Math::Matrix3 rot;
		rot.buildAroundZ(_turnDirection == kTurnLeft ? -getAngularSpeed() : getAngularSpeed());
		rot.transformVector(&direction);
	}

	// Some scripts expect the character position to be the exact destination
	if (newPosition == _destination) {
		_reachedDestination = true;
		stop();
	}

	// Update the new position's height according to the floor
	int32 newFloorFaceIndex = floor->findFaceContainingPoint(newPosition);
	if (newFloorFaceIndex >= 0) {
		floor->computePointHeightInFace(newPosition, newFloorFaceIndex);
	} else {
		warning("Item %s is walking off the floor", _item->getName().c_str());
	}

	// Update the item's properties
	_item3D->setPosition3D(newPosition);
	if (direction.getMagnitude() != 0.0) {
		_item3D->setDirection(computeAngleBetweenVectorsXYPlane(direction, Math::Vector3d(1.0, 0.0, 0.0)));
	}
	if (newFloorFaceIndex >= 0) {
		// When unable to find the face containing the new position, keep the previous one
		// to prevent draw order glitches.
		_item3D->setFloorFaceIndex(newFloorFaceIndex);
	}

	changeItemAnim();
}