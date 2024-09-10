bool CBoxBehaviorState::IsPutable(CCSprite* sprite, CCPoint touchPos, CCPoint& avaliablePos)
{
	auto arr = CObjectManager::getInstance()->getBox2dSprite();
	CCPoint setPos;
	bool bIsEnable = true;
	CCRect rect;

	for (int i = 0; i <= 20; i++)
	{
		for (int j = 0; j <= 20; j++)
		{
			CCRect r;
			r.setRect(i * 105 + CScrollManager::getInstance()->getDeltaPosition().x, j * 105 + CScrollManager::getInstance()->getDeltaPosition().y, 105, 105);

			if (r.containsPoint(touchPos))
			{
				setPos = ccp(r.getMidX(), r.getMidY());
				rect = r;
			}
		}
	}

	for (int i = 0; i < arr->getSize(); i++)
	{
		auto anothersprite = arr->getObjectAt(i)->getSpritePtr();

		if (rect.intersectsRect(anothersprite->getBoundingBox()))
			bIsEnable = false;
	}

	avaliablePos = setPos;
	return bIsEnable;
}