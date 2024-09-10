void ComponentWallConstruction::buildingPhase()
{
	parent->position = graphicsEngine->getMousePositionOnGround();
	Vector2d pos = aiAux->getFrame(parent->position);
	lastPosition = aiAux->getFrameCenter(pos.y,pos.x);
	bresenham();

	begin->setRotation((lastPosition-firstPosition).getAngle());
	end->setPosition(lastPosition);
	end->setRotation((firstPosition-lastPosition).getAngle());

	if(aiAux->checkMap(aiAux->getFrame(lastPosition).y,aiAux->getFrame(lastPosition).x) == 'W' || lastPosition.getSqrDistanceFrom(Vector2d(900,0)) < 122500)
	{
		canBuild = false;
	}
	else
	{
		canBuild = true;
	}
	float distance = firstPosition.getDistanceFrom(lastPosition);
	Vector2d center = lastPosition+((firstPosition-lastPosition).normalize() * distance/2);
		
	float scale = (distance-10)/15;
	if(scale>0)
	{
		wall->setPosition(center);
		wall->setScale(Vector3d(scale,1,1));
		wall->setRotation((lastPosition-firstPosition).getAngle());
	}
	else
	{
		wall->setPosition(Vector2d(5000,5000));
	}

	if(firstPosition == lastPosition)
	{
		canBuild = false;
	}

	if(canBuild)
	{
		Vector2d direction = firstPosition - lastPosition;
		direction.normalize();
		direction *= 5;
		Vector2d downright = (firstPosition+direction*4/5*-1).rotateBy(90,firstPosition+direction);
		Vector2d downleft = (firstPosition+direction*4/5*-1).rotateBy(-90,firstPosition+direction);
		Vector2d upright = (lastPosition+direction*4/5).rotateBy(-90,lastPosition-direction);
		Vector2d upleft = (lastPosition+direction*4/5).rotateBy(90,lastPosition-direction);
		/*if(!GameManager::getInstance()->isServer())
		{
			GameManager::getInstance()->getGraphicsEngine()->drawDebugLine(upright.asVector3d(),downright.asVector3d());
			GameManager::getInstance()->getGraphicsEngine()->drawDebugLine(downright.asVector3d(),downleft.asVector3d());
			GameManager::getInstance()->getGraphicsEngine()->drawDebugLine(downleft.asVector3d(),upleft.asVector3d());
			GameManager::getInstance()->getGraphicsEngine()->drawDebugLine(upleft.asVector3d(),upright.asVector3d());
		}*/
		std::vector<GameObject*> list = GameManager::getInstance()->getCollisionManager()->getGameObjectBetween(upright, upleft, downright, downleft);
		if(list.size() > 0)
		{
			canBuild = false;
		}
	}

	if(canBuild)
	{
		begin->setColor(2);
		end->setColor(2);
	}
	else
	{
		begin->setColor(0);
		end->setColor(0);
	}
	Vector2d textPosition = Vector2d(30,-30) + lastPosition;
	priceToShow->setText((std::to_wstring(price*distance)).c_str());
	priceToShow->setPosition(textPosition);

	if(GameManager::getInstance()->getEventManager()->mouseState.leftButtonDown)
	{
		if(canBuild)
		{
			Message message;
			message.type = Message::TRY_BUY;
			message.value = price*distance;
			message.gameObject = parent;
			GameManager::getInstance()->getGameObjectManager()->getMainPlayer()->broadcastMessage(message);
		}	
	}
}