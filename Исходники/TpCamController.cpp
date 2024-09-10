void TpCamController::UpdateLocation()
{
	Vector3 targetPosition = Vector3::ZERO;
	Quaternion targetRotation = Quaternion::IDENTITY;

	if (WORLD->getPlayerAgent()->getID() > -1)
	{
		targetPosition = WORLD->getPlayerAgent()->GetPosition();
		if (aim)
		{
			targetRotation = WORLD->getPlayerAgent()->GetRotation();
		}
		else
		{
			targetRotation.FromAngleAxis(Radian(yaw), Vector3::UNIT_Y);
		}
	}

	//position
	Vector3 mPos =  targetPosition;
	mPos.y += 1.0;
	//float inc = GlobalVars::Tick * 4;
	//if (inc > 1)inc = 1;
	//rotation = Quaternion::Slerp(inc, rotation, targetRotation, true);
	rotation = targetRotation;
	
	if (aim && curCamOffset.squaredDistance(closeCamOffset) > 0.1)
	{
		Vector3 delta = closeCamOffset - curCamOffset;
		curCamOffset += delta * closeSpeed * GlobalVars::Tick;
	}
	else if (!aim && curCamOffset.squaredDistance(farCamOffset) > 0.1)
	{
		Vector3 delta = farCamOffset - curCamOffset;
		curCamOffset += delta * closeSpeed * GlobalVars::Tick;
	}

	Quaternion q;
	q.FromAngleAxis(Radian(pitch), Vector3::UNIT_X);
	Vector3 addPos = rotation * q * curCamOffset;
	Vector3 addPosNorm = addPos.normalisedCopy();
	Vector3 castPos = PHY->CastRay1(mPos, addPosNorm);
	float dist = castPos.distance(mPos);
	float skinWidth2 = 0.25;
	if (dist - skinWidth2 < addPos.length())
	{
		//keep y
		float ty = mPos.y + addPos.y;
		mPos += addPos.normalisedCopy() * (dist-skinWidth2);
		mPos.y = ty;
	}
	else
	{
		mPos += addPos;
	}

	mCamera->setPosition(mPos);

	//target
	Vector3 nDest;
	if (aim)
	{
		nDest = targetPosition + rotation * q * closeDestOffset;
	}
	else
	{
		nDest = targetPosition + rotation * q * farDestOffset;
	}
	mCamera->lookAt(nDest);
}