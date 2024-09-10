void UCameraAnimInst::ApplyToView(FMinimalViewInfo& InOutPOV) const
{
	if (CurrentBlendWeight > 0.f)
	{
		ACameraActor const* AnimatedCamActor = dynamic_cast<ACameraActor*>(InterpGroupInst->GetGroupActor());
		if (AnimatedCamActor)
		{

			if (CamAnim->bRelativeToInitialTransform)
			{
				// move animated cam actor to initial-relative position
				FTransform const AnimatedCamToWorld = AnimatedCamActor->GetTransform();
				FTransform const AnimatedCamToInitialCam = AnimatedCamToWorld * InitialCamToWorld.Inverse();
				ACameraActor* const MutableCamActor = const_cast<ACameraActor*>(AnimatedCamActor);
				MutableCamActor->SetActorTransform(AnimatedCamToInitialCam);
			}

			float const Scale = CurrentBlendWeight;
			FRotationMatrix const CameraToWorld(InOutPOV.Rotation);

			if (PlaySpace == ECameraAnimPlaySpace::CameraLocal)
			{
				// the code in the else block will handle this just fine, but this path provides efficiency and simplicity for the most common case

				// loc
				FVector const LocalOffset = CameraToWorld.TransformVector(AnimatedCamActor->GetActorLocation()*Scale);
				InOutPOV.Location += LocalOffset;

				// rot
				FRotationMatrix const AnimRotMat(AnimatedCamActor->GetActorRotation()*Scale);
				InOutPOV.Rotation = (AnimRotMat * CameraToWorld).Rotator();
			}
			else
			{
				// handle playing the anim in an arbitrary space relative to the camera

				// find desired space
				FMatrix const PlaySpaceToWorld = (PlaySpace == ECameraAnimPlaySpace::UserDefined) ? UserPlaySpaceMatrix : FMatrix::Identity;

				// loc
				FVector const LocalOffset = PlaySpaceToWorld.TransformVector(AnimatedCamActor->GetActorLocation()*Scale);
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
			if (bHasFOVTrack)
			{
				const float FOVMin = 5.f;
				const float FOVMax = 170.f;

				// Interp the FOV toward the camera component's FOV based on Scale
				if (CamAnim->bRelativeToInitialFOV)
				{
					InOutPOV.FOV += (AnimatedCamActor->GetCameraComponent()->FieldOfView - InitialFOV) * Scale;
				}
				else
				{
					const int32 DesiredDirection = FMath::Sign(AnimatedCamActor->GetCameraComponent()->FieldOfView - InOutPOV.FOV);
					const int32 InitialDirection = FMath::Sign(AnimatedCamActor->GetCameraComponent()->FieldOfView - InitialFOV);
					if (DesiredDirection != InitialDirection)
					{
						InOutPOV.FOV = FMath::Clamp(InOutPOV.FOV + ((AnimatedCamActor->GetCameraComponent()->FieldOfView - InOutPOV.FOV) * Scale), InOutPOV.FOV, AnimatedCamActor->GetCameraComponent()->FieldOfView);
					}
					else
					{
						InOutPOV.FOV = FMath::Clamp(InOutPOV.FOV + ((AnimatedCamActor->GetCameraComponent()->FieldOfView - InitialFOV) * Scale), AnimatedCamActor->GetCameraComponent()->FieldOfView, InitialFOV);
					}
				}
				InOutPOV.FOV = FMath::Clamp<float>(InOutPOV.FOV, FOVMin, FOVMax);
			}
		}
	}
}