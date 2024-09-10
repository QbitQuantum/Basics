/*!
\brief Steal something
\author Unknow, completly rewritten by Endymion
\param ps the client
*/
void Skills::target_stealing( NXWCLIENT ps, P_TARGET t )
{
	P_CHAR thief = ps->currChar();
	VALIDATEPC(thief);
	SERIAL target_serial = t->getClicked();

	AMXEXECSVTARGET( thief->getSerial32(),AMXT_SKITARGS,STEALING,AMX_BEFORE);

	//steal a char
	if ( isCharSerial(target_serial) )
	{
		Skills::target_randomSteal(ps,t);
        	return;
	}

	const P_ITEM pi = pointers::findItemBySerial( target_serial );
	VALIDATEPI(pi);

	//steal a pickpocket, a steal training dummy
	if( pi->getId() == 0x1E2D || pi->getId() == 0x1E2C )
	{
		Skills::PickPocketTarget(ps);
        	return;
	}

	//no stealing for items on layers other than 0 (equipped!) , newbie items, and items not being in containers allowed !
	if ( pi->layer!=0 || pi->isNewbie() || pi->isInWorld() )
	{
       	thief->sysmsg(TRANSLATE("You cannot steal that."));
       	return;
	}

	P_CHAR victim = pi->getPackOwner();
	VALIDATEPC(victim);

	if (victim->npcaitype == NPCAI_PLAYERVENDOR)
	{
		thief->sysmsg(TRANSLATE("You cannot steal from player vendors."));
       	return;
	}

	if ( (thief->getSerial32() == victim->getSerial32()) || (thief->getSerial32()==victim->getOwnerSerial32()) )
	{
		thief->sysmsg(TRANSLATE("You catch yourself red handed."));
		return;
	}

	if (thief->distFrom( victim ) == 1)
	{

		int result;

		R32 we = pi->getWeightActual();
		int bonus= (int)( (1800 - we)/5 );
		if ( thief->checkSkill( STEALING,0,(1000-bonus)) )
		{
			// 0 stealing 2 stones, 10  3 stones, 99.9 12 stones, 100 17 stones !!!
			int cansteal = thief->skill[STEALING] > 999 ? 1700 : thief->skill[STEALING] + 200;

			if ( we > cansteal )
			{
        		thief->sysmsg(TRANSLATE("That is too heavy."));
        		return;
			}

			
			if (pi->amxevents[EVENT_IONSTOLEN]!=NULL)
			{
				g_bByPass = false;
				pi->amxevents[EVENT_IONSTOLEN]->Call(pi->getSerial32(), thief->getSerial32(), victim->getSerial32());
				if (g_bByPass==true)
					return;
			}

			if (victim->amxevents[EVENT_CHR_ONSTOLEN])
			{
				g_bByPass = false;
				victim->amxevents[EVENT_CHR_ONSTOLEN]->Call(victim->getSerial32(), thief->getSerial32());
				if (g_bByPass==true)
					return;
			}
			/*

			pi->runAmxEvent( EVENT_IONSTOLEN, pi->getSerial32(), s, victim->getSerial32() );
			if (g_bByPass==true)
				return;

			victim->runAmxEvent( EVENT_CHR_ONSTOLEN, victim->getSerial32(), s );
			if (g_bByPass==true)
				return;
			*/

			P_ITEM pack= thief->getBackpack();
			VALIDATEPI(pack);

			pi->setContSerial( pack->getSerial32() );

			thief->sysmsg(TRANSLATE("You successfully steal the item."));
			pi->Refresh();
			
			result=+200;
			//all_items(s); why all item?
		}
		else
		{
			thief->sysmsg( TRANSLATE("You failed to steal the item."));
			result=-200;
			//Only onhide when player is caught!
		}

		if ( rand()%1000 > ( thief->skill[STEALING] + result )  )
		{
			thief->unHide();
			thief->sysmsg(TRANSLATE("You have been caught!"));
			thief->IncreaseKarma(ServerScp::g_nStealKarmaLoss);
			thief->modifyFame(ServerScp::g_nStealFameLoss);

			if ( victim->IsInnocent() && thief->attackerserial != victim->getSerial32() && Guilds->Compare(thief,victim)==0)
				setCrimGrey(thief, ServerScp::g_nStealWillCriminal); //Blue and not attacker and not same guild


			std::string itmname ( "" );
			char temp[TEMP_STR_SIZE]; //xan -> this overrides the global temp var
			char temp2[TEMP_STR_SIZE]; //xan -> this overrides the global temp var
			if ( pi->getCurrentName() != "#" )
				itmname = pi->getCurrentName();
			else
			{
				pi->getName( temp );
				itmname = temp;
			}
			sprintf(temp,TRANSLATE("You notice %s trying to steal %s from you!"), thief->getCurrentNameC(), itmname.c_str());
			sprintf(temp2,TRANSLATE("You notice %s trying to steal %s from %s!"), thief->getCurrentNameC(), itmname.c_str(), victim->getCurrentNameC());

			if ( victim->npc )
				if( victim->HasHumanBody() )
					victim->talkAll(TRANSLATE( "Guards!! A thief is amoung us!"),0);
			else
				victim->sysmsg(temp);

			//send to all player temp2 = thief are stealing victim if are more intelligent and a bonus of luck :D
			NxwSocketWrapper sw;
			sw.fillOnline( thief, true );
			for( sw.rewind(); !sw.isEmpty(); sw++ ) {
				
				NXWCLIENT ps_i=sw.getClient();
				if(ps_i==NULL ) continue;

				P_CHAR pc_i=ps_i->currChar();
				if ( ISVALIDPC(pc_i) )
					if( (rand()%10+10==17) || ( (rand()%2==1) && (pc_i->in>=thief->in)))
						pc_i->sysmsg(temp2);
			}
		}
	}
	else 
	{
		thief->sysmsg(TRANSLATE("You are too far away to steal that item."));
	}

	AMXEXECSVTARGET( thief->getSerial32(),AMXT_SKITARGS,STEALING,AMX_AFTER);
}