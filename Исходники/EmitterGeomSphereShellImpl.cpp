void EmitterGeomSphereShellImpl::computeFillPositions(physx::Array<PxVec3>& positions,
        physx::Array<PxVec3>& velocities,
        const PxTransform& pose,
		const PxVec3& scale,
        float objRadius,
        PxBounds3& outBounds,
        QDSRand&) const
{
	PX_UNUSED(scale);

	const float bigRadius = *mRadius + *mShellThickness;
	const float radiusSquared = bigRadius * bigRadius;
	const float hemisphere = *mHemisphere;
	const float sphereCapBaseHeight = -bigRadius + 2 * bigRadius * hemisphere;
	const float sphereCapBaseRadius = PxSqrt(radiusSquared - sphereCapBaseHeight * sphereCapBaseHeight);
	const float horizontalExtents = hemisphere < 0.5f ? bigRadius : sphereCapBaseRadius;

	// we're not doing anything with the velocities array
	PX_UNUSED(velocities);

	// we don't want anything outside the emitter
	uint32_t numX = (uint32_t)PxFloor(horizontalExtents / objRadius);
	numX -= numX % 2;
	uint32_t numY = (uint32_t)PxFloor((bigRadius - sphereCapBaseHeight) / objRadius);
	numY -= numY % 2;
	uint32_t numZ = (uint32_t)PxFloor(horizontalExtents / objRadius);
	numZ -= numZ % 2;

	for (float x = -(numX * objRadius); x <= bigRadius - objRadius; x += 2 * objRadius)
	{
		for (float y = -(numY * objRadius); y <= bigRadius - objRadius; y += 2 * objRadius)
		{
			for (float z = -(numZ * objRadius); z <= bigRadius - objRadius; z += 2 * objRadius)
			{
				const float magnitudeSquare = PxVec3(x, y, z).magnitudeSquared();
				if ((magnitudeSquare > (*mRadius + objRadius) * (*mRadius + objRadius)) &&
				        (magnitudeSquare < (bigRadius - objRadius) * (bigRadius - objRadius)))
				{
					positions.pushBack(pose.transform(PxVec3(x, y, z)));
					outBounds.include(positions.back());
				}
			}
		}
	}
}