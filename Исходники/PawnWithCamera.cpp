// Called every frame
void APawnWithCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Rotate our actor's yaw, which will turn our camera because we're attached to it
	{
		FRotator NewRotation = OurCameraBase->GetComponentRotation();
		NewRotation.Yaw += -CameraInput.X;
		OurCameraBase->SetWorldRotation(NewRotation);
	}

	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		FRotator NewRotation = OurCameraBase->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch - CameraInput.Y, -80.0f, 80.0f);
		OurCameraBase->SetWorldRotation(NewRotation);
	}

	//Handle movement based on our "MoveX" and "MoveY" axes
	{
		if (!MovementInput.IsZero())
		{
			//Scale our movement input axis values by 100 units per second
			MovementInput = MovementInput.SafeNormal() * 100.0f;
			FVector NewLocation = GetActorLocation();
			NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
			NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
			SetActorLocation(NewLocation);
		}
	}




	FVector LeftEyePosition = LeftEyePos->GetComponentLocation() - OurCamera->GetComponentLocation();
	LeftEyePosition.Normalize();

	FVector RightEyePosition = RightEyePos->GetComponentLocation() - OurCamera->GetComponentLocation();
	RightEyePosition.Normalize();

	FVector4 LeftEyeWeight;
	FVector4 RightEyeWeight;

	for (int i = 0; i < 4; i++)
	{
		LeftEyeWeight[i] = FVector::DotProduct((LeftEyePosition - FishEyePos[i]), dir[i]) / length[i];
		RightEyeWeight[i] = FVector::DotProduct((RightEyePosition - FishEyePos[i]), dir[i]) / length[i];
	}

	RV_MatInst->SetVectorParameterValue(FName("LeftEyePos"), LeftEyePosition);
	RV_MatInst->SetVectorParameterValue(FName("RightEyePos"), RightEyePosition);
	RV_MatInst->SetVectorParameterValue(FName("RightWeight"), LeftEyePosition);
	RV_MatInst->SetVectorParameterValue(FName("LeftWeight"), RightEyePosition);
}