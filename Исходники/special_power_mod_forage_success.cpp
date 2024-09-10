//--------------------------------------------------------------
//					apply()  
//--------------------------------------------------------------
void CSpecialPowerModForageSuccess::apply()
{
	if (!_Phrase)
		return;

	CCharacter *actor = PlayerManager.getChar(_ActorRowId);
	if (!actor)
	{
		nlwarning("<CSpecialPowerModForageSuccess::apply> Cannot find actor entity or not a player");
		return;
	}

	// disable power
	actor->forbidPower(_PowerType, _Phrase->getConsumableFamilyId(), CTickEventHandler::getGameCycle() + _DisablePowerTime);

	const TGameCycle endDate = _Duration + CTickEventHandler::getGameCycle();

	// create effect and apply it on target
	EFFECT_FAMILIES::TEffectFamily effectFamily;
	ECOSYSTEM::EECosystem eco = ECOSYSTEM::stringToEcosystem(_Ecosystem);
	switch( eco )
	{
		case ECOSYSTEM::common_ecosystem:
			effectFamily = EFFECT_FAMILIES::PowerModForageSkill;
			break;
		case ECOSYSTEM::desert:
			effectFamily = EFFECT_FAMILIES::PowerModDesertForageSkill;
			break;
		case ECOSYSTEM::forest:
			effectFamily = EFFECT_FAMILIES::PowerModForestForageSkill;
			break;
		case ECOSYSTEM::lacustre:
			effectFamily = EFFECT_FAMILIES::PowerModLacustreForageSkill;
			break;
		case ECOSYSTEM::jungle:
			effectFamily = EFFECT_FAMILIES::PowerModJungleForageSkill;
			break;
		case ECOSYSTEM::primary_root:
			effectFamily = EFFECT_FAMILIES::PowerModPrimaryRootForageSkill;
			break;
		default:
			nldebug("<CSpecialPowerModForageSuccess::apply> The ecosystem '%s' is not managed by this special power",_Ecosystem.c_str());
			return;
	}

	CModForageSuccessEffect *effect = new CModForageSuccessEffect(_ActorRowId, 
													endDate, 
													effectFamily,
													_Ecosystem,
													_Modifier1,
													_Modifier2);
	if (!effect)
	{
		nlwarning("<CSpecialPowerModForageSuccess::apply> Failed to allocate new CModForageSuccessEffect");
		return;
	}

	actor->addSabrinaEffect(effect);

	// send messages
	SM_STATIC_PARAMS_1(params, STRING_MANAGER::power_type);
//	TVectorParamCheck params;
	// for actor
	if (actor->getId().getType() == RYZOMID::player)
	{
		params[0].Enum = _PowerType;
		PHRASE_UTILITIES::sendDynamicSystemMessage(_ActorRowId, "POWER_USE", params);
	}
} // apply //