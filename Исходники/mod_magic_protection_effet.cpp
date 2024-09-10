//--------------------------------------------------------------
bool CModMagicProtectionEffect::update(CTimerEvent * event, bool applyEffect)
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
	player->setUnclampedMagicProtection( _AffectedProtection, player->getUnclampedMagicProtection(_AffectedProtection) + _Modifier1 + _Modifier2 );
	return false;
} // update //