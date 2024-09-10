void FAnimationRuntime::BlendMeshPosesPerBoneWeights(
		struct FCompactPose& BasePose,
		const TArray<struct FCompactPose>& BlendPoses,
		struct FBlendedCurve& BaseCurve,
		const TArray<struct FBlendedCurve>& BlendedCurves,
		const TArray<FPerBoneBlendWeight>& BoneBlendWeights,
		ECurveBlendOption::Type CurveBlendOption,
		/*out*/ FCompactPose& OutPose,
		/*out*/ struct FBlendedCurve& OutCurve)
{
	check(BasePose.GetNumBones() == BoneBlendWeights.Num());

	const FBoneContainer& BoneContainer = BasePose.GetBoneContainer();

	TCustomBoneIndexArray<FQuat, FCompactPoseBoneIndex> SourceRotations;
	TCustomBoneIndexArray<FQuat, FCompactPoseBoneIndex> BlendRotations;
	TCustomBoneIndexArray<FQuat, FCompactPoseBoneIndex> TargetRotations;

	SourceRotations.AddUninitialized(BasePose.GetNumBones());
	BlendRotations.AddUninitialized(BasePose.GetNumBones());
	TargetRotations.AddUninitialized(BasePose.GetNumBones());

	int32 PoseNum = BlendPoses.Num();

	TArray<float> MaxPoseWeights;
	MaxPoseWeights.AddZeroed(PoseNum);

	for (FCompactPoseBoneIndex BoneIndex : BasePose.ForEachBoneIndex())
	{
		const int32 PoseIndex = BoneBlendWeights[BoneIndex.GetInt()].SourceIndex;
		const FCompactPoseBoneIndex ParentIndex = BoneContainer.GetParentBoneIndex(BoneIndex);

		FQuat SrcRotationInMesh;
		FQuat TargetRotationInMesh;

		if (ParentIndex != INDEX_NONE)
		{
			SrcRotationInMesh = SourceRotations[ParentIndex] * BasePose[BoneIndex].GetRotation();
			TargetRotationInMesh = TargetRotations[ParentIndex] * BlendPoses[PoseIndex][BoneIndex].GetRotation();
		}
		else
		{
			SrcRotationInMesh = BasePose[BoneIndex].GetRotation();
			TargetRotationInMesh = BlendPoses[PoseIndex][BoneIndex].GetRotation();
		}

		// update mesh based rotations
		SourceRotations[BoneIndex] = SrcRotationInMesh;
		TargetRotations[BoneIndex] = TargetRotationInMesh;

		// now update outer
		FTransform BaseAtom = BasePose[BoneIndex];
		FTransform TargetAtom = BlendPoses[PoseIndex][BoneIndex];
		FTransform BlendAtom;

		const float BlendWeight = FMath::Clamp(BoneBlendWeights[BoneIndex.GetInt()].BlendWeight, 0.f, 1.f);
		MaxPoseWeights[PoseIndex] = FMath::Max(MaxPoseWeights[PoseIndex], BlendWeight);

		if (BlendWeight < ZERO_ANIMWEIGHT_THRESH)
		{
			BlendAtom = BaseAtom;
			BlendRotations[BoneIndex] = SourceRotations[BoneIndex];
		}
		else if ((1.0 - BlendWeight) < ZERO_ANIMWEIGHT_THRESH)
		{
			BlendAtom = TargetAtom;
			BlendRotations[BoneIndex] = TargetRotations[BoneIndex];
		}
		else // we want blend here
		{
			BlendAtom = BaseAtom;
			BlendAtom.BlendWith(TargetAtom, BlendWeight);

			// blend rotation in mesh space
			BlendRotations[BoneIndex] = FQuat::FastLerp(SourceRotations[BoneIndex], TargetRotations[BoneIndex], BlendWeight);

			// Fast lerp produces un-normalized quaternions, re-normalize.
			BlendRotations[BoneIndex].Normalize();
		}

		OutPose[BoneIndex] = BlendAtom;
		if (ParentIndex != INDEX_NONE)
		{
			FQuat LocalBlendQuat = BlendRotations[ParentIndex].Inverse() * BlendRotations[BoneIndex];

			// local -> mesh -> local transformations can cause loss of precision for long bone chains, we have to normalize rotation there.
			LocalBlendQuat.Normalize();
			OutPose[BoneIndex].SetRotation(LocalBlendQuat);
		}
	}

	// time to blend curves
	// the way we blend curve per bone
	// is to find out max weight per that pose, and then apply that weight to the curve
	{
		TArray<const FBlendedCurve*> SourceCurves;
		TArray<float> SourceWegihts;

		SourceCurves.SetNumUninitialized(PoseNum+1);
		SourceWegihts.SetNumUninitialized(PoseNum+1);

		SourceCurves[0] = &BaseCurve;
		SourceWegihts[0] = 1.f;

		for(int32 Idx=0; Idx<PoseNum; ++Idx)
		{
			SourceCurves[Idx+1] = &BlendedCurves[Idx];
			SourceWegihts[Idx+1] = MaxPoseWeights[Idx];
		}

		BlendCurves(SourceCurves, SourceWegihts, OutCurve, CurveBlendOption);
	}
}