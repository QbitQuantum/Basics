	PxU32 PrismaticJointSolverPrep(Px1DConstraint* constraints,
		PxVec3& body0WorldOffset,
		PxU32 maxConstraints,
		PxConstraintInvMassScale &invMassScale,
		const void* constantBlock,
		const PxTransform& bA2w,
		const PxTransform& bB2w)
	{
		PX_UNUSED(maxConstraints);

		const PrismaticJointData& data = *reinterpret_cast<const PrismaticJointData*>(constantBlock);
		invMassScale = data.invMassScale;

		PxTransform cA2w = bA2w.transform(data.c2b[0]);
		PxTransform cB2w = bB2w.transform(data.c2b[1]);

		bool limitEnabled = data.jointFlags & PxPrismaticJointFlag::eLIMIT_ENABLED;
		const PxJointLinearLimitPair &limit = data.limit;
		bool limitIsLocked = limitEnabled && limit.lower >= limit.upper;

		PxVec3 bOriginInA = cA2w.transformInv(cB2w.p);

		body0WorldOffset = cB2w.p-bA2w.p;
		joint::ConstraintHelper ch(constraints,cB2w.p-bA2w.p, cB2w.p-bB2w.p);
		ch.prepareLockedAxes(cA2w.q, cB2w.q, bOriginInA, limitIsLocked ? (PxU32)7 : 6, 7);

		if(limitEnabled && !limitIsLocked)
		{
			PxVec3 axis = cA2w.rotate(PxVec3(1.f,0,0));
			PxReal ordinate = bOriginInA.x;

			ch.linearLimit(axis, ordinate, limit.upper, limit);
			ch.linearLimit(-axis, -ordinate, -limit.lower, limit);
		}

		return ch.getCount();
	}