void IChickenMonster::mFunction_Fire(VECTOR3 shootDir)
{

	//different types of bullets have various cool down time
	const float fireTimeThreshold_common = 500.0f;
	const float fireTimeThreshold_rotate1 = 200.0f;
	const float fireTimeThreshold_rotate2 = 300.0f;
	const float fireTimeThreshold_explode = 2000.0f;
	static std::default_random_engine rndEngine;
	static std::uniform_real_distribution<float> dirDist1(-0.1f,0.1f);
	static std::uniform_real_distribution<float> dirDist2(-0.5f, 0.5f);
	static std::uniform_real_distribution<float> dirDist3(-1.0f, 1.0f);

	//update time counter
	attackPatternTimeCounter += gTimeElapsed;

	switch (mAttackState)
	{
	case CHICKEN_ATTACK_STATE_CHASE_PLAYER:
	{
		if (attackPatternTimeCounter > fireTimeThreshold_common)
		{
			shootDir.Normalize();

			for (int i = 0;i < 5;++i)
			{
				//shoot direction (add some random offset)
				VECTOR3 dir = shootDir + VECTOR3(dirDist1(rndEngine), dirDist1(rndEngine), dirDist1(rndEngine));
				m_pBulletMgr->SpawnBullet(mPos, dir*0.5f, VECTOR3(1.0f, 0, 0));
			}

			//time counter reset
			attackPatternTimeCounter = 0.0f;
		}
	}
	break;

	case CHICKEN_ATTACK_STATE_TYPE1:
	{
		if (attackPatternTimeCounter > fireTimeThreshold_rotate1)
		{
			shootDir.Normalize();

			for (int i = 0;i < 20;++i)
			{
				//shoot direction (add some random offset)
				VECTOR3 dir = { shootDir.x,0,shootDir.z };
				//Y direction offset ( a whole column of bullets)
				dir.y += ((-10 + i) * 0.1f);
				dir.Normalize();
				m_pBulletMgr->SpawnBullet(mPos, dir*0.5f, VECTOR3(1.0f, 0, 0));
			}

			//time counter reset
			attackPatternTimeCounter = 0.0f;
		}
		break;
	}

	case CHICKEN_ATTACK_STATE_TYPE2:
	{
		if (attackPatternTimeCounter > fireTimeThreshold_rotate2)
		{
			shootDir.Normalize();

			for (int i = 0;i < 20;++i)
			{
				VECTOR3 dir = shootDir + VECTOR3(dirDist2(rndEngine), dirDist2(rndEngine), dirDist2(rndEngine));
				m_pBulletMgr->SpawnBullet(mPos, dir, VECTOR3(0,1.0f, 0));
			}

			//time counter reset
			attackPatternTimeCounter = 0.0f;
		}
		break;
	}

	case CHICKEN_ATTACK_STATE_ULTIMATE_EXPLODE:
	{
		if (attackPatternTimeCounter > fireTimeThreshold_explode)
		{
			for (int i = 0;i < 1000;++i)
			{
				//shoot direction (add some random offset)
				VECTOR3 dir = { dirDist3(rndEngine),dirDist3(rndEngine) ,dirDist3(rndEngine) };
				//Y direction offset ( a whole column of bullets)
				dir.Normalize();
				m_pBulletMgr->SpawnBullet(mPos, dir, VECTOR3(0, 0, 1.0f));
			}
			attackPatternTimeCounter = 0.0f;
		}
		break;
	}

	default:
		break;
	}

}