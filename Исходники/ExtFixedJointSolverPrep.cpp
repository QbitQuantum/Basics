	PxU32 FixedJointSolverPrep(Px1DConstraint* constraints,
		PxVec3& body0WorldOffset,
		PxU32 maxConstraints,
		PxConstraintInvMassScale &invMassScale,
		const void* constantBlock,
		const PxTransform& bA2w,
		const PxTransform& bB2w)
	{
		PX_UNUSED(maxConstraints);

		const FixedJointData& data = *reinterpret_cast<const FixedJointData*>(constantBlock);
		invMassScale = data.invMassScale;

		PxTransform cA2w = bA2w.transform(data.c2b[0]);
		PxTransform cB2w = bB2w.transform(data.c2b[1]);

		PxVec3 bOriginInA = cA2w.transformInv(cB2w.p);

		body0WorldOffset = cB2w.p-bA2w.p;
		joint::ConstraintHelper ch(constraints,cB2w.p-bA2w.p, cB2w.p-bB2w.p);
		ch.prepareLockedAxes(cA2w.q, cB2w.q, bOriginInA, 7, 7);

		return ch.getCount();
	}