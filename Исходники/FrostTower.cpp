void FrostTower::FrostEnemies(){
	//Get the near enemies vector
	std::vector<Enemy *> enemies = mGame.GetWorld().GetEnemiesInRange(GetWorldTransform().GetTranslation(), 100.0f);

	for (Enemy * enemy : enemies){
		enemy->Slow();
	}
}