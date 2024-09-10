void FollowCamera::update( Real time )
{
	if (!mGoalNode || !ca || !mCamera)  return;

	Vector3 posGoal = mGoalNode ? mGoalNode->getPosition() : Vector3::UNIT_Y;
	Quaternion orientGoal = mGoalNode ? mGoalNode->getOrientation() : Quaternion::IDENTITY;

	const static Quaternion  qO = Quaternion(Degree(180),Vector3::UNIT_Z) * Quaternion(Degree(-90),Vector3::UNIT_Y),
		qR = Quaternion(Degree(90),Vector3(0,1,0));
	Quaternion  orient = orientGoal * qO;
	Vector3  ofs = orient * ca->mOffset,  goalLook = posGoal + ofs;
	
    if (ca->mType == CAM_Car)	/* 3 Car - car pos & rot full */
    {
		mCamera->setPosition( goalLook );
		mCamera->setOrientation( orient );
		updInfo(time);
		return;
	}
    if (ca->mType == CAM_Follow)  ofs = ca->mOffset;
    
	Vector3  pos,goalPos;
	pos     = mCamera->getPosition() - ofs;
	goalPos = posGoal;
	
	Vector3  xyz;
	if (ca->mType != CAM_Arena)
	{
		Real x,y,z,xz;   // pitch & yaw to direction vector
		Real ap = ca->mPitch.valueRadians(), ay =  ca->mYaw.valueRadians();
		y = sin(ap), xz = cos(ap);
		x = sin(ay) * xz, z = cos(ay) * xz;
		xyz = Vector3(x,y,z);  xyz *= ca->mDist;
	}
	
	bool manualOrient = false;
	switch (ca->mType)
	{
		case CAM_Arena:		/* 2 Arena - free pos & rot */
		    goalPos = ca->mOffset - ofs;
		    break;
		    
		case CAM_Free:		/* 1 Free - free rot, pos from car */
			goalPos += xyz;
			break;
			
		case CAM_Follow:	/* 0 Follow - car rotY & pos from behind car, smooth */
		{	Quaternion  orient = orientGoal * qR;
			orient.FromAngleAxis(orient.getYaw(), Vector3::UNIT_Y);
			goalPos += orient * xyz;
		}	break;
		
		case CAM_ExtAng:    /* 4 Extended Angle - car in center, angle smooth */
		{	Quaternion  orient = orientGoal * qR;
			Quaternion  ory;  ory.FromAngleAxis(orient.getYaw(), Vector3::UNIT_Y);

			if (first)  {  qq = ory;  first = false;  }
			else  qq = orient.Slerp(ca->mSpeed * time, qq, ory, true);

			//  smooth dist from vel
			if (0)
			{
				if (first)  {  mPosNodeOld = posGoal;  }
				Real vel = (posGoal - mPosNodeOld).length() / std::max(0.001f, std::min(0.1f, time));
				mPosNodeOld = posGoal;
				if (first)  mVel = 0.f;  else
					mVel += (vel - mVel) * time * 8.f;  // par  vel smooth speed
				if (!first)
					xyz *= 1.f + std::min(100.f, mVel) * 0.01f;  // par  vel dist factor
			}

			Quaternion  qy = Quaternion(ca->mYaw,Vector3(0,1,0));
			goalPos += qq * (xyz + ca->mOffset);
			
			mCamera->setPosition( goalPos );
			mCamera->setOrientation( qq * qy * Quaternion(Degree(-ca->mPitch),Vector3(1,0,0)) );
			manualOrient = true;
		}	break;
	}

	if (!manualOrient)  // if !CAM_ExtAng
	{
		float dtmul = ca->mSpeed == 0 ? 1.0f : ca->mSpeed * time;

		if (ca->mType ==  CAM_Arena)
		{
			Vector3  Pos(0,0,0), goalPos = ca->mOffset;
			Pos = mCamera->getPosition();
			Pos += (goalPos - Pos) * dtmul;
			
			static Radian  pitch(0), yaw(0);
			pitch += (ca->mPitch - pitch) * dtmul;  yaw += (ca->mYaw - yaw) * dtmul;
			
			if (first)  {  Pos = goalPos;  pitch = ca->mPitch;  yaw = ca->mYaw;  first = false;  }
			mCamera->setPosition( Pos );
			mCamera->setOrientation(Quaternion::IDENTITY);
			mCamera->pitch(pitch);  mCamera->yaw(yaw);
			manualOrient = true;
		}
		else
		{
			if (first)  pos = goalPos;
			Vector3  addPos,addLook;
			addPos = (goalPos - pos).normalisedCopy() * (goalPos - pos).length() * dtmul;
			if (addPos.squaredLength() > (goalPos - pos).squaredLength())  addPos = goalPos - pos;
			pos += addPos;
			mCamera->setPosition( pos + ofs );
		
			if (mGoalNode)  goalLook = posGoal + ofs;
			if (first)	{	mLook = goalLook;  first = false;  }

			addLook = (goalLook - mLook) * dtmul;//Rot;
			mLook += addLook;
		}
	}

	/// cast ray from car to camera, to prevent objects blocking the camera's sight
    #ifdef CAM_BLT
	// update sphere pos
	btVector3 carPos = BtOgre::Convert::toBullet(posGoal);
	state->setWorldTransform( btTransform(btQuaternion(0,0,0,1), carPos ));
	
	// calculate origin & direction of the ray, convert to vdrift coordinates
	MATHVECTOR<float,3> origin;
	origin.Set( carPos.x(), carPos.y(), carPos.z() );
	MATHVECTOR<float,3> direction;
	btVector3 dir = BtOgre::Convert::toBullet(mCamera->getPosition()-posGoal);
	direction.Set(dir.x(), dir.y(), dir.z());
	Real distance = (mCamera->getPosition()-posGoal ).length();
	int pOnRoad;
	
	// shoot our ray
	COLLISION_CONTACT contact;
	mWorld->CastRay( origin, direction, distance, body, contact, &pOnRoad );
	
	if (contact.col != NULL)
	{
		LogO("Collision occured");
		// collision occured - update cam pos
		mCamera->setPosition( BtOgre::Convert::toOgre( btVector3(contact.GetPosition()[0], contact.GetPosition()[1], contact.GetPosition()[2]) ) );
	}
	#endif
	
	moveAboveTerrain();
	if (!manualOrient)
		mCamera->lookAt( mLook );
	updInfo(time);
}