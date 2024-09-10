void CJaw::OnDropped( EntityId actorId, bool ownerWasAI)
{
	CItem::OnDropped(actorId, ownerWasAI);

	IEntity* pEntity = GetEntity();

	uint32 flags = pEntity->GetFlags();	
	flags &= ~ENTITY_FLAG_NO_PROXIMITY;
	pEntity->SetFlags(flags);

	m_expended_ammo = 0;

	m_laserGuider.TurnOffLaser();
}