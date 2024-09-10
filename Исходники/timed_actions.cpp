//-----------------------------------------------
bool CTimedAction::testCancelOnHit( sint32 attackSkillValue, CEntityBase * attacker, CEntityBase * defender)
{
	// get defender defense skill
	sint32 defenderValue;
	if ( defender->getId().getType() == RYZOMID::player )
	{
		CCharacter *pC = dynamic_cast<CCharacter*> (defender);
		if (!pC)
		{
			nlwarning("Entity %s type is player but dynamic_cast in CCharacter * returns NULL ?!", defender->getId().toString().c_str());
			return false;
		}
		defenderValue = pC->getSkillValue(pC->getBestSkill());
	}
	else
	{
		const CStaticCreatures * form = defender->getForm();
		if ( !form )
		{
			nlwarning( "<MAGIC>invalid creature form %s in entity %s", defender->getType().toString().c_str(), defender->getId().toString().c_str() );
			return false;
		}	
		defenderValue = form->getAttackLevel();
	}
	
	//test if the spell is broken
	const uint8 chances = CStaticSuccessTable::getSuccessChance( SUCCESS_TABLE_TYPE::BreakCastResist, defenderValue - attackSkillValue);
	const uint8 roll = (uint8) RandomGenerator.rand(99);
	
	if ( roll >= chances )
		return true;
	else
		return false;
}