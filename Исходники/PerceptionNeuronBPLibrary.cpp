// Read motion data from Axis Neuron
// Deprecated
bool UPerceptionNeuronBPLibrary::NeuronReadMotion(APerceptionNeuronController *Controller, FVector& Translation, FRotator& Rotation, FVector AdditionalTranslation, FRotator AdditionalRotation, int32 BoneIndex, ENeuronSkeletonEnum SkeletonType)
{
	if (Controller == nullptr)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Controller is invalid.")));
		}
		Rotation.Yaw = Rotation.Pitch = Rotation.Roll = 0;
		Translation.X = Translation.Y = Translation.Z = 0;
		return false;
	}
	else if ((Controller->bConnected == false) && (Controller->bPlay == false))
	{
		Rotation.Yaw = Rotation.Pitch = Rotation.Roll = 0;
		Translation.X = Translation.Y = Translation.Z = 0;
		return false;
	}
	else if (BoneIndex >= Controller->Skeleton.BoneNr)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Boneindex %d exceeds maximum available bones %d."), BoneIndex, Controller->Skeleton.BoneNr));
		}
		Rotation.Yaw = Rotation.Pitch = Rotation.Roll = 0;
		Translation.X = Translation.Y = Translation.Z = 0;
		return false;
	}

	int32 FloatsPerBone = 6; // 3 for x,y,z translation and 3 for x,y,z rotation
	if (Controller->bDisplacement == false)
	{
		FloatsPerBone = 3;	// If there is no displacement (translation) info we have only 3 floats for rotation left
	}

	if ((BoneIndex * FloatsPerBone) > Controller->FloatCount)
	{
		Rotation.Yaw = Rotation.Pitch = Rotation.Roll = 0;
		Translation.X = Translation.Y = Translation.Z = 0;
		return false;
	}


	//
	// Translation
	//

	if (Controller->bDisplacement == true)
	{
		// Read translation values and remove BVH reference position
		float X = Controller->MotionLine[(BoneIndex * FloatsPerBone) + Controller->Skeleton.Bones[BoneIndex].XPos] - Controller->Skeleton.Bones[BoneIndex].Offset[0];
		float Y = Controller->MotionLine[(BoneIndex * FloatsPerBone) + Controller->Skeleton.Bones[BoneIndex].YPos] - Controller->Skeleton.Bones[BoneIndex].Offset[1];
		float Z = Controller->MotionLine[(BoneIndex * FloatsPerBone) + Controller->Skeleton.Bones[BoneIndex].ZPos] - Controller->Skeleton.Bones[BoneIndex].Offset[2];

		// Map BVH right hand system to local bone coordinate system
		switch (SkeletonType)
		{
		case ENeuronSkeletonEnum::VE_Neuron:  // Neuron BVH skeleton
		{
			if (BoneIndex == 0)
			{	// Hips
				Translation = FVector(X, -Y, Z);
			}
			else if ((BoneIndex >= 1) && (BoneIndex <= 6))
			{	// Legs
				Translation = FVector(X, Y, -Z);
			}
			else if ((BoneIndex >= 7) && (BoneIndex <= 12))
			{	// Spine,...
				Translation = FVector(X, -Y, -Z);
			}
			else if ((BoneIndex >= 13) && (BoneIndex <= 35))
			{	// Right arm
				Translation = FVector(-Z, X, Y);
			}
			else if ((BoneIndex >= 36) && (BoneIndex <= 58))
			{	// Left arm
				Translation = FVector(Z, -X, Y);
			}
			break;
		}
		case ENeuronSkeletonEnum::VE_TPP_Hero:	// Hero_TPP, Old blue Unreal default skeleton with T-Pose
		case ENeuronSkeletonEnum::VE_Mannequin: // Mannequin, New Unreal default skeleton with A-Pose
		{
			if (BoneIndex == 0)
			{	// Hips
				Translation = FVector(Y, Z, -X);
			}
			// Ignore other bones
			break;
		}
		case ENeuronSkeletonEnum::VE_Map: // Map to configured bone map
		{
			// Map translation with configured Bonemap
			float Map[3] = { X, Y, Z };

			Translation = FVector(Map[Controller->Bonemap[BoneIndex].XYZ[0]] * Controller->Bonemap[BoneIndex].Sign[0],
				Map[Controller->Bonemap[BoneIndex].XYZ[1]] * Controller->Bonemap[BoneIndex].Sign[1],
				Map[Controller->Bonemap[BoneIndex].XYZ[2]] * Controller->Bonemap[BoneIndex].Sign[2]);
			break;
		}
		case ENeuronSkeletonEnum::VE_UE4: // Map to UE4 world coordinate system
		{
			Translation = FVector(X, Z, Y);
			break;
		}
		case ENeuronSkeletonEnum::VE_None: // Map to nothing, use BVH translation as it is
		default:
		{
			Translation = FVector(X, Y, Z);
			break;
		}
		}
	}
	else
	{
		Translation.X = Translation.Y = Translation.Z = 0;
	}

	// Add additional translation
	Translation.X += AdditionalTranslation.X;
	Translation.Y += AdditionalTranslation.Y;
	Translation.Z += AdditionalTranslation.Z;



	//
	// Rotation 
	//

	// Read rotation values and map to pitch, yaw, roll (y, z, x)
	float XR = Controller->MotionLine[(BoneIndex * FloatsPerBone) + Controller->Skeleton.Bones[BoneIndex].XRot] * PI / 180.f;
	float YR = Controller->MotionLine[(BoneIndex * FloatsPerBone) + Controller->Skeleton.Bones[BoneIndex].YRot] * PI / 180.f;
	float ZR = Controller->MotionLine[(BoneIndex * FloatsPerBone) + Controller->Skeleton.Bones[BoneIndex].ZRot] * PI / 180.f;

	// Calculate Rotation Matrix and map to Quaternion
	FQuat Quat = CalculateQuat(XR, YR, ZR, Controller->Skeleton.Bones[BoneIndex].RotOrder);

	// Map BVH coordinate system to each bone coordinate system dependend on skeleton type
	switch (SkeletonType)
	{
	case ENeuronSkeletonEnum::VE_Neuron:  // Neuron BVH skeleton
	{
		if ((BoneIndex >= 1) && (BoneIndex <= 6))
		{	// Legs
			Quat.Z *= -1.f;
		}
		else if ((BoneIndex >= 13) && (BoneIndex <= 35))
		{	// Right Arm
			float X = Quat.X;
			float Y = Quat.Y;
			float Z = Quat.Z;
			Quat.X = -Z;
			Quat.Y = X;
			Quat.Z = Y;
		}
		else if ((BoneIndex >= 36) && (BoneIndex <= 58))
		{	// Left Arm
			float X = Quat.X;
			float Y = Quat.Y;
			float Z = Quat.Z;
			Quat.X = Z;
			Quat.Y = -X;
			Quat.Z = Y;
		}
		else
		{
			Quat.Y *= -1.f;
		}
		break;
	}
	case ENeuronSkeletonEnum::VE_TPP_Hero:	// Hero_TPP, Old blue Unreal default skeleton with T-Pose
	case ENeuronSkeletonEnum::VE_Mannequin: // Mannequin, New Unreal default skeleton with A-Pose
	{
		if ((BoneIndex >= 1) && (BoneIndex <= 3))
		{	// Right Leg
			float X = Quat.X;
			float Y = Quat.Y;
			float Z = Quat.Z;
			Quat.X = -Y;
			Quat.Y = -Z;
			Quat.Z = -X;
		}
		else if (BoneIndex == 16)
		{	// Right Hand
			Quat.Y *= -1.f;
		}
		else if ((BoneIndex >= 13) && (BoneIndex <= 19))
		{	// Right Arm and Thumb
			float Y = Quat.Y;
			float Z = Quat.Z;
			Quat.Y = -Z;
			Quat.Z = -Y;
		}
		else if ((BoneIndex >= 20) && (BoneIndex <= 35))
		{	// Right Finger
			Quat.Y *= -1.f;
		}
		else if (BoneIndex == 39)
		{	// Left Hand
			Quat.Z *= -1.f;
		}
		else if ((BoneIndex >= 36) && (BoneIndex <= 42))
		{	// Left Arm and Thumb
			float Y = Quat.Y;
			float Z = Quat.Z;
			Quat.Y = Z;
			Quat.Z = Y;
		}
		else if ((BoneIndex >= 43) && (BoneIndex <= 58))
		{	// Left Finger
			Quat.Z *= -1.f;
		}
		else
		{	// Left Leg, Hips, Spine, Neck, Head
			float X = Quat.X;
			float Y = Quat.Y;
			float Z = Quat.Z;
			Quat.X = Y;
			Quat.Y = Z;
			Quat.Z = -X;
		}
		break;
	}
	case ENeuronSkeletonEnum::VE_Map: // Map to configured bone map
	{
		// Map Quat.X/Y/Z with configured Bonemap				
		float Map[3] = { Quat.X, Quat.Y, Quat.Z };

		Quat.X = Map[Controller->Bonemap[BoneIndex].XYZ[0]] * Controller->Bonemap[BoneIndex].Sign[0];
		Quat.Y = Map[Controller->Bonemap[BoneIndex].XYZ[1]] * Controller->Bonemap[BoneIndex].Sign[1];
		Quat.Z = Map[Controller->Bonemap[BoneIndex].XYZ[2]] * Controller->Bonemap[BoneIndex].Sign[2];
		break;
	}
	case ENeuronSkeletonEnum::VE_UE4: // Map to UE4 world coordinate system
	{
		float Y = Quat.Y;
		float Z = Quat.Z;
		Quat.Y = Z;
		Quat.Z = Y;
		break;
	}
	case ENeuronSkeletonEnum::VE_None: // Map to nothing, use BVH rotation as it is
	default:
	{
		// Nothing to do, Quaternion is already BVH
		break;
	}
	}

	// Convert to Rotator
	Rotation = Quat.Rotator();

	// Add additional rotation
	Rotation.Yaw += AdditionalRotation.Yaw;
	Rotation.Pitch += AdditionalRotation.Pitch;
	Rotation.Roll += AdditionalRotation.Roll;
	Rotation.Normalize();

	return true;
}