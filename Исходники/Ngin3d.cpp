void shNgin3dMove(float frontSpeed, float rightSpeed, float upSpeed, unsigned long dt)
{
	// cashed version of conversion of latitude and longitude to points already exist in _Ngin3d_cameraTarget and _Ngin3d_cameraUp
	float targetDir[3] = {_Ngin3d_cameraTarget[0]-_Ngin3d_cameraPosition[0], _Ngin3d_cameraTarget[1]-_Ngin3d_cameraPosition[1], _Ngin3d_cameraTarget[2]-_Ngin3d_cameraPosition[2]};
	float rightDir[3] = {CROSS(targetDir, _Ngin3d_cameraUp)};		// targetDir and _Ngin3d_cameraUp should already be normalized
	float upDir[3] = {0, 1, 0};
	if (g_Ngin3d_uprightMode)
	{
		if (_Ngin3d_cameraUp[1] < 0)
			upDir[1] = -1;
	}
	else
	{
		upDir[0] = _Ngin3d_cameraUp[0];
		upDir[1] = _Ngin3d_cameraUp[1];
		upDir[2] = _Ngin3d_cameraUp[2];
	}
	float speed[3] = {frontSpeed*targetDir[0]+upSpeed*upDir[0]+rightSpeed*rightDir[0],
			frontSpeed*targetDir[1]+upSpeed*upDir[1]+rightSpeed*rightDir[1],
			frontSpeed*targetDir[2]+upSpeed*upDir[2]+rightSpeed*rightDir[2]};
	float gravity[3] = {g_Ngin3d_settings[NGIN3D_GRAVITY_X], g_Ngin3d_settings[NGIN3D_GRAVITY_Y], g_Ngin3d_settings[NGIN3D_GRAVITY_Z]};
	float normGravity = NORM(gravity);
	if (g_Ngin3d_uprightMode && !STATE_IN_AIR && normGravity > EPSILON)
	{
		float speedInDirectionOfGravity = DOT(speed, gravity)/normGravity/normGravity;
		speed[0] -= gravity[0]*speedInDirectionOfGravity;
		speed[1] -= gravity[1]*speedInDirectionOfGravity;
		speed[2] -= gravity[2]*speedInDirectionOfGravity;
	}
	shNgin3dCollisionResult cr = g_Ngin3d_player.shNgin3dPOUpdate(dt, speed);
	if (cr == NGIN3D_COLLISION_WITH_GROUND)
	{
		STATE_IN_AIR = false;
	}
	float cameraDisplacement[3] = {0, 0, 0};
	if (g_Ngin3d_uprightMode)
	{
		if (STATE_CROUCHED)
			cameraDisplacement[1] = g_Ngin3d_settings[NGIN3D_CROUCHED_HEIGHT];
		else
			cameraDisplacement[1] = g_Ngin3d_settings[NGIN3D_HEIGHT];
	}
	_Ngin3d_cameraPosition[0] = g_Ngin3d_player.position[0]+cameraDisplacement[0];
	_Ngin3d_cameraPosition[1] = g_Ngin3d_player.position[1]+cameraDisplacement[1];
	_Ngin3d_cameraPosition[2] = g_Ngin3d_player.position[2]+cameraDisplacement[2];
	_Ngin3d_cameraTarget[0] = _Ngin3d_cameraPosition[0]+targetDir[0];
	_Ngin3d_cameraTarget[1] = _Ngin3d_cameraPosition[1]+targetDir[1];
	_Ngin3d_cameraTarget[2] = _Ngin3d_cameraPosition[2]+targetDir[2];
	(*_Ngin3d_cameraPositionFunction)(_Ngin3d_cameraPosition);
	(*_Ngin3d_cameraTargetFunction)(_Ngin3d_cameraTarget);
}