void myouse::MyouseListener::onOrientationData(myo::Myo * myo, uint64_t timestamp,
	const myo::Quaternion<float> & rotation)
{
	using std::atan2;
	using std::asin;
	using std::sin;

	double newRoll = atan2(2.0f * (rotation.w() * rotation.x() + rotation.y() * rotation.z()),
		1.0f - 2.0f * (rotation.x() * rotation.x() + rotation.y() * rotation.y()));
	double newPitch = asin(2.0f * (rotation.w() * rotation.y() - rotation.z() * rotation.x()));
	double newYaw = atan2(2.0f * (rotation.w() * rotation.z() + rotation.x() * rotation.y()),
		1.0f - 2.0f * (rotation.y() * rotation.y() + rotation.z() * rotation.z()));

	double roll = newRoll - rollOffset;
	double pitch = newPitch - pitchOffset;
	double yaw = newYaw - yawOffset;

	if (xDir == myo::xDirectionTowardElbow) pitch *= -1;

	if (isScrolling)
	{
		scroll(-pitch * SCROLL_SPEED);
	}
	else
	{
		int x = SCREEN_WIDTH * (0.5 - X_SPEED * yaw);
		int y = SCREEN_HEIGHT * (0.5 + Y_SPEED * pitch);

		bool dragging = leftDown || rightDown || middleDown;
		float dist = sqrt((x - lastX) * (x - lastX) + (y - lastY) * (y - lastY));

		if (!dragging || dist > DRAG_THRESHOLD)
		{
			moveMouse(x, y);

			lastX = x;
			lastY = y;
		}
	}

	rawRoll = newRoll;
	rawPitch = newPitch;
	rawYaw = newYaw;
}