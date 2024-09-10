void ACinemotusPlayerController::HandleMovementAbs(float DeltaTime, bool useHydraMotion = false)
{
	APawn* pawn = GetPawn();
	if (!pawn)
	{
		return;
	}

	

	//check velocities
	FVector velocity = useHydraMotion ? HydraLatestData->controllers[CAM_HAND].velocity : FVector::ZeroVector;
	FVector velRel = FVector(velocity);
	FRotationMatrix mat(GetControlRotation());
	float scalar = 2.5;
	if (useHydraMotion)
	{
		FRotationMatrix cMat(HydraLatestData->controllers[CAM_HAND].rotation);
		velRel.X = FVector::DotProduct(cMat.GetScaledAxis(EAxis::X), velocity);
		velRel.Y = FVector::DotProduct(cMat.GetScaledAxis(EAxis::Y), velocity);
		velRel.Z = FVector::DotProduct(cMat.GetScaledAxis(EAxis::Z), velocity); //take motion and make relative to the orientation of the controller
	}
	//velocity.X*DeltaTime * scaleCmToMetres*fSpeedMulitplier +

	pawn->AddMovementInput(mat.GetScaledAxis(EAxis::X), velRel.X*DeltaTime * scalar*fSpeedMulitplier + vXYandCrane.X);
	pawn->AddMovementInput(mat.GetScaledAxis(EAxis::Y), velRel.Y*DeltaTime * scalar*fSpeedMulitplier + vXYandCrane.Y);
	pawn->AddMovementInput(mat.GetScaledAxis(EAxis::Z), velRel.Z*DeltaTime * scalar*fSpeedMulitplier);
	pawn->AddMovementInput(FVector::UpVector, vXYandCrane.Z);


	//Add Movement input for offhand

	FVector xPlanar = mat.GetScaledAxis(EAxis::X);
	xPlanar.Z = 0;
	bool didNorm = xPlanar.Normalize();
	if (!didNorm)
	{ 
		xPlanar.X = 1.0; xPlanar.Normalize(); }
	pawn->AddMovementInput(xPlanar, offHandPlanarMovement.X);


	FVector yPlanar = mat.GetScaledAxis(EAxis::Y);
	yPlanar.Z = 0;
	didNorm = yPlanar.Normalize();
	if (!didNorm) { yPlanar.Y = 1.0; yPlanar.Normalize(); }
	pawn->AddMovementInput(yPlanar, offHandPlanarMovement.Y);



}