void pWheel2::_updateVirtoolsEntity(bool position,bool rotation)
{

	CK3dEntity *ent  = static_cast<CK3dEntity*>(GetPMan()->GetContext()->GetObject(getEntID()));
	if (ent && position) 
	{

		NxWheelShape *wShape = getWheelShape();
		NxMat34 pose = wShape->getGlobalPose();
		NxWheelContactData wcd; 
		NxShape* contactShape = wShape->getContact(wcd);
		NxVec3 suspensionOffsetDirection;
		pose.M.getColumn(1, suspensionOffsetDirection);
		suspensionOffsetDirection =-suspensionOffsetDirection;

		if (contactShape && wcd.contactForce > -1000)
		{
			NxVec3 toContact = wcd.contactPoint - pose.t;
			double alongLength = suspensionOffsetDirection.dot(toContact);
			NxVec3 across = toContact - alongLength * suspensionOffsetDirection;
			double r = wShape->getRadius();
			double pullBack = sqrt(r*r - across.dot(across));
			pose.t += (alongLength - pullBack) * suspensionOffsetDirection;
		} else {
			pose.t += wShape->getSuspensionTravel() * suspensionOffsetDirection;
		}

		VxVector oPos  = getFrom(pose.t);
		ent->SetPosition(&oPos);

		if (hasGroundContact())
		{

			NxWheelShape *wShape = getWheelShape();
			NxMat34& wheelPose = wShape->getGlobalPose();

/*			NxWheelContactData wcd;
			NxShape* cShape = wShape->getContact(wcd);	
			NxReal  stravel = wShape->getSuspensionTravel();
			NxReal radius = wShape->getRadius();

			VxVector gPos  = getFrom(getWheelPose().t);

			/*
			if( cShape && wcd.contactPosition <=  (stravel + radius) ) 
			{
			}*/

			//////////////////////////////////////////////////////////////////////////

			/*VxVector gPos  = getFrom(getWheelPose().t);
			//gPos*=-1.0f;
			gPos -=getWheelPos();
			V	3.
				xVector gPos2  = getFrom(getWheelShape()->getLocalPose().t);
			ent->SetPosition(&gPos2,getBody()->GetVT3DObject());
			*/
		}else
		{
//			VxVector gPos  = getWheelPos();
//			ent->SetPosition(&gPos,getBody()->GetVT3DObject());
		}
	}
	if (ent && rotation)
	{


		//float rollAngle = getWheelRollAngle();
		//rollAngle+=wShape->getAxleSpeed() * (dt* 0.01f);
        
		VxQuaternion rot  = pMath::getFrom( getWheelPose().M );
		ent->SetQuaternion(&rot,NULL);
	}


	/*



	NxWheelShape *wShape = getWheelShape();

	


	while (rollAngle > NxTwoPi)	//normally just 1x
	rollAngle-= NxTwoPi;
	while (rollAngle< -NxTwoPi)	//normally just 1x
	rollAngle+= NxTwoPi;

	setWheelRollAngle(rollAngle);


	NxMat34& wheelPose = wShape->getGlobalPose();

	NxWheelContactData wcd;
	NxShape* cShape = wShape->getContact(wcd);	
	NxReal  stravel = wShape->getSuspensionTravel();
	NxReal radius = wShape->getRadius();


	//have ground contact?
	if( cShape && wcd.contactPosition <=  (stravel + radius) ) {
	wheelPose.t = NxVec3( wheelPose.t.x, wcd.contactPoint.y + getRadius(), wheelPose.t.z );
	}
	else {
	wheelPose.t = NxVec3( wheelPose.t.x, wheelPose.t.y - getSuspensionTravel(), wheelPose.t.z );
	}

	float rAngle = rollAngle;
	float steer = wShape->getSteerAngle();

	NxMat33 rot, axisRot, rollRot;
	rot.rotY( wShape->getSteerAngle() );
	axisRot.rotY(0);
	rollRot.rotX(rollAngle);
	wheelPose.M = rot * wheelPose.M * axisRot * rollRot;
	setWheelPose(wheelPose);

	*/
}