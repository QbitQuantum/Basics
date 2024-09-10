void EnemyAIModelHunt::makeDecision(MOC::CollisionTools *mCollisionTools, const Ogre::FrameEvent& evt, Enemy *enemy, ZombiePack **zombies, int nZombies)
{
	if (aux >= rate)
	{
		double x, z;
		movModel->calculateMove(enemy, zombies, nZombies, &x, &z);

		// Calculamos si está demasiado cerca:
		Ogre::Vector3 myPos = enemy->node->getPosition();
		if (myPos.distance(Ogre::Vector3(x, myPos.y, z)) < enemy->range*0.5)
		{
			x = 2 * myPos.x - x;
			z = 2 * myPos.z - z;
		}

		enemy->move(x, z);
	}

	enemy->update(mCollisionTools, evt, zombies);
}