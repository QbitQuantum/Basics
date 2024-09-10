bool ParticleEmitterPressure::stepEmissionSite(
	SiteData& siteData,
	ParticleData& spawnData,
	PxU32& spawnNum, 
	const PxU32 spawnMax,
	const PxVec3 &sitePos, 
	const PxVec3 &siteVel,
	const PxReal dt)
{
	PxReal maxDistanceMoved = 5.0f * mSpacingZ;	// don't generate long particle beams

	/**
	 * Find displacement vector of the particle's motion this frame
	 * this is not necessarily v*stepSize because a collision might have occured
	 */
	PxVec3 displacement = siteData.position - sitePos;
	PxVec3 normal = displacement;
	PxReal distanceMoved = normal.normalize();

	if (distanceMoved > maxDistanceMoved)
		distanceMoved = maxDistanceMoved;
	
	/**
	 * Place particles along line between emission point and new position
	 * starting backwards from the new position
	 * spacing between the particles is the rest spacing of the fluid 
	 */
	PxReal lastPlaced = 0.0f;
	while((lastPlaced + mSpacingZ) <= distanceMoved)
	{
		PxVec3 pos = sitePos + normal * (distanceMoved - (lastPlaced + mSpacingZ));

		PxVec3 posNoise;
		posNoise.x = randInRange(-mRandomPos.x, mRandomPos.x);
		posNoise.y = randInRange(-mRandomPos.y, mRandomPos.y);		
		
		pos += mAxisX*posNoise.x + mAxisY*posNoise.y;

		bool isSpawned = spawnParticle(spawnData, spawnNum, spawnMax, pos, siteVel);
		if(isSpawned)
		{
			updatePredecessor(siteData, pos, siteVel);
			lastPlaced += mSpacingZ;
		}
		else
		{
			return false;
		}
	}
	return true;
}