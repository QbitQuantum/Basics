CString CAISettings::SetValue (const CString &sSetting, const CString &sValue)

//	SetValue
//
//	Set AISettings value

	{
	if (strEquals(sSetting, AGGRESSOR_ATTRIB))
		m_fAggressor = !sValue.IsBlank();
	else if (strEquals(sSetting, ASCEND_ON_GATE_ATTRIB))
		m_fAscendOnGate = !sValue.IsBlank();
	else if (strEquals(sSetting, COMBAT_SEPARATION_ATTRIB))
		m_rMinCombatSeparation = Max(1, strToInt(sValue, 1)) * g_KlicksPerPixel;
	else if (strEquals(sSetting, COMBAT_STYLE_ATTRIB))
		m_iCombatStyle = ConvertToAICombatStyle(sValue);
	else if (strEquals(sSetting, FIRE_ACCURACY_ATTRIB))
		m_iFireAccuracy = Max(0, Min(strToInt(sValue, 100), 100));
	else if (strEquals(sSetting, FIRE_RANGE_ADJ_ATTRIB))
		m_iFireRangeAdj = Max(1, strToInt(sValue, 100));
	else if (strEquals(sSetting, FIRE_RATE_ADJ_ATTRIB))
		m_iFireRateAdj = Max(1, strToInt(sValue, 10));
	else if (strEquals(sSetting, NO_DOGFIGHTS_ATTRIB))
		m_fNoDogfights = !sValue.IsBlank();
	else if (strEquals(sSetting, NO_SHIELD_RETREAT_ATTRIB))
		m_fNoShieldRetreat = !sValue.IsBlank();
	else if (strEquals(sSetting, NO_FRIENDLY_FIRE_ATTRIB))
		m_fNoFriendlyFire = !sValue.IsBlank();
	else if (strEquals(sSetting, NO_FRIENDLY_FIRE_CHECK_ATTRIB))
		m_fNoFriendlyFireCheck = !sValue.IsBlank();
	else if (strEquals(sSetting, NO_NAV_PATHS_ATTRIB))
		m_fNoNavPaths = !sValue.IsBlank();
	else if (strEquals(sSetting, NO_ORDER_GIVER_ATTRIB))
		m_fNoOrderGiver = !sValue.IsBlank();
	else if (strEquals(sSetting, NON_COMBATANT_ATTRIB))
		m_fNonCombatant = !sValue.IsBlank();
	else if (strEquals(sSetting, PERCEPTION_ATTRIB))
		m_iPerception = Max((int)CSpaceObject::perceptMin, Min(strToInt(sValue, CSpaceObject::perceptNormal), (int)CSpaceObject::perceptMax));
	else
		return NULL_STR;

	return GetValue(sSetting);
	}