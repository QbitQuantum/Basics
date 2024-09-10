const Vec2& GameData::getNearTargetByPos( const Vec2& curPos )
{
	Vec2 nearPos = Vec2(0,0);
	float dis = 100000.0f;
	auto plVec = m_EnemyPlaneVec;
	for (auto it = plVec.begin(); it != plVec.end(); it++)
	{
		auto pl = (*it);
		if (pl)
		{
			Vec2 pos = pl->convertToWorldSpaceAR(Vec2::ZERO);
			float TempDis = pos.distance(curPos);
			if (TempDis < dis)
			{
				dis = TempDis;
				nearPos = pos;
			}
		}
		else
		{
			log("");
		}
	}
	return nearPos;
}