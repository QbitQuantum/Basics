void APlayerCameraManager::ApplyAnimToCamera(ACameraActor const* AnimatedCamActor, UCameraAnimInst const* AnimInst, FMinimalViewInfo& InOutPOV)
{
	if (AnimInst->CamAnim->bRelativeToInitialTransform)
	{
		// move animated cam actor to initial-relative position
		FTransform const AnimatedCamToWorld = AnimatedCamActor->GetTransform();
		FTransform const AnimatedCamToInitialCam = AnimatedCamToWorld * AnimInst->InitialCamToWorld.Inverse();
		ACameraActor* const MutableCamActor = const_cast<ACameraActor*>(AnimatedCamActor);
		MutableCamActor->SetActorTransform(AnimatedCamToInitialCam);
	}

	float const Scale = AnimInst->CurrentBlendWeight;
	FRotationMatrix const CameraToWorld(InOutPOV.Rotation);

	if (AnimInst->PlaySpace == ECameraAnimPlaySpace::CameraLocal)
	{
		// the code in the else block will handle this just fine, but this path provides efficiency and simplicity for the most common case

		// loc
		FVector const LocalOffset = CameraToWorld.TransformVector( AnimatedCamActor->GetActorLocation()*Scale );
		InOutPOV.Location += LocalOffset;

		// rot
		FRotationMatrix const AnimRotMat( AnimatedCamActor->GetActorRotation()*Scale );
		InOutPOV.Rotation = (AnimRotMat * CameraToWorld).Rotator();
	}
	else
	{
		// handle playing the anim in an arbitrary space relative to the camera

		// find desired space
		FMatrix const PlaySpaceToWorld = (AnimInst->PlaySpace == ECameraAnimPlaySpace::UserDefined) ? AnimInst->UserPlaySpaceMatrix : FMatrix::Identity;

		// loc
		FVector const LocalOffset = PlaySpaceToWorld.TransformVector( AnimatedCamActor->GetActorLocation()*Scale );
		InOutPOV.Location += LocalOffset;

		// rot
		// find transform from camera to the "play space"
		FMatrix const CameraToPlaySpace = CameraToWorld * PlaySpaceToWorld.Inverse();	// CameraToWorld * WorldToPlaySpace

		// find transform from anim (applied in playspace) back to camera
		FRotationMatrix const AnimToPlaySpace(AnimatedCamActor->GetActorRotation()*Scale);
		FMatrix const AnimToCamera = AnimToPlaySpace * CameraToPlaySpace.Inverse();			// AnimToPlaySpace * PlaySpaceToCamera

		// RCS = rotated camera space, meaning camera space after it's been animated
		// this is what we're looking for, the diff between rotated cam space and regular cam space.
		// apply the transform back to camera space from the post-animated transform to get the RCS
		FMatrix const RCSToCamera = CameraToPlaySpace * AnimToCamera;

		// now apply to real camera
		FRotationMatrix const RealCamToWorld(InOutPOV.Rotation);
		InOutPOV.Rotation = (RCSToCamera * RealCamToWorld).Rotator();
	}

	// fov
	const float FOVMin = 5.f;
	const float FOVMax = 170.f;
	InOutPOV.FOV += (AnimatedCamActor->GetCameraComponent()->FieldOfView - AnimInst->InitialFOV) * Scale;
	InOutPOV.FOV = FMath::Clamp<float>(InOutPOV.FOV, FOVMin, FOVMax);

	// postprocess
	if (AnimatedCamActor->GetCameraComponent()->PostProcessBlendWeight > 0.f)
	{
		AddCachedPPBlend(AnimatedCamActor->GetCameraComponent()->PostProcessSettings, AnimatedCamActor->GetCameraComponent()->PostProcessBlendWeight);
	}
}