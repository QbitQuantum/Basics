void pWheel1::tick(bool handbrake, float motorTorque, float brakeTorque, float dt)
{

	if(getWheelFlag(WF_Accelerated)) 
	{
		if (handbrake && getWheelFlag(WF_AffectedByHandbrake)) 
		{
			// Handbrake, blocking!
		}
		else if (hasGroundContact()) 
		{
			// Touching, force applies
			NxVec3 steeringDirection;
			getSteeringDirection(steeringDirection);
			steeringDirection.normalize();
			NxReal localTorque = motorTorque;
			NxReal wheelForce = localTorque / _radius;
			steeringDirection *= wheelForce;
			wheelCapsule->getActor().addForceAtPos(steeringDirection, contactInfo->contactPosition);
			if(contactInfo->otherActor->isDynamic())
				contactInfo->otherActor->addForceAtPos(-steeringDirection, contactInfo->contactPosition);
		} 
	}

	NxReal OneMinusBreakPedal = 1-brakeTorque;

	/*
	if(handBrake && getWheelFlag(WF_AffectedByHandbrake)) 
	{
	material->setDynamicFrictionV(1);
	material->setStaticFrictionV(4);
	material->setDynamicFriction(0.4f);
	material->setStaticFriction(1.0f);
	} 
	else 
	{
	NxReal newv = OneMinusBreakPedal * _frictionToFront + brakeTorque;
	NxReal newv4= OneMinusBreakPedal * _frictionToFront + brakeTorque*4;
	material->setDynamicFrictionV(newv);
	material->setDynamicFriction(_frictionToSide);

	material->setStaticFrictionV(newv*4);
	material->setStaticFriction(2);
	}*/

	if(!hasGroundContact())
		updateContactPosition();
	updateAngularVelocity(dt, handbrake);

	contactInfo->reset();
}