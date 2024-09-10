void
Turret::serverProcessFiring(DWORD in_currTime)
{
   if (!getControlClient() && getState () == StaticBase::Enabled && isActive()) {
      AssertFatal(m_pProjectile != NULL, "Must have projectile");

      if (m_pTarget == NULL) {
         // Lost our target, or player mount just ended...
         unshoot();
         return;
      }

      if (in_currTime >= m_beganState + data->firingTime) {
         // If the firing time runs out, we switch to reloading...
         unshoot();
         return;
      }
   
      float useRange = data->gunRange == -1 ? data->iRange : data->gunRange;
      float minDist  = useRange;
      if (isTargetable(m_pTarget, &minDist, useRange) == false) {
         unshoot();
         return;
      }

      // Guess we're still good, track the player...
      float interval = 0.032;
	   Vector3F rot = getAngulerPosition();
	   int aimed = 0;
	   float old_rot = turretRotation;
	   float increment = data->speed * interval;
	   float des_z;
	   Point3F playerPos;

	   float dist = m_distf (getBoxCenter(), m_pTarget->getLeadCenter());
	   leadPosition (m_pTarget->getLeadCenter(), m_pTarget->getLeadVelocity(), dist, &playerPos);

	   TMat3F invMat;
	   getNodeOffset (&invMat, "dummy muzzle", gunNode);
	   invMat.inverse();
	   m_mul (Point3F (playerPos.x, playerPos.y, playerPos.z), invMat, &playerPos);

	   des_z = rotation (-playerPos.x, -playerPos.y);
	   	
	   while (des_z < 0)
	   	des_z += (float)M_2PI;
	   	
	   while (des_z > M_2PI)
	   	des_z -= (float)M_2PI;
	   	
	   float diff = des_z - turretRotation;
	
	   if (diff > M_PI || diff < -M_PI)
	   	increment = -increment;
	   	
	   if (diff < increment && diff > -increment)
	   	{
	   		turretRotation = des_z;
	   		aimed += 1;
	   	}
	   else
	   	if (diff < 0)
	   		turretRotation -= increment;
	   	else
	   		turretRotation += increment;
	   		
	   wrapRotation ();
	   		
	   if (turretRotation != old_rot)
	   	setMaskBits (TRotationMask);
	
	   float old_elevation = turretElevation;
	   float des_y;
	
	   increment = data->speed * interval;
	   des_y = elevation (playerPos.x, playerPos.y, playerPos.z);
	   diff = des_y - turretElevation;
	
	   if (diff > M_PI || diff < -M_PI)
	   	increment = -increment;
	
	   if (diff < increment && diff > -increment)
	   	{
	   		turretElevation = des_y;
	   		aimed += 1;
	   	}
	   else
	   	if (diff < 0)
	   		turretElevation -= increment;
	   	else
	   		turretElevation += increment;
	   		
	   wrapElevation ();
	   		
	   if (old_elevation != turretElevation)
	   	setMaskBits (ElevationMask);
   }

   if (m_pProjectile)
      m_pProjectile->updateImageTransform(getEyeTransform());
}