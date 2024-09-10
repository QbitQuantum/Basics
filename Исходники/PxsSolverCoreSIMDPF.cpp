void solveContactCoulomb_BStatic(const PxcSolverConstraintDesc& desc, PxcSolverContext& /*cache*/)
{
	PxcSolverBody& b0 = *desc.bodyA;


	Vec3V linVel0 = V3LoadA(b0.linearVelocity);
	Vec3V angVel0 = V3LoadA(b0.angularVelocity);

	PxcSolverContactCoulombHeader* firstHeader = (PxcSolverContactCoulombHeader*)desc.constraint;
	const PxU8* PX_RESTRICT last = desc.constraint + firstHeader->frictionOffset;//getConstraintLength(desc);

	//hopefully pointer aliasing doesn't bite.
	const PxU8* PX_RESTRICT currPtr = desc.constraint;

	const FloatV zero = FZero();

	while(currPtr < last)
	{
		PxcSolverContactCoulombHeader* PX_RESTRICT hdr = (PxcSolverContactCoulombHeader*)currPtr;
		currPtr += sizeof(PxcSolverContactCoulombHeader);

		const PxU32 numNormalConstr = hdr->numNormalConstr;

		PxcSolverContact* PX_RESTRICT contacts = (PxcSolverContact*)currPtr;
		Ps::prefetchLine(contacts);
		currPtr += numNormalConstr * sizeof(PxcSolverContact);

		PxF32* appliedImpulse = (PxF32*) (((PxU8*)hdr) + hdr->frictionOffset + sizeof(PxcSolverFrictionHeader));
		Ps::prefetchLine(appliedImpulse);

		const Vec3V normal = hdr->getNormal();

		const FloatV invMassDom0 = FLoad(hdr->dominance0);

		FloatV normalVel1 = V3Dot(normal, linVel0);

		const Vec3V delLinVel0 = V3Scale(normal, invMassDom0);
		FloatV accumDeltaF = zero;
		//FloatV accumImpulse = zero;

		for(PxU32 i=0;i<numNormalConstr;i++)
		{
			PxcSolverContact& c = contacts[i];
			Ps::prefetchLine(&contacts[i+1]);

			//const Vec4V normalXYZ_velMultiplierW = c.normalXYZ_velMultiplierW;
			const Vec4V raXnXYZ_appliedForceW = c.raXnXYZ_appliedForceW;
			const Vec4V rbXnXYZ_velMultiplierW = c.rbXnXYZ_velMultiplierW;

			//const Vec3V normal = c.normal;
			//const Vec3V normal = Vec3V_From_Vec4V(normalXYZ_velMultiplierW);
			const Vec3V raXn = Vec3V_From_Vec4V(raXnXYZ_appliedForceW);

			const FloatV appliedForce = V4GetW(raXnXYZ_appliedForceW);
			const FloatV velMultiplier = V4GetW(rbXnXYZ_velMultiplierW);
			//const FloatV velMultiplier = V4GetW(normalXYZ_velMultiplierW);

			const Vec3V delAngVel0 = Vec3V_From_Vec4V(c.delAngVel0_InvMassADom);

			const FloatV targetVel = c.getTargetVelocity();
			const FloatV nScaledBias = FNeg(c.getScaledBias());
			const FloatV maxImpulse = c.getMaxImpulse();

			//Compute the normal velocity of the constraint.

			//const FloatV normalVel1 = V3Dot(normal, linVel0);
			const FloatV normalVel2 = V3Dot(raXn, angVel0);
			const FloatV normalVel =  FAdd(normalVel1, normalVel2);

			//const FloatV unbiasedErr = FMul(targetVel, velMultiplier);
			const FloatV biasedErr = FMulAdd(targetVel, velMultiplier, nScaledBias);

			// still lots to do here: using loop pipelining we can interweave this code with the
			// above - the code here has a lot of stalls that we would thereby eliminate

			const FloatV _deltaF = FMax(FNegMulSub(normalVel, velMultiplier, biasedErr), FNeg(appliedForce));
			const FloatV _newForce = FAdd(appliedForce, _deltaF);
			const FloatV newForce = FMin(_newForce, maxImpulse);
			const FloatV deltaF = FSub(newForce, appliedForce);

			//linVel0 = V3MulAdd(delLinVel0, deltaF, linVel0);
			normalVel1 = FScaleAdd(invMassDom0, deltaF, normalVel1);
			angVel0 = V3ScaleAdd(delAngVel0, deltaF, angVel0);

			accumDeltaF = FAdd(accumDeltaF, deltaF);

			c.setAppliedForce(newForce);
			Ps::aos::FStore(newForce, &appliedImpulse[i]);
			Ps::prefetchLine(&appliedImpulse[i], 128);

			//accumImpulse = FAdd(accumImpulse, newAppliedForce);
		}
		linVel0 = V3ScaleAdd(delLinVel0, accumDeltaF, linVel0);
		//hdr->setAccumlatedForce(accumImpulse);
	}

	// Write back
	V3StoreU(linVel0, b0.linearVelocity);
	V3StoreU(angVel0, b0.angularVelocity);

	PX_ASSERT(currPtr == last);
}