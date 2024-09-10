bool CEnmityContainer::IsWithinEnmityRange(CBattleEntity* PEntity)
{
	return distance(m_EnmityHolder->loc.p, PEntity->loc.p) <= m_EnmityHolder->m_enmityRange;
}