void ComponentAIBomber::defenderSquad()
{

	//GameManager::getInstance()->getGraphicsEngine()->drawDebugLine(parent->position.asVector3d(), (parent->position + (Vector2d::getVector2dByAngle(-parent->rotation) * -30)).asVector3d(),2);
	int i=0;
	std::list<GameObject*>::iterator it;
	int cantRow = defenders.size();
	int separationBack = 260/defenders.size();
	for (it=defenders.begin(); it!=defenders.end(); ++it)
	{
		if(!(*it)->isDead())
		{
			Vector2d tv = Vector2d::getVector2dByAngle(-parent->rotation) * -1;
			//tv = Vector2d::getVector2dByAngle(parent->rotation);
			int angle = 260/cantRow;
			tv.normalize();

			int total = separationBack * (defenders.size()-1);
			tv.rotateBy(i*separationBack - total/2,Vector2d(0,0));
			tv.normalize();
			tv *= 15;
			//angulo igual a nueva pos mirando hacia player
			(*it)->position = parent->position + tv;
			if(players.empty())
			{
				float desiredRotation = parent->rotation;

				float newRotation = (*it)->rotation - desiredRotation;

				newRotation = Math::warpAngle(newRotation);

				if(Math::abs(newRotation) < 0.001)
				{
					(*it)->rotation = desiredRotation;
				} 
				else
				{
					(*it)->rotation -= newRotation * 0.2;
				}
			}
			else
			{
				float desiredRotation = (players.front()->position - (*it)->position).getAngle();

				float newRotation = (*it)->rotation - desiredRotation;

				newRotation = Math::warpAngle(newRotation);

				if(Math::abs(newRotation) < 0.001)
				{
					(*it)->rotation = desiredRotation;
				} 
				else
				{
					(*it)->rotation -= newRotation * 0.2;
				}
			}
			/*if(!GameManager::getInstance()->isServer())
			{
				GameManager::getInstance()->getGraphicsEngine()->drawDebugLine(parent->position.asVector3d(),(*it)->position.asVector3d());
			}*/
		}
		i++;
	}
}