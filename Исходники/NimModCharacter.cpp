void ANimModCharacter::OnCameraUpdate(const FVector& PreviousCameraLocation, const FVector& CameraLocation, const FRotator& CameraRotation)
{
	USkeletalMeshComponent* DefMesh1P = Cast<USkeletalMeshComponent>(GetClass()->GetDefaultSubobjectByName(TEXT("PawnMesh1P")));
	//USkeletalMeshComponent* DefMesh1P = Mesh1P;
	const FMatrix DefMeshLS = FRotationTranslationMatrix(DefMesh1P->RelativeRotation, DefMesh1P->RelativeLocation);
	const FMatrix LocalToWorld = ActorToWorld().ToMatrixWithScale();

	// Mesh rotating code expect uniform scale in LocalToWorld matrix

	const FRotator RotCameraPitch(CameraRotation.Pitch, 0.0f, 0.0f);
	const FRotator RotCameraYaw(0.0f, CameraRotation.Yaw, 0.0f);

	const FMatrix LeveledCameraLS = FRotationTranslationMatrix(RotCameraYaw, CameraLocation) * LocalToWorld.Inverse();
	const FMatrix PitchedCameraLS = FRotationMatrix(RotCameraPitch) * LeveledCameraLS;
	const FMatrix MeshRelativeToCamera = DefMeshLS * LeveledCameraLS.Inverse();
	const FMatrix PitchedMesh = MeshRelativeToCamera * PitchedCameraLS;

	//FVector origin = PitchedMesh.GetOrigin();
	FVector origin = Mesh1P->GetRelativeTransform().GetLocation();
	//FVector originalLocation = Mesh1P->GetRelativeTransform().GetLocation();
	////FVector origin = Mesh1P->ComponentToWorld.GetLocation();
	//if (bIsCrouched)
	//{
	//	//origin.Z = (origin.Z - (DefaultBaseEyeHeight - DefMesh1P->RelativeLocation.Z));
	//	origin.Z = (PreviousCameraLocation.Z - CameraLocation.Z);
	//}

	Mesh1P->SetRelativeLocationAndRotation(origin, PitchedMesh.Rotator(), false, nullptr, ETeleportType::TeleportPhysics);
	/*FVector newLocation = Mesh1P->GetRelativeTransform().GetLocation();
	int i = -1;*/
}