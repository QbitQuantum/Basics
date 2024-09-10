void ABounceBlock::OnHit(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//衝突された場合の判定
	UE_LOG(LogTemp, Log, TEXT("On Hit Call!"));

	//横方向に限定して弾き返す
	float speed = NormalImpulse.Size();
	NormalImpulse.Z = 0;

	//ベロシティを反射方向に導く
	FVector velocity = OtherComp->GetComponentVelocity();
	float power = velocity.Size();
	if (power > 0.0f){
		NormalImpulse.Normalize();
		NormalImpulse = velocity + 2 * (-velocity | NormalImpulse) * NormalImpulse;

		power = NormalImpulse.Size();
		NormalImpulse.Z = 0;
		NormalImpulse.Normalize();

		NormalImpulse *= power;

		OtherComp->SetPhysicsLinearVelocity(NormalImpulse);
	}

	//トルクを0にしてみる
	OtherComp->SetPhysicsAngularVelocity(FVector(0, 0, 0));

	//弾き返す！！
	//OtherComp->AddImpulseAtLocation(NormalImpulse * 2.0f, Hit.Location);

}