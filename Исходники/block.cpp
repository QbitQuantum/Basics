// Wall2D의 노말벡터가 블럭의 바깥을 바라보게 한다
void CBlock::CalculateNormal()
{
	// 중점을 구한다
	Vector2D center(0,0);
	list<Wall2D*>::iterator itor = m_WallList.begin();
	while (itor != m_WallList.end())
	{
		center += (*itor)->From();
		++itor;
	}

	center /= (float)m_WallList.size();

	// 중점과 노말벡터가 마주본다면 반전시킨다
	itor = m_WallList.begin();
	while (itor != m_WallList.end())
	{
		Vector2D line = (*itor)->From() + (*itor)->To();
		line /= 2.f;
		const Vector2D centerToLine = line - center;
		const double dot = centerToLine.Dot((*itor)->Normal());

		if (dot <= 0.f)
		{
			Vector2D to = (*itor)->To();
			(*itor)->SetTo((*itor)->From());
			(*itor)->SetFrom(to);
		}
		++itor;
	}

}