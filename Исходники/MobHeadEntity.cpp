void cMobHeadEntity::SetOwner(const AString & a_Owner)
{
	if ((a_Owner.length() > 16) || (m_Type != SKULL_TYPE_PLAYER))
	{
		return;
	}
	m_Owner = a_Owner;
}