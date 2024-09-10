// ----------------------------------------------------------------------
bool Squad::setLeader(NetworkId const & unit, bool const rebuildFormation)
{
	LOGC(ConfigServerGame::isSpaceAiLoggingEnabled(), "space_debug_ai", ("Squad::setLeader() className(%s) squadId(%d) unit(%s) rebuildFormation(%s)", getClassName(), m_id, unit.getValueString().c_str(), rebuildFormation ? "yes" : "no"));

	if (   isEmpty()
	    && (unit == NetworkId::cms_invalid))
	{
		m_leader = CachedNetworkId::cms_cachedInvalid;

		return true;
	}

	bool result = false;
	UnitMap::iterator iterUnitMap = m_unitMap->find(CachedNetworkId(unit));

	if (iterUnitMap != m_unitMap->end())
	{
		result = true;

		NetworkId oldLeader(m_leader);
		m_leader = CachedNetworkId(unit);
		onNewLeader(oldLeader);

		if (rebuildFormation)
		{
			m_formation.markDirty();
		}
	}
	else
	{
		m_leader = CachedNetworkId::cms_cachedInvalid;

#ifdef _DEBUG
		FormattedString<1024> fs;
		char const * const text = fs.sprintf("Squad::setLeader() ERROR: className(%s) Trying to set a leader(%s) who is not a member of the squad.", getClassName(), unit.getValueString().c_str());
		DEBUG_WARNING(true, (text));
		LOGC(ConfigServerGame::isSpaceAiLoggingEnabled(), "space_debug_ai", (text));
#endif // _DEBUG
	}

	return result;
}