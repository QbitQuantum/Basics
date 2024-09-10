// updates the internals of a mapped particle
void CMappedParticle::Update( float flTimeSinceLastDraw )
{
	flParticleTime += flTimeSinceLastDraw;

	// limit to at least 1 sort per second as 0 sorts can cause problems 
	if (g_ParticleSorts->value == 0)
		g_ParticleSorts->value = 1;

	// update distance between particle and player g_ParticleSorts times a second
	float flTimeSinceLastSort = (gEngfuncs.GetClientTime() - sParticle.flLastSort);
	if(flTimeSinceLastSort == 0 || (((int)(1 / flTimeSinceLastSort)) < g_ParticleSorts->value))
	{
		// update lightlevel everytime we sort
		//	if (pSys->iParticleLightCheck == NO_CHECK)

		if (pSys->iParticleLightCheck == CHECK_EVERY_SORT)
		{
			// great thanks go to Sneaky_Bastard and randomnine for helping me alot to finding 
			// this great method of obtaining lightlevel on the clientside
			
			// create temporary entity to get illumination from it
			alight_t lighting;
			cl_entity_t *LightEntity;
			vec3_t dir;

			// bogus data as valve calls it :)
			LightEntity = gEngfuncs.GetLocalPlayer();

			if ( !LightEntity )
				return;

			// move it in the particles location
			LightEntity->origin = sParticle.vPosition;
			
			// I have no idea what this does but if you don't do it -> crash
			lighting.plightvec = dir;

			IEngineStudio.StudioDynamicLight(LightEntity, &lighting );
			IEngineStudio.StudioSetupLighting (&lighting);
			IEngineStudio.StudioEntityLight( &lighting );

			sParticle.iRed = (int)(lighting.color[0] * lighting.shadelight );
			sParticle.iGreen = (int)(lighting.color[1] * lighting.shadelight );
			sParticle.iBlue = (int)(lighting.color[2] * lighting.shadelight );
		}
	}

	// dont draw the particle if smoke is enabled and its close to the player
	if (pSys->bSmoke == true)
	{
		if (sParticle.flSquareDistanceToPlayer < (PARTICLE_THRESHOLD_START*PARTICLE_THRESHOLD_START))
			bIgnoreParticle = true;
		else
			bIgnoreParticle = false;
	}

	if (pSys->iParticleAlign == NO_ALIGN)
	{
		vNormal.x += flTimeSinceLastDraw * (pSys->vRotationVel.x + vRotationVelVar.x);
		vNormal.y += flTimeSinceLastDraw * (pSys->vRotationVel.y + vRotationVelVar.y);
		vNormal.z += flTimeSinceLastDraw * (pSys->vRotationVel.z + vRotationVelVar.z);
		
		while (vNormal.x > 360)
			vNormal.x -= 360;
		while (vNormal.y > 360)
			vNormal.y -= 360;
		while (vNormal.z > 360)
			vNormal.z -= 360;
	}	
	
	// if we're using a custom mode for displaying our texture
	if (pSys->iFPS != 0) {
		if (pSys->iAnimSpeed == CUSTOM) {
			if (pSys->iAnimBehaviour == LOOP) {
				while (flParticleTime > (1.0f / pSys->iFPS)) {
					iCurrentFrame++;
					flParticleTime -= (1.0f / pSys->iFPS);
				}

				if (iCurrentFrame > (pSys->iEndingFrame - 1))
					iCurrentFrame = (pSys->iStartingFrame - 1);

			} else if (pSys->iAnimBehaviour == REVERSE_LOOP) {
				bool bCountUp = true;

				if (iCurrentFrame >= (pSys->iEndingFrame - 1))
					bCountUp = false;
				if (iCurrentFrame <= (pSys->iStartingFrame - 1))
					bCountUp = true;

				while (flParticleTime > (1.0f / pSys->iFPS))
				{
					if (bCountUp == true)
						iCurrentFrame++;
					else
						iCurrentFrame--;

					flParticleTime -= (1.0f / pSys->iFPS);
				}
			} else { // once_through
				while (flParticleTime > (1.0f / pSys->iFPS))
				{
					iCurrentFrame++;
					flParticleTime -= (1.0f / pSys->iFPS);
				}
				if (iCurrentFrame > (pSys->iEndingFrame - 1))
					iCurrentFrame = (pSys->iEndingFrame - 1);
			}
		}
	}


	if (pSys->iAnimSpeed == START_FAST_END_SLOW)
		iCurrentFrame = pSys->iEndingFrame * (1 - exp(-3*sParticle.flAge));

	if (pSys->iAnimSpeed == ANIMATE_OVER_LIFE && sParticle.flMaxAge)
		iCurrentFrame = (pSys->iEndingFrame) * (sParticle.flAge / sParticle.flMaxAge);
	
	if (flTimeSinceLastDraw < 0) // how the hell can the time between updates be less than nothing?
		flTimeSinceLastDraw = -flTimeSinceLastDraw;

	if (pSys->flVelocityDampening > 0.01) {
		sParticle.vVelocity.x *= ( 1 / ( 1 + fabsf(pSys->flVelocityDampening * flTimeSinceLastDraw * sParticle.vVelocity.x)));
		sParticle.vVelocity.y *= ( 1 / ( 1 + fabsf(pSys->flVelocityDampening * flTimeSinceLastDraw * sParticle.vVelocity.y)));
		sParticle.vVelocity.z *= ( 1 / ( 1 + fabsf(pSys->flVelocityDampening * flTimeSinceLastDraw * sParticle.vVelocity.z)));
	}
	
	sParticle.vVelocity.z -= pSys->flGravity * flTimeSinceLastDraw;

	if (pSys->bWindy) {
		sParticle.vVelocity.x += (sParticle.vWind.x * flTimeSinceLastDraw);
		sParticle.vVelocity.y += (sParticle.vWind.y * flTimeSinceLastDraw);
		sParticle.vVelocity.z += (sParticle.vWind.z * flTimeSinceLastDraw);
	}
	
	VectorMA( sParticle.vPosition, (60.0 * flTimeSinceLastDraw), sParticle.vVelocity, sParticle.vPosition );
	
	sParticle.flSize += flTimeSinceLastDraw * sParticle.flGrowth;
	sParticle.flCurrentRotation += flTimeSinceLastDraw * sParticle.flRotation;
	while (sParticle.flCurrentRotation > 360) {
		sParticle.flCurrentRotation -= 360;
	}
 	
	sParticle.flAge += flTimeSinceLastDraw;
}