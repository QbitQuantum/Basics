void PlayerSprite::update( float delta )
{
	b2ContactEdge* ce = m_pB2Body->GetContactList();
	list<BaseSprite*> desList;

	while (ce)
	{
		b2Body* body = ce->contact->GetFixtureA()->GetBody();
		BaseSprite* sprite = (BaseSprite*)body->GetUserData();

		if (sprite->getTag() == kEnemySprite)
		{
			desList.push_back(sprite);
		}
		ce = ce->next;
	}

	for (list<BaseSprite*>::iterator it = desList.begin(); it != desList.end(); it++)
	{
		CCPoint dir = (*it)->getPosition() - getPosition();
		dir = dir.normalize();

		float sita = CC_RADIANS_TO_DEGREES(acos(dir.dot(CCPoint(0, 1))));
		ElementColor hitColor;

		//cos值域在(0,180)，修正在(180,360)的情况
		if (dir.x < 0)
		{
			sita = 360 - sita;
		}
		sita += getRotation();

		while (sita < 0) 
		{
			sita += 360;
		}
		sita = (int)sita % 360;

		if (sita >=0 && sita < 120)
		{
			hitColor = kGreen;
		}
		else if (sita >= 120 && sita < 240)
		{
			hitColor = kRed;
		}
		else
		{
			hitColor = kBlue;
		}

		EnemySprite* esp = dynamic_cast<EnemySprite*>(*it);
		if (!esp) continue;

		if (hitColor == esp->getElementColor())
		{
			HudLayer::getCurrent()->score(g_ScoreStep);
		}

		GameLayer::getCurrent()->getGameBg()->changeBgColor(esp->getElementColor());

		(*it)->destroySprite();
	}
	desList.clear();

	keyBoardHandle();
}