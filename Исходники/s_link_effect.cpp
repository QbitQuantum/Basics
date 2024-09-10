//-----------------------------------------------
// CSLinkEffectOffensive updateOffensive
//-----------------------------------------------
bool CSLinkEffectOffensive::updateOffensive(CTimerEvent * event, bool sendReportForXP)
{
	if ( CSLinkEffect::update(event,true) )
		return true;

	CEntityBase * target = CEntityBaseManager::getEntityBasePtr( _TargetRowId );
	if ( !target )
	{
		nlwarning("<CSLinkEffectDot update> Invalid target %u",_TargetRowId.getIndex() );
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}

	// if target is now protected, cancel the effect
	CSEffect *effect = target->lookForActiveEffect(EFFECT_FAMILIES::PowerAntiMagicShield);
	if (effect)
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}

	// test target is still valid for a link (can happen in PVP or duel)
	string errorCode;
	if ( !PHRASE_UTILITIES::validateSpellTarget(_CreatorRowId, _TargetRowId, ACTNATURE::OFFENSIVE_MAGIC, errorCode, true ) )
	{
		_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
		return true;
	}

	if (_LinkExists)
	{
		CEntityBase * caster = CEntityBaseManager::getEntityBasePtr( _CreatorRowId );
		if ( !caster )
		{
			nlwarning("<CSLinkEffectDot update> Invalid caster %u",_CreatorRowId.getIndex() );
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			return true;
		}
	
		// test resistance
		if ( !_FirstResist && !EntitiesNoResist)
		{
			uint32 resistValue = 0;
			if (_Family == EFFECT_FAMILIES::Dot)
			{
				CSLinkEffectDot *dot = dynamic_cast<CSLinkEffectDot*> (this);
				if (dot)
				{
					resistValue = target->getMagicResistance(dot->getDamageType());
				}
			}
			else
			{
				resistValue = target->getMagicResistance(_Family);
			}

			sint skillValue = 0;
			if ( caster->getId().getType() == RYZOMID::player )
			{
				CCharacter * pC = (CCharacter *) caster;
				skillValue = pC->getSkillValue( _Skill );
			}
			else
			{
				const CStaticCreatures * form = caster->getForm();
				if ( !form )
				{
					nlwarning( "<MAGIC>invalid creature form %s in entity %s", caster->getType().toString().c_str(), caster->getId().toString().c_str() );
					_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
					return true;
				}	
				skillValue = form->getAttackLevel();
			}

			const CSEffect* debuff = caster->lookForActiveEffect( EFFECT_FAMILIES::DebuffSkillMagic );
			if ( debuff )
				skillValue -= debuff->getParamValue();
			const CSEffect * outPostBuff = caster->lookForActiveEffect( EFFECT_FAMILIES::OutpostMagic );
			if ( outPostBuff )
				skillValue += outPostBuff->getParamValue();

			// cap skill values with brick power
			if ( (sint32)_Power < skillValue )
				skillValue = (sint32)_Power;
			
			if ( caster->getId().getType() == RYZOMID::player )
			{
				CCharacter * pC = dynamic_cast<CCharacter *>( caster );
				if( pC )
				{
					// boost magic skill for low level chars
					sint sb = (sint)MagicSkillStartValue.get();
					skillValue = max( sb, skillValue );

					// add magic boost from consumable
					skillValue += pC->magicSuccessModifier();
				}
			}

			// test resistance
			const uint8 roll = (uint8)RandomGenerator.rand( 99 );
			_ResistFactor = CStaticSuccessTable::getSuccessFactor(SUCCESS_TABLE_TYPE::MagicResistLink, skillValue - resistValue, roll);

			// increase target resistance
			if (_ResistFactor > 0.0f)
			{
				if (_Family == EFFECT_FAMILIES::Dot)
				{
					CSLinkEffectDot *dot = dynamic_cast<CSLinkEffectDot*> (this);
					if (dot)
					{
						target->incResistModifier(dot->getDamageType(), _ResistFactor);
					}
				}
				else
				{
					target->incResistModifier(_Family,_ResistFactor);
				}
			}

			// delta level for XP gain 
			// opponent must be a creature or an npc to gain xp
			_Report.DeltaLvl = skillValue - resistValue;
			if (target->getId().getType() != RYZOMID::player && caster->getId().getType() == RYZOMID::player)
			{
				CCreature *creature = dynamic_cast<CCreature*> (target);
				if (!creature)
				{
					nlwarning("Entity %s type is creature but dynamic_cast in CCreature * returns NULL ?!", target->getId().toString().c_str());
					_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
					return true;
				}
				CCharacter * pC = dynamic_cast<CCharacter*> (caster);
				if (!pC)
				{
					nlwarning("Entity %s type is player but dynamic_cast in CCharacter * returns NULL ?!", caster->getId().toString().c_str());
					_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
					return true;
				}

				const CStaticCreatures* form = creature->getForm();
				if (form)
					_Report.DeltaLvl =  pC->getSkillValue(_Skill) - form->getXPLevel();
				else
					sendReportForXP = false;
			}
			else
				sendReportForXP = false;
		}
		else
		{
			_FirstResist = false;
			_ResistFactor = 1.0f;
		}
		
		bool end = true;
		// resist if factor <= 0
		if ( _ResistFactor > 0.0f  )
		{
			end = false;
			if ( _ResistFactor > 1.0f )
			{
				_ResistFactor = 1.0f;
			}

			// send report for XP			
			_Report.factor = _ResistFactor;

			if (sendReportForXP)
			{
				PROGRESSIONPVE::CCharacterProgressionPVE::getInstance()->actionReport( _Report );
				PROGRESSIONPVP::CCharacterProgressionPVP::getInstance()->reportAction(_Report);
			}
		}
		else
		{
			PHRASE_UTILITIES::sendSpellResistMessages( _CreatorRowId, _TargetRowId);
		}

		//////////////////////////////////////////////////////////////////////////
		// TEMPORARY : SEND AGGRO MESSAGE FOR EVERY UPDATE OF OFFENSIVE LINKS
		//////////////////////////////////////////////////////////////////////////	
		CAiEventReport report;
		report.Originator = _CreatorRowId;
		report.Target = _TargetRowId;
		report.Type = ACTNATURE::OFFENSIVE_MAGIC;		
		report.AggroAdd = -0.01f;
		CPhraseManager::getInstance().addAiEventReport(report);
		//////////////////////////////////////////////////////////////////////////
				
		if (end)
		{
			_EndTimer.setRemaining(1, new CEndEffectTimerEvent(this));
			return true;
		}
	}
	else
	{
		// no link -> no possible resist ?
	}

	return false;
} // CSLinkEffectOffensive::updateOffensive //