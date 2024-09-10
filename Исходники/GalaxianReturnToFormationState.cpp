void GalaxianReturnToFormationState::Update(Galaxian* a_galaxian, float a_fDeltaTime)
{
	m_deltaTimeMap[a_galaxian] += a_fDeltaTime;
	if(m_referanceMap[a_galaxian]->m_state == EntityState::REMOVED)
	{
		m_referanceMap[a_galaxian] = m_formation->GetFirstGalaxianInFormation();
	}
	Vector2 referancePosition = m_referanceMap[a_galaxian]->GetPosition();
	int xOffset = a_galaxian->GetPositionInFormation().x - m_referanceMap[a_galaxian]->GetPositionInFormation().x;
	int yOffset = a_galaxian->GetPositionInFormation().y - m_referanceMap[a_galaxian]->GetPositionInFormation().y;
	Vector2 targetPosition = referancePosition + Vector2(xOffset * (GalaxianFormation::SPRITE_WIDTH+12), yOffset * (GalaxianFormation::SPRITE_HEIGHT+6));

	if(a_galaxian->GetPosition().Distance(targetPosition) > 5)
	{
		Vector2 direction = targetPosition - a_galaxian->GetPosition();
		direction.Normalize();
		a_galaxian->Move(direction * a_fDeltaTime * 200);
	}
	else
	{
		a_galaxian->SetPosition(targetPosition);
		a_galaxian->SetDirection(Vector2(0,1));
		a_galaxian->ChangeState(GalaxianInFormationState::getInstance());
	}
}