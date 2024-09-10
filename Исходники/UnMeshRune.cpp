// function is similar to part of CSkelMeshInstance::SetMesh()
static void BuildSkeleton(TArray<CCoords> &Coords, const TArray<RJoint> &Bones, const TArray<AnalogTrack> &Anim)
{
	guard(BuildSkeleton);

	int numBones = Anim.Num();
	Coords.Empty(numBones);
	Coords.AddZeroed(numBones);

	for (int i = 0; i < numBones; i++)
	{
		const AnalogTrack &A = Anim[i];
		const RJoint &B = Bones[i];
		CCoords &BC = Coords[i];
		// compute reference bone coords
		CVec3 BP;
		CQuat BO;
		// get default pose
		BP = CVT(A.KeyPos[0]);
		BO = CVT(A.KeyQuat[0]);
		if (!i) BO.Conjugate();

		BC.origin = BP;
		BO.ToAxis(BC.axis);
		// move bone position to global coordinate space
		if (i)	// do not rotate root bone
		{
			assert(B.parent >= 0);
			Coords[B.parent].UnTransformCoords(BC, BC);
		}
	}

	unguard;
}