void CannonTower::Fire(){
	//Get closest enemy
	Enemy * enemy = mGame.GetWorld().GetClosestEnemy(GetWorldTransform().GetTranslation());
	if (enemy == nullptr)
		return;

	//Turn to enemy direction
	SetRotation(0);
	Vector3 enemyDir = enemy->GetPosition() - GetWorldTransform().GetTranslation();
	enemyDir.Normalize();
	Vector3 towerPos = GetWorldTransform().GetTranslation();
	float angle = Math::Acos(Dot(enemyDir, Vector3::UnitX));
	float crossZ = Cross(Vector3::UnitX, enemyDir).z;
	if (crossZ < 0.0f){
		angle *= -1.0f;
	}
	SetRotation(angle);

	//Fire the ball
	auto ball = CannonBall::Spawn(mGame);
	ball->SetPosition(GetWorldTransform().GetTranslation());
	ball->SetRotation(angle);

	//Trigger the sound
	mAudio->PlaySound(mShottingSound);
}