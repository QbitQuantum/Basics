void RacketPhysics::testCollisionWithBall()
{
	if (timeSinceLastHit < 0.5f)
		return;
	Ogre::Vector3 racketNormal = Ogre::Vector3::UNIT_Y;
	racketNormal = ori * racketNormal;
	Ogre::Vector3 ballPos = ball->getPosition();
	Ogre::Plane racketPlane(racketNormal, pos);
	float distanceFromPlane = racketPlane.getDistance(ballPos);
	if (distanceFromPlane < 0.0f)
	{
		racketNormal = -racketNormal;
		distanceFromPlane = -distanceFromPlane;
	}
	//if (distanceFromPlane < g_RacketThickness + g_BallRadius)
	if (distanceFromPlane < 0.03f)
	{
		Ogre::Vector3 distanceVector = racketNormal * distanceFromPlane;
		Ogre::Vector3 nearestPointOnPlane = ballPos - distanceVector;
		Ogre::Vector3 distanceOnPlane = nearestPointOnPlane - pos;
		//odprintf("dist before: %f, %f, %f", distanceOnPlane.x, distanceOnPlane.y, distanceOnPlane.z);
		distanceOnPlane.z *= 0.5f;
		distanceOnPlane.y *= 0.5f;
		//odprintf("dist after: %f, %f, %f", distanceOnPlane.x, distanceOnPlane.y, distanceOnPlane.z);
		float projectedDistance = distanceOnPlane.length();
		//odprintf("dist sum: %f", projectedDistance);
		//if (projectedDistance < g_RacketRadiusB)
		if (projectedDistance < 0.3f)
		{
			odprintf("HIT, time sinc last hit: %f", timeSinceLastHit);
			timeSinceLastHit = 0;
			// Collision
			ballPos += distanceVector * (0.03f/abs(distanceFromPlane));
			ball->setPosition(ballPos);
			Ogre::Vector3 ballSpeed = ball->getSpeed();
			ballSpeed = ballSpeed.reflect(racketNormal);
			// Perpendicular element, used for spin
			Ogre::Vector3 speedPerp = racketPlane.projectVector(speed);
			ball->setSpin(speedPerp.crossProduct(racketNormal));
			// Parallel element, used for speed
			Ogre::Vector3 speedPara = speed - speedPerp;
			ballSpeed += speedPara * g_HitStrength;
			ball->setSpeed(ballSpeed);
			gameLogic->onTouchRacket(playerId);
		}
		else
		{
			//odprintf("no hit, time sinc last hit: %f", timeSinceLastHit);
		}
	}

}