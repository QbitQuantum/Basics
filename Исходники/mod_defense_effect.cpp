//--------------------------------------------------------------
//		CModDefenseEffect::update()
//--------------------------------------------------------------
bool CModDefenseEffect::update(CTimerEvent * event, bool applyEffect)
{
	if (!TheDataset.isAccessible(_TargetRowId))
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}

	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}
	
	switch( _Family )
	{
		case EFFECT_FAMILIES::PowerModDodgeSkill:
			player->incDodgeModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->dodgeSuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
			break;
		case EFFECT_FAMILIES::PowerModParrySkill:
			player->incParryModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->parrySuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
			break;
		case EFFECT_FAMILIES::PowerModDefenseSkill:
			player->incDodgeModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->incParryModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->dodgeSuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
			player->parrySuccessModifier( (sint32)(_Modifier1 + _Modifier2) );
			break;
		default:
			break;
	}
	
	return false;
} // update //