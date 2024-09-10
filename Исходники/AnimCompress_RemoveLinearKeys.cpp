void UAnimCompress_RemoveLinearKeys::ProcessAnimationTracks(
	UAnimSequence* AnimSeq, 
	const TArray<FBoneData>& BoneData, 
	TArray<FTranslationTrack>& PositionTracks,
	TArray<FRotationTrack>& RotationTracks, 
	TArray<FScaleTrack>& ScaleTracks)
{
	// extract all the data we'll need about the skeleton and animation sequence
	const int32 NumBones			= BoneData.Num();
	const int32 NumFrames			= AnimSeq->NumFrames;
	const float SequenceLength	= AnimSeq->SequenceLength;
	const int32 LastFrame = NumFrames-1;
	const float FrameRate = (float)(LastFrame) / SequenceLength;
	const float TimePerFrame = SequenceLength / (float)(LastFrame);

	const TArray<FTransform>& RefPose = AnimSeq->GetSkeleton()->GetRefLocalPoses();
	const bool bHasScale =  (ScaleTracks.Num() > 0);

	// make sure the parent key scale is properly bound to 1.0 or more
	ParentKeyScale = FMath::Max(ParentKeyScale, 1.0f);

	// generate the raw and compressed skeleton in world-space
	TArray<FTransform> RawWorldBones;
	TArray<FTransform> NewWorldBones;
	RawWorldBones.Empty(NumBones * NumFrames);
	NewWorldBones.Empty(NumBones * NumFrames);
	RawWorldBones.AddZeroed(NumBones * NumFrames);
	NewWorldBones.AddZeroed(NumBones * NumFrames);

	// generate an array to hold the indices of our end effectors
	TArray<int32> EndEffectors;
	EndEffectors.Empty(NumBones);

	// Create an array of FTransform to use as a workspace
	TArray<FTransform> BoneAtoms;

	// setup the raw bone transformation and find all end effectors
	for ( int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex )
	{
		// get the raw world-atoms for this bone
		UpdateWorldBoneTransformTable(
			AnimSeq, 
			BoneData, 
			RefPose,
			BoneIndex,
			true,
			RawWorldBones);

		// also record all end-effectors we find
		const FBoneData& Bone = BoneData[BoneIndex];
		if (Bone.IsEndEffector())
		{
			EndEffectors.Add(BoneIndex);
		}
	}

	TArray<int32> TargetBoneIndices;
	// for each bone...
	for ( int32 BoneIndex = 0; BoneIndex < NumBones; ++BoneIndex )
	{
		const FBoneData& Bone = BoneData[BoneIndex];
		const int32 ParentBoneIndex = Bone.GetParent();

		const int32 TrackIndex = AnimSeq->GetSkeleton()->GetAnimationTrackIndex(BoneIndex, AnimSeq);

		if (TrackIndex != INDEX_NONE)
		{
			// get the tracks we will be editing for this bone
			FRotationTrack& RotTrack = RotationTracks[TrackIndex];
			FTranslationTrack& TransTrack = PositionTracks[TrackIndex];
			const int32 NumRotKeys = RotTrack.RotKeys.Num();
			const int32 NumPosKeys = TransTrack.PosKeys.Num();
			const int32 NumScaleKeys = (bHasScale)? ScaleTracks[TrackIndex].ScaleKeys.Num() : 0;

			check( (NumPosKeys == 1) || (NumRotKeys == 1) || (NumPosKeys == NumRotKeys) );

			// build an array of end effectors we need to monitor
			TargetBoneIndices.Reset(NumBones);

			int32 HighestTargetBoneIndex = BoneIndex;
			int32 FurthestTargetBoneIndex = BoneIndex;
			int32 ShortestChain = 0;
			float OffsetLength= -1.0f;
			for (int32 EffectorIndex=0; EffectorIndex < EndEffectors.Num(); ++EffectorIndex)
			{
				const int32 EffectorBoneIndex = EndEffectors[EffectorIndex];
				const FBoneData& EffectorBoneData = BoneData[EffectorBoneIndex];

				int32 RootIndex = EffectorBoneData.BonesToRoot.Find(BoneIndex);
				if (RootIndex != INDEX_NONE)
				{
					if (ShortestChain == 0 || (RootIndex+1) < ShortestChain)
					{
						ShortestChain = (RootIndex+1);
					}
					TargetBoneIndices.Add(EffectorBoneIndex);
					HighestTargetBoneIndex = FMath::Max(HighestTargetBoneIndex, EffectorBoneIndex);
					float ChainLength= 0.0f;
					for (long FamilyIndex=0; FamilyIndex < RootIndex; ++FamilyIndex)
					{
						const int32 NextParentBoneIndex= EffectorBoneData.BonesToRoot[FamilyIndex];
						ChainLength += RefPose[NextParentBoneIndex].GetTranslation().Size();
					}

					if (ChainLength > OffsetLength)
					{
						FurthestTargetBoneIndex = EffectorBoneIndex;
						OffsetLength = ChainLength;
					}

				}
			}

			// if requested, retarget the FBoneAtoms towards the target end effectors
			if (bRetarget)
			{
				if (NumScaleKeys > 0 && ParentBoneIndex != INDEX_NONE)
				{
					// update our bone table from the current bone through the last end effector we need to test
					UpdateWorldBoneTransformRange(
						AnimSeq, 
						BoneData, 
						RefPose,
						PositionTracks,
						RotationTracks,
						ScaleTracks,
						BoneIndex,
						HighestTargetBoneIndex,
						false,
						NewWorldBones);

					FScaleTrack& ScaleTrack = ScaleTracks[TrackIndex];

					// adjust all translation keys to align better with the destination
					for ( int32 KeyIndex = 0; KeyIndex < NumScaleKeys; ++KeyIndex )
					{
						FVector& Key= ScaleTrack.ScaleKeys[KeyIndex];

						const int32 FrameIndex= FMath::Clamp(KeyIndex, 0, LastFrame);
						const FTransform& NewWorldParent = NewWorldBones[(ParentBoneIndex*NumFrames) + FrameIndex];
						const FTransform& RawWorldChild = RawWorldBones[(BoneIndex*NumFrames) + FrameIndex];
						const FTransform& RelTM = (RawWorldChild.GetRelativeTransform(NewWorldParent));
						const FTransform Delta = FTransform(RelTM);

						Key = Delta.GetScale3D();
					}
				}
							
				if (NumRotKeys > 0 && ParentBoneIndex != INDEX_NONE)
				{
					if (HighestTargetBoneIndex == BoneIndex)
					{
						for ( int32 KeyIndex = 0; KeyIndex < NumRotKeys; ++KeyIndex )
						{
							FQuat& Key = RotTrack.RotKeys[KeyIndex];

							check(ParentBoneIndex != INDEX_NONE);
							const int32 FrameIndex = FMath::Clamp(KeyIndex, 0, LastFrame);
							FTransform NewWorldParent = NewWorldBones[(ParentBoneIndex*NumFrames) + FrameIndex];
							FTransform RawWorldChild = RawWorldBones[(BoneIndex*NumFrames) + FrameIndex];
							const FTransform& RelTM = (RawWorldChild.GetRelativeTransform(NewWorldParent)); 
							FQuat Rot = FTransform(RelTM).GetRotation();

							const FQuat& AlignedKey = EnforceShortestArc(Key, Rot);
							Key = AlignedKey;
						}
					}
					else
					{
						// update our bone table from the current bone through the last end effector we need to test
						UpdateWorldBoneTransformRange(
							AnimSeq, 
							BoneData, 
							RefPose,
							PositionTracks,
							RotationTracks,
							ScaleTracks,
							BoneIndex,
							HighestTargetBoneIndex,
							false,
							NewWorldBones);
						
						// adjust all rotation keys towards the end effector target
						for ( int32 KeyIndex = 0; KeyIndex < NumRotKeys; ++KeyIndex )
						{
							FQuat& Key = RotTrack.RotKeys[KeyIndex];

							const int32 FrameIndex = FMath::Clamp(KeyIndex, 0, LastFrame);

							const FTransform& NewWorldTransform = NewWorldBones[(BoneIndex*NumFrames) + FrameIndex];

							const FTransform& DesiredChildTransform = RawWorldBones[(FurthestTargetBoneIndex*NumFrames) + FrameIndex].GetRelativeTransform(NewWorldTransform);
							const FTransform& CurrentChildTransform = NewWorldBones[(FurthestTargetBoneIndex*NumFrames) + FrameIndex].GetRelativeTransform(NewWorldTransform);

							// find the two vectors which represent the angular error we are trying to correct
							const FVector& CurrentHeading = CurrentChildTransform.GetTranslation();
							const FVector& DesiredHeading = DesiredChildTransform.GetTranslation();

							// if these are valid, we can continue
							if (!CurrentHeading.IsNearlyZero() && !DesiredHeading.IsNearlyZero())
							{
								const float DotResult = CurrentHeading.SafeNormal() | DesiredHeading.SafeNormal();

								// limit the range we will retarget to something reasonable (~60 degrees)
								if (DotResult < 1.0f && DotResult > 0.5f)
								{
									FQuat Adjustment= FQuat::FindBetween(CurrentHeading, DesiredHeading); 
									Adjustment.Normalize();
									Adjustment= EnforceShortestArc(FQuat::Identity, Adjustment);

									const FVector Test = Adjustment.RotateVector(CurrentHeading);
									const float Delta = (Test - DesiredHeading).Size();
									if (Delta < 0.001f)
									{
										FQuat NewKey = Adjustment * Key;
										NewKey.Normalize();

										const FQuat& AlignedKey = EnforceShortestArc(Key, NewKey);
										Key = AlignedKey;
									}
								}
							}
						}
					}
				}

				if (NumPosKeys > 0 && ParentBoneIndex != INDEX_NONE)
				{
					// update our bone table from the current bone through the last end effector we need to test
					UpdateWorldBoneTransformRange(
						AnimSeq, 
						BoneData, 
						RefPose,
						PositionTracks,
						RotationTracks,
						ScaleTracks,
						BoneIndex,
						HighestTargetBoneIndex,
						false,
						NewWorldBones);

					// adjust all translation keys to align better with the destination
					for ( int32 KeyIndex = 0; KeyIndex < NumPosKeys; ++KeyIndex )
					{
						FVector& Key= TransTrack.PosKeys[KeyIndex];

						const int32 FrameIndex= FMath::Clamp(KeyIndex, 0, LastFrame);
						FTransform NewWorldParent = NewWorldBones[(ParentBoneIndex*NumFrames) + FrameIndex];
						FTransform RawWorldChild = RawWorldBones[(BoneIndex*NumFrames) + FrameIndex];
						const FTransform& RelTM = RawWorldChild.GetRelativeTransform(NewWorldParent);
						const FTransform Delta = FTransform(RelTM);
						ensure (!Delta.ContainsNaN());

						Key = Delta.GetTranslation();
					}
				}

			}

			// look for a parent track to reference as a guide
			int32 GuideTrackIndex = INDEX_NONE;
			if (ParentKeyScale > 1.0f)
			{
				for (long FamilyIndex=0; (FamilyIndex < Bone.BonesToRoot.Num()) && (GuideTrackIndex == INDEX_NONE); ++FamilyIndex)
				{
					const int32 NextParentBoneIndex= Bone.BonesToRoot[FamilyIndex];

					GuideTrackIndex = AnimSeq->GetSkeleton()->GetAnimationTrackIndex(NextParentBoneIndex, AnimSeq);
				}
			}

			// update our bone table from the current bone through the last end effector we need to test
			UpdateWorldBoneTransformRange(
				AnimSeq, 
				BoneData, 
				RefPose,
				PositionTracks,
				RotationTracks,
				ScaleTracks,
				BoneIndex,
				HighestTargetBoneIndex,
				false,
				NewWorldBones);

			// rebuild the BoneAtoms table using the current set of keys
			UpdateBoneAtomList(AnimSeq, BoneIndex, TrackIndex, NumFrames, TimePerFrame, BoneAtoms); 

			// determine the EndEffectorTolerance. 
			// We use the Maximum value by default, and the Minimum value
			// as we approach the end effectors
			float EndEffectorTolerance = MaxEffectorDiff;
			if (ShortestChain <= 1)
			{
				EndEffectorTolerance = MinEffectorDiff;
			}

			// Determine if a guidance track should be used to aid in choosing keys to retain
			TArray<float>* GuidanceTrack = NULL;
			float GuidanceScale = 1.0f;
			if (GuideTrackIndex != INDEX_NONE)
			{
				FTranslationTrack& GuideTransTrack = PositionTracks[GuideTrackIndex];
				GuidanceTrack = &GuideTransTrack.Times;
				GuidanceScale = ParentKeyScale;
			}
			
			// if the TargetBoneIndices array is empty, then this bone is an end effector.
			// so we add it to the list to maintain our tolerance checks
			if (TargetBoneIndices.Num() == 0)
			{
				TargetBoneIndices.Add(BoneIndex);
			}

			if (bActuallyFilterLinearKeys)
			{
				if (bHasScale)
				{
					FScaleTrack& ScaleTrack = ScaleTracks[TrackIndex];
					// filter out translations we can approximate through interpolation
					FilterLinearKeysTemplate<FVector>(
						ScaleTrack.ScaleKeys, 
						ScaleTrack.Times, 
						BoneAtoms,
						GuidanceTrack, 
						RawWorldBones,
						NewWorldBones,
						TargetBoneIndices,
						NumFrames,
						BoneIndex,
						ParentBoneIndex,
						GuidanceScale, 
						MaxScaleDiff, 
						EndEffectorTolerance,
						EffectorDiffSocket,
						BoneData);

					// update our bone table from the current bone through the last end effector we need to test
					UpdateWorldBoneTransformRange(
						AnimSeq, 
						BoneData, 
						RefPose,
						PositionTracks,
						RotationTracks,
						ScaleTracks,
						BoneIndex,
						HighestTargetBoneIndex,
						false,
						NewWorldBones);

					// rebuild the BoneAtoms table using the current set of keys
					UpdateBoneAtomList(AnimSeq, BoneIndex, TrackIndex, NumFrames, TimePerFrame, BoneAtoms); 
				}

				// filter out translations we can approximate through interpolation
				FilterLinearKeysTemplate<FVector>(
					TransTrack.PosKeys, 
					TransTrack.Times, 
					BoneAtoms,
					GuidanceTrack, 
					RawWorldBones,
					NewWorldBones,
					TargetBoneIndices,
					NumFrames,
					BoneIndex,
					ParentBoneIndex,
					GuidanceScale, 
					MaxPosDiff, 
					EndEffectorTolerance,
					EffectorDiffSocket,
					BoneData);

				// update our bone table from the current bone through the last end effector we need to test
				UpdateWorldBoneTransformRange(
					AnimSeq, 
					BoneData, 
					RefPose,
					PositionTracks,
					RotationTracks,
					ScaleTracks,
					BoneIndex,
					HighestTargetBoneIndex,
					false,
					NewWorldBones);

				// rebuild the BoneAtoms table using the current set of keys
				UpdateBoneAtomList(AnimSeq, BoneIndex, TrackIndex, NumFrames, TimePerFrame, BoneAtoms); 

				// filter out rotations we can approximate through interpolation
				FilterLinearKeysTemplate<FQuat>(
					RotTrack.RotKeys, 
					RotTrack.Times, 
					BoneAtoms,
					GuidanceTrack, 
					RawWorldBones,
					NewWorldBones,
					TargetBoneIndices,
					NumFrames,
					BoneIndex,
					ParentBoneIndex,
					GuidanceScale, 
					MaxAngleDiff, 
					EndEffectorTolerance,
					EffectorDiffSocket,
					BoneData);
			}
		}

		// make sure the final compressed keys are repesented in our NewWorldBones table
		UpdateWorldBoneTransformRange(
			AnimSeq, 
			BoneData, 
			RefPose,
			PositionTracks,
			RotationTracks,
			ScaleTracks,
			BoneIndex,
			BoneIndex,
			false,
			NewWorldBones);
	}
};