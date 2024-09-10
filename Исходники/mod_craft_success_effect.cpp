//--------------------------------------------------------------
//		activate
//--------------------------------------------------------------
void CModCraftSuccessEffect::activate()
{
	CCharacter *actor = PlayerManager.getChar(_CreatorEntityId);
	if (!actor)
	{
		nlwarning("<CModCraftSuccessEffect::activate> Cannot find actor entity or not a player");
		return;
	}
	
	CModCraftSuccessEffect *effect = new CModCraftSuccessEffect(actor->getEntityRowId(), 
		getEndDate()+CTickEventHandler::getGameCycle(), 
		EFFECT_FAMILIES::PowerModCraftSkill,
		_Modifier1,
		_Modifier2);
	
	if (!effect)
	{
		nlwarning("<CModCraftSuccessEffect::activate> Failed to allocate new CModCraftSuccessEffect");
		return;
	}
	actor->addSabrinaEffect(effect);
}