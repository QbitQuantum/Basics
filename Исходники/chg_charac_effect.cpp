//--------------------------------------------------------------
//		CChgCharacEffect::removed()
//--------------------------------------------------------------
void CChgCharacEffect::removed()
{
	// reset modifier to it's old value
	CCharacter *player = PlayerManager.getChar(_TargetRowId);
	if (!player)
	{
		nlwarning("Cannot find target entity %s", _TargetRowId.toString().c_str());
		return;
	}
	
	//player->getScores()._PhysicalScores[_AffectedScore].RegenerateModifier -= _RegenModifier;
	string var = "Modifier" + _AffectedCharac;

	string currentValueStr;
	player->getValue(var,currentValueStr);
	sint32 currentValue;
	NLMISC::fromString(currentValueStr, currentValue);
	string newValueStr = toString(currentValue - _Modifier1 - _Modifier2);
	player->setValue(var,newValueStr);
}