void SharedMemoryTracker::updateOrientation()
{
	OutputDebugString("Motion Tracker updateOrientation\n");

	if(getOrientation(&yaw, &pitch, &roll) == 0)
	{
		yaw = fmodf(yaw + 360.0f, 360.0f);
		pitch = -fmodf(pitch + 360.0f, 360.0f);

		deltaYaw = yaw - currentYaw;
		deltaPitch = pitch - currentPitch;

		// hack to avoid errors while translating over 360/0
		if(fabs(deltaYaw) > 4.0f) deltaYaw = 0.0f;
		if(fabs(deltaPitch) > 4.0f) deltaPitch = 0.0f;

		mouseData.mi.dx = (long)(deltaYaw*multiplierYaw);
		mouseData.mi.dy = (long)(deltaPitch*multiplierPitch);
		
		OutputDebugString("Motion Tracker SendInput\n");
		SendInput(1, &mouseData, sizeof(INPUT));

		currentYaw = yaw;
		currentPitch = pitch;
		currentRoll = (float)( roll * (PI/180.0) * multiplierRoll);			// convert from deg to radians then apply mutiplier
	}
}