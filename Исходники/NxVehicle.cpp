void NxVehicle::updateVehicle(NxReal lastTimeStepSize)
{
	//printf("updating %x\n", this);
	
	NxReal distanceSteeringAxisCarTurnAxis = _steeringSteerPoint.x  - _steeringTurnPoint.x;
	NX_ASSERT(_steeringSteerPoint.z == _steeringTurnPoint.z);
	NxReal distance2 = 0;
	if (NxMath::abs(_steeringWheelState) > 0.01f)
		distance2 = distanceSteeringAxisCarTurnAxis / NxMath::tan(_steeringWheelState * _steeringMaxAngleRad);

	//printf("d1 = %2.3f, d2 = %2.3f, a1 = %2.3f, a2 = %2.3f\n",
	//	distanceSteeringAxisCarTurnAxis, distance2,
	//	_steeringWheelState, _steeringWheelState * _steeringMaxAngleRad);


	_lastTrailTime += lastTimeStepSize;

	if(_lastTrailTime > TRAIL_FREQUENCY)
	{
		_lastTrailTime = 0.0f;
	}

	NxU32 nbTouching = 0;
	NxU32 nbNotTouching = 0;
	NxU32 nbHandBrake = 0;
	for(NxU32 i = 0; i < _wheels.size(); i++)
	{
		NxWheel* wheel = _wheels[i];

		if (_lastTrailTime  == 0.0f)
		{
			if(_wheels[i]->hasGroundContact())
			{
				if (++_nextTrailSlot >= NUM_TRAIL_POINTS)
					_nextTrailSlot = 0;
				_trailBuffer[_nextTrailSlot] = _bodyActor->getGlobalPose() * _wheels[i]->getGroundContactPos();
			}
		}

		if(wheel->getWheelFlag(NX_WF_STEERABLE_INPUT))
		{
			if(distance2 != 0)
			{
				NxReal xPos = wheel->getWheelPos().x;
				NxReal zPos = wheel->getWheelPos().z;
				NxReal dz = -zPos + distance2;
				NxReal dx = xPos - _steeringTurnPoint.x;
				wheel->setAngle(NxMath::atan(dx/dz));
			} else {
				wheel->setAngle(0.f);
			}
			//printf("%2.3f\n", wheel->getAngle());

		} else if(wheel->getWheelFlag(NX_WF_STEERABLE_AUTO))
			{
			NxVec3 localVelocity = _bodyActor->getLocalPointVelocity(wheel->getWheelPos());
			NxQuat local2Global = _bodyActor->getGlobalOrientationQuat();
			local2Global.inverseRotate(localVelocity);
//			printf("%2.3f %2.3f %2.3f\n", wheel->getWheelPos().x,wheel->getWheelPos().y,wheel->getWheelPos().z);
			localVelocity.y = 0;
			if(localVelocity.magnitudeSquared() < 0.01f)
			{
				wheel->setAngle(0.0f);
			} else {
				localVelocity.normalize();
//				printf("localVelocity: %2.3f %2.3f\n", localVelocity.x, localVelocity.z);
				if(localVelocity.x < 0)
					localVelocity = -localVelocity;
				NxReal angle = NxMath::clamp((NxReal)atan(localVelocity.z / localVelocity.x), 0.3f, -0.3f);
				wheel->setAngle(angle);
			}
		}

		// now the acceleration part
		if(!wheel->getWheelFlag(NX_WF_ACCELERATED))
			continue;

		if(_handBrake && wheel->getWheelFlag(NX_WF_AFFECTED_BY_HANDBRAKE))
		{
			nbHandBrake++;
		} else {
			if (!wheel->hasGroundContact())
			{
				nbNotTouching++;
			} else {
				nbTouching++;
			}
		}
	}
	
	NxReal motorTorque = 0.0f; 
	if(nbTouching && NxMath::abs(_accelerationPedal) > 0.01f) 
	{
		NxReal axisTorque = _computeAxisTorque();
		NxReal wheelTorque = axisTorque / (NxReal)(_wheels.size() - nbHandBrake);
		NxReal wheelTorqueNotTouching = nbNotTouching>0?wheelTorque*(NxMath::pow(0.5f, (NxReal)nbNotTouching)):0;
		NxReal wheelTorqueTouching = wheelTorque - wheelTorqueNotTouching;
		motorTorque = wheelTorqueTouching / (NxReal)nbTouching; 
	} else {
		_updateRpms();
	}
//printf("wt: %f %f\n", motorTorque, _brakePedal);
	for(NxU32 i = 0; i < _wheels.size(); i++) 
	{
		NxWheel* wheel = _wheels[i];
		wheel->tick(_handBrake, motorTorque, _brakePedal, lastTimeStepSize);
	}

	//printf("---\n");
}