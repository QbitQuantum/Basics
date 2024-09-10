void AttackStuff(NXWSOCKET  s, P_CHAR victim)
{
	if ( s < 0 || s >= now )
		return;

	P_CHAR attacker = MAKE_CHAR_REF( currchar[s] );
	VALIDATEPC( attacker );
	VALIDATEPC( victim );

	if( attacker->getSerial32() == victim->getSerial32() )
		return;

	
	if ( attacker->amxevents[EVENT_CHR_ONBEGINATTACK]) {
		g_bByPass = false;
		attacker->amxevents[EVENT_CHR_ONBEGINATTACK]->Call( attacker->getSerial32(), victim->getSerial32() );
		if (g_bByPass==true) return;
	}

	if ( victim->amxevents[EVENT_CHR_ONBEGINDEFENSE]) {
		g_bByPass = false;
		victim->amxevents[EVENT_CHR_ONBEGINDEFENSE]->Call( victim->getSerial32(), attacker->getSerial32() );
		if (g_bByPass==true) return;
	}
	/*
	attacker->runAmxEvent( EVENT_CHR_ONBEGINATTACK, attacker->getSerial32(), victim->getSerial32() );
	if (g_bByPass==true)
		return;
	victim->runAmxEvent( EVENT_CHR_ONBEGINDEFENSE, victim->getSerial32(), attacker->getSerial32() );
	if (g_bByPass==true)
		return;
	*/
	attacker->targserial=victim->getSerial32();
	attacker->unHide();
	attacker->disturbMed();

	if( victim->dead || victim->hp <= 0 )//AntiChrist
	{
		attacker->sysmsg( TRANSLATE("That person is already dead!") );
		return;
	}

	if ( victim->npcaitype==NPCAI_PLAYERVENDOR)
	{
		attacker->sysmsg( TRANSLATE("%s cannot be harmed."), victim->getCurrentNameC() );
		return;
	}

	SndAttackOK(s, victim->getSerial32());	//keep the target highlighted
	if (!( victim->targserial== INVALID))
	{
		victim->attackerserial=attacker->getSerial32();
		victim->ResetAttackFirst();
	}
	attacker->SetAttackFirst();
	attacker->attackerserial=victim->getSerial32();

	if( victim->guarded )
	{
		NxwCharWrapper sc;
		sc.fillOwnedNpcs( victim, false, false );
		for ( sc.rewind(); !sc.isEmpty(); sc++ )
		{
			P_CHAR guard = sc.getChar();
			if ( ISVALIDPC( guard ) )
				if ( guard->npcaitype == NPCAI_PETGUARD && ( attacker->distFrom( guard )<= 10 ) )
					npcattacktarget(attacker, guard);
		}
	}

	if ((region[ victim->region].priv & RGNPRIV_GUARDED) && (SrvParms->guardsactive))
	{
		if (victim->IsGrey())
			attacker->SetGrey();

		if (victim->npc==0 && victim->IsInnocent() && (!victim->IsGrey()) && Guildz.compareGuilds( attacker->getGuild(), victim->getGuild() )==0) //REPSYS
		{
			criminal( attacker );
			if (ServerScp::g_nInstantGuard==1)
				npcs::SpawnGuard(attacker, victim,attacker->getPosition() );
		}
		else if( victim->npc && victim->IsInnocent() && !victim->HasHumanBody() && victim->npcaitype!=NPCAI_TELEPORTGUARD )
		{
			criminal( attacker );
			if (ServerScp::g_nInstantGuard==1)
				npcs::SpawnGuard(attacker, victim, attacker->getPosition() );
		}
		else if( victim->npc && victim->IsInnocent() && victim->HasHumanBody() && victim->npcaitype!=NPCAI_TELEPORTGUARD )
		{
			victim->talkAll( TRANSLATE("Help! Guards! I've been attacked!"), 1);
			criminal( victim );
			callguards(DEREF_P_CHAR(victim)); // Sparhawk must check if npcs can call guards
		}
		else if( victim->npc && victim->npcaitype==NPCAI_TELEPORTGUARD)
		{
			criminal( attacker );
			npcattacktarget(victim, attacker);
		}
		else if ((victim->npc || victim->tamed) && !victim->war && victim->npcaitype!=NPCAI_TELEPORTGUARD)
		{
			victim->fight( attacker );
		}
		else
		{
			victim->setNpcMoveTime();
		}
		//attacker->emoteall( "You see %s attacking %s!", 1, attacker->getCurrentNameC(), victim->getCurrentNameC() );
	}
	else	// not a guarded area
	{
		if ( victim->IsInnocent())
		{
			if ( victim->IsGrey())
				attacker->SetGrey();
			if (!victim->npc && (!victim->IsGrey()) && Guildz.compareGuilds(attacker->getGuild(), victim->getGuild() )==0)
			{
				criminal( attacker );
			}
			else if (victim->npc && victim->tamed)
			{
				criminal( attacker );
				npcattacktarget(victim, attacker);
			}
			else if (victim->npc)
			{
				criminal( attacker );
				npcattacktarget(victim, attacker);
				if (victim->HasHumanBody() )
				{
					victim->talkAll(TRANSLATE("Help! Guards! Tis a murder being commited!"), 1);
				}
			}
		}
	}

}