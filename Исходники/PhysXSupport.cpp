void AddRadialForceToPxRigidBody_AssumesLocked(PxRigidBody& PRigidBody, const FVector& Origin, float Radius, float Strength, uint8 Falloff, bool bAccelChange)
{
#if WITH_PHYSX
	if (!(PRigidBody.getRigidBodyFlags() & PxRigidBodyFlag::eKINEMATIC))
	{
		float Mass = PRigidBody.getMass();
		PxTransform PCOMTransform = PRigidBody.getGlobalPose().transform(PRigidBody.getCMassLocalPose());
		PxVec3 PCOMPos = PCOMTransform.p; // center of mass in world space
		PxVec3 POrigin = U2PVector(Origin); // origin of radial impulse, in world space
		PxVec3 PDelta = PCOMPos - POrigin; // vector from

		float Mag = PDelta.magnitude(); // Distance from COM to origin, in Unreal scale : @todo: do we still need conversion scale?

		// If COM is outside radius, do nothing.
		if (Mag > Radius)
		{
			return;
		}

		PDelta.normalize();

		// If using linear falloff, scale with distance.
		float ForceMag = Strength;
		if (Falloff == RIF_Linear)
		{
			ForceMag *= (1.0f - (Mag / Radius));
		}

		// Apply force
		PxVec3 PImpulse = PDelta * ForceMag;
		PRigidBody.addForce(PImpulse, bAccelChange ? PxForceMode::eACCELERATION : PxForceMode::eFORCE);
	}
#endif // WITH_PHYSX
}