void IMainGame::mFunction_GameOverAnimationInit(BOOL hasPlayerWon)
{
	static std::default_random_engine rndEngine;
	static std::uniform_real_distribution<float> unitDist(-1.0f, 1.0f);

	if (hasPlayerWon)
	{
		mMainGameState = GameState::MainGame::GS_DeathExplode;
		//clear bullets
		mBulletMgr.KillAllBullet();
		//player WIN
		mIsPlayerVictorious = TRUE;
		//set camera to look at chicken
		gCamera.SetLookAt(mChickenBoss.GetPosition());
		//..explode fireworks
		for (int i = 0;i < 2000;++i)
		{
			//shoot direction (add some random offset)
			VECTOR3 dir = { unitDist(rndEngine),unitDist(rndEngine) ,unitDist(rndEngine) };
			//Y direction offset ( a whole column of bullets)
			dir.Normalize();
			mBulletMgr.SpawnBullet(mChickenBoss.GetPosition(), dir, VECTOR3(1, 0,0));
		}
	}
	else
	{
		mMainGameState = GameState::MainGame::GS_DeathExplode;
		//clear bullets
		mBulletMgr.KillAllBullet();
		//player LOSE
		mIsPlayerVictorious = FALSE;
		//..explode fireworks
		for (int i = 0;i < 2000;++i)
		{
			//shoot direction (add some random offset)
			VECTOR3 dir = { unitDist(rndEngine),unitDist(rndEngine) ,unitDist(rndEngine) };
			//Y direction offset ( a whole column of bullets)
			dir.Normalize();
			mBulletMgr.SpawnBullet(mPlayer.GetPosition(), dir, VECTOR3(1, 0, 0));
		}

		//move to another position to watch the explosion
		gCamera.SetPosition(mPlayer.GetPosition() + VECTOR3(300.0f,300.0f,300.0f));
		gCamera.SetLookAt(mPlayer.GetPosition());
	}
}