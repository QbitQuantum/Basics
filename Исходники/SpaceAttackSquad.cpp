// ----------------------------------------------------------------------
void SpaceAttackSquad::calculateAttackRanges()
{
	if (!isEmpty())
	{
		m_projectileAttackRange = FLT_MAX;
		m_weaponAttackRange = FLT_MAX;
	}

	UnitMap const & unitMap = getUnitMap();
	UnitMap::const_iterator iterUnitMap = unitMap.begin();

	for (; iterUnitMap != unitMap.end(); ++iterUnitMap)
	{
		CachedNetworkId const & unit = iterUnitMap->first;
		Object * const unitObject = unit.getObject();
		ServerObject * const unitServerObject = (unitObject != NULL) ? unitObject->asServerObject() : NULL;
		ShipObject * const unitShipObject = (unitServerObject != NULL) ? unitServerObject->asShipObject() : NULL;

		if (unitShipObject != NULL)
		{
			m_projectileAttackRange = std::min(m_projectileAttackRange, unitShipObject->getApproximateAttackRange());
			
			bool includeMissiles = true;
			m_weaponAttackRange = std::min(m_projectileAttackRange, unitShipObject->getApproximateAttackRange(includeMissiles));
		}
		else
		{
#ifdef _DEBUG
			FormattedString<1024> fs;
			char const * const text = fs.sprintf("SpaceAttackSquad::calculateProjectileAttackRange() ERROR: Could not convert unit(%s) to a ShipObject.", unit.getValueString().c_str());
			DEBUG_WARNING(true, (text));
			LOGC(ConfigServerGame::isSpaceAiLoggingEnabled(), "space_debug_ai", (text));
#endif // _DEBUG
		}
	}

	LOGC(ConfigServerGame::isSpaceAiLoggingEnabled(), "space_debug_ai", ("SpaceAttackSquad::calculateProjectileAttackRange() m_projectileAttackRange(%.0f) m_weaponAttackRange(%.0f)", m_projectileAttackRange, m_weaponAttackRange));
}