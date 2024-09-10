void Enemy::CheckShooting(float dist, float deltaTime)
{

	PxExtendedVec3 tpPos = physics->player->getPosition();
	PxVec3 pPos = playerPos;
	PxVec3 ori = actor->getGlobalPose().p;
	PxVec3 dir = pPos - ori;
	dir.normalize();
	int numHits = 0;
	PxRaycastHit* hit = physics->RaycastMultiple(ori,dir,dist,&numHits, PxQueryFlag::eSTATIC | PxQueryFlag::eDYNAMIC);
	for(unsigned int i = 1; i < numHits; i++)
	{
		if(hit[i-1].actor == actor && hit[i].actor == physics->player->getActor())
		{
			sawPlayer = true;
			lastTimeShot+=deltaTime;
			if(lastTimeShot > shootDelay)
			{
				obj->PlayAnimation("Shoot",true);
				moveDir *= 0.1f;
				if(obj->GetCurrentAnim()->doAction)
				{
					CreateBullet(ori+dir*2,dir);
					currentMoveTime = 9999.0f;
					lastTimeShot = 0;
					resources->GetSoundHandler()->PlayWaveFile("piew");
					obj->GetCurrentAnim()->doAction = false;
				}
			}
		}
	}
}