void MonsterTwoSprite::AI(Point playerPos)
{
	NPCSprite::AI(playerPos);

	//实现自己的AI

	Point pos = getPosition();

	//怪物比玩家的x坐标大表示怪物在右边
	if (pos.x > playerPos.x)
	{
		m_npc->changeDir(Left);
		setScaleX(1);
	}
	else
	{
		m_npc->changeDir(Right);
		setScaleX(-1);
	}

	float distance = pos.distance(playerPos);

	if (distance <= MONSTER_AI_SHOOT_DISTANCE)
	{
		this->startShoot();
	}
	else
	{
		this->closeShoot();
	}
}