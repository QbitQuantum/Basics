void AiAgentHealSupport::Update(uint32 p_time)
{
	_UpdateTimer(p_time);
	_UpdateMovement(p_time);

	if( !m_PetOwner )
		return; //oh noez, our master has abandoned us ! Where is te luv ?

	//we used this spell to create healbot. To avoid logout / login recreate we need to remove aura
	// lol, this will never work :(
	if( !m_Unit->isAlive() )
		m_PetOwner->RemoveAura( 36765 );

	if( m_Unit->GetMapMgr() != m_PetOwner->GetMapMgr() )
	{
		m_PetOwner->RemoveAura( 36765 );
		m_Unit->EventSummonPetExpire();
	}

	if( m_Unit->isCasting() )
		return; // we are already supporting someone ...get back later

	//we should be at same level at owner so we profit of fighting formulas same as owner
	if(	m_Unit->GetUInt32Value( UNIT_FIELD_LEVEL ) != m_PetOwner->GetUInt32Value( UNIT_FIELD_LEVEL ) )
	{
		m_Unit->SetUInt32Value( UNIT_FIELD_LEVEL, m_PetOwner->GetUInt32Value( UNIT_FIELD_LEVEL ) );
		DifficultyLevel = m_PetOwner->GetUInt32Value( UNIT_FIELD_LEVEL ) / 80.0f;
//printf("difficulty changed to %f \n",DifficultyLevel);
		//scale health and mana.when we level we max out our stats
		m_Unit->SetUInt32Value( UNIT_FIELD_MAXHEALTH , (uint32)(m_Unit->GetUInt32Value( UNIT_FIELD_BASE_HEALTH ) * ( 1 + DifficultyLevel ) * CREATURE_STATS_SCALE_WITH_DIFFICULTY) );
		m_Unit->SetUInt32Value( UNIT_FIELD_MAXPOWER1 , (uint32)(m_Unit->GetUInt32Value( UNIT_FIELD_BASE_MANA ) * ( 1 + DifficultyLevel ) * CREATURE_STATS_SCALE_WITH_DIFFICULTY) );
		m_Unit->SetUInt32Value( UNIT_FIELD_HEALTH , (uint32)(m_Unit->GetUInt32Value( UNIT_FIELD_HEALTH ) * ( 1 + DifficultyLevel ) * CREATURE_STATS_SCALE_WITH_DIFFICULTY) );
		m_Unit->SetUInt32Value( UNIT_FIELD_POWER1 , (uint32)(m_Unit->GetUInt32Value( UNIT_FIELD_POWER1 ) * ( 1 + DifficultyLevel ) * CREATURE_STATS_SCALE_WITH_DIFFICULTY) );
	}

	//if owner fights a long combat then we he desrvers to get lasy at the end ?
	if( m_PetOwner->CombatStatus.IsInCombat() )
		CombatDifficultyLevel += DIFFICULTY_UPDATE_SPEED;
	else CombatDifficultyLevel = 0;
	if( CombatDifficultyLevel > 1 )
		CombatDifficultyLevel = 1;

	uint32 Time_Now = getMSTime();

	std::list<healagentspell*>::iterator itr;
	SpellCastTargets targets( m_PetOwner->GetGUID() );
	healagentspell *m_castingSpell = NULL;
	Unit			*SpellTarget = m_PetOwner;

	//poor thing died. Res him. 
	//will never work
	if( !m_PetOwner->isAlive() && CheckCanCast( revive_spell.sp, SpellTarget ) )
	{
		m_castingSpell = &revive_spell;
//printf("master died, we are going to resurect him\n");
	}

	//if we are injusred we should try to survive it
	if ( m_castingSpell== NULL && m_Unit->GetUInt32Value( UNIT_FIELD_HEALTH ) < m_Unit->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
	{
//printf("we are injured, diff is %u \n",m_Unit->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) - m_Unit->GetUInt32Value( UNIT_FIELD_HEALTH ));
		if(	!Protect_self() ) //first we try to escape combat
		{
			m_castingSpell = PickSpellFromList( &m_healspells, m_Unit );
			SpellTarget = m_Unit;
		}
		else
		{
			m_castingSpell = &m_defend_self;
			SpellTarget = m_Unit;
		}
	}

	//select an augment spell if we have nothing better to do
	if( m_castingSpell== NULL && m_PetOwner->GetUInt32Value( UNIT_FIELD_HEALTH ) == m_PetOwner->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
	{
//printf("master is ok, we can try augment someone\n");
		m_castingSpell = PickSpellFromList( &m_AugmentSelf, m_Unit );
		//try augment owner ?
		if( !m_castingSpell )
		{
			m_castingSpell = PickSpellFromList( &m_AugmentTarget, m_PetOwner );
			SpellTarget = m_Unit;
		}
	}

	//master is injured, this should be most common case
	if( m_castingSpell==NULL && m_PetOwner->GetUInt32Value( UNIT_FIELD_HEALTH ) < m_PetOwner->GetUInt32Value( UNIT_FIELD_MAXHEALTH ) )
	{
//printf("master is injured, will try to heal him\n");
		m_castingSpell = PickSpellFromList( &m_healspells , m_PetOwner);
		SpellTarget = m_PetOwner;
	}

	if( m_castingSpell )
	{
//printf("we have a spell to cast\n");

		SpellCastTime *sd = dbcSpellCastTime.LookupEntry( m_castingSpell->sp->CastingTimeIndex );

		//do not stop for instant casts
		if(GetCastTime(sd) != 0)
		{
			StopMovement(0);
//printf("spell is not instant so we are going to stop movement \n");
		}

		float distance = m_Unit->GetDistanceSq( SpellTarget );
		if(	distance <= m_castingSpell->sp->base_range_or_radius_sqr || m_castingSpell->sp->base_range_or_radius_sqr == 0 )
		{

//printf("we are in range and going to cast spell \n");
			m_AIState = STATE_CASTING;
			
			Spell *nspell = SpellPool.PooledNew();
			nspell->Init(m_Unit, m_castingSpell->sp, false, NULL);

#ifdef SPELL_EFF_PCT_SCALE_WITH_DIFFICULTY
			if( m_castingSpell->max_scale )
			{
				nspell->forced_basepoints[ 0 ] = (uint32)( m_castingSpell->max_scale * ( DifficultyLevel + CombatDifficultyLevel) );
				if( nspell->forced_basepoints[ 0 ] > m_castingSpell->max_scale * 2)
					nspell->forced_basepoints[ 0 ] = m_castingSpell->max_scale * 2;
			}
#endif

			targets.m_unitTarget = SpellTarget->GetGUID();
			nspell->prepare( &targets );

			CastSpell( m_Unit, m_castingSpell->sp, targets );

			SetSpellDuration( m_castingSpell );

			//mana regen is to big, he can cast forever, double mana usage maybe regulates this
			m_Unit->ModSignedInt32Value( UNIT_FIELD_POWER1, -m_castingSpell->sp->manaCost );

		}
		else // Target out of Range -> Run to it
		{
//printf("we are going to move closer \n");
			m_moveRun = true;
			_CalcDestinationAndMove( SpellTarget, sqrt( m_castingSpell->sp->base_range_or_radius_sqr ) );
		}
	}

// check if pets regenrate mana, If not then we should implement that too
	//if owner is mounted then we mount too. Speed is not set though
	if( m_PetOwner->GetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID ) && m_Unit->GetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID ) == 0 )
	{
		if( Owner_side == OWNER_SIDE_ALIANCE )
			m_Unit->SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID, HELPER_MOUNT_A_DISPLAY );
		else
			m_Unit->SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID, OWNER_SIDE_HORDE );
		m_moveSprint =  true;
	}
	else if( m_PetOwner->GetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID ) == 0 && m_Unit->GetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID ) != 0 )
	{
		m_Unit->SetUInt32Value( UNIT_FIELD_MOUNTDISPLAYID, 0 );
		m_moveSprint = false;
	}

	//for fun : mimic master standstate. Note that this might give strange results
	if( m_PetOwner->GetStandState() != m_Unit->GetStandState() )
		m_Unit->SetStandState( m_PetOwner->GetStandState() );

	if( m_castingSpell == NULL )
	{
		if( First_noaction_stamp == 0 )
			First_noaction_stamp = Time_Now;

		float dist = m_Unit->CalcDistance( m_PetOwner );

//printf("we are far from owner, we should move closer , dist %f from %f \n",dist,(FollowDistance*FollowDistance));
		if ( dist > FollowDistance ) //if out of range
		{
			m_moveRun = true;

			if(dist > 20.0f)
				m_moveSprint = true;

			float delta_x = UnitToFollow->GetPositionX();
			float delta_y = UnitToFollow->GetPositionY();
			float d = 3;

			MoveTo(delta_x+(d*(cosf(m_fallowAngle+m_PetOwner->GetOrientation()))),
				delta_y+(d*(sinf(m_fallowAngle+m_PetOwner->GetOrientation()))),
				m_PetOwner->GetPositionZ(),m_PetOwner->GetOrientation());				
		}
	}
	else if(m_castingSpell != NULL )
		First_noaction_stamp = 0;

//if( First_noaction_stamp )printf("ms to say something %u and ms for say cooldown %u\n",First_noaction_stamp + BOREDOM_TIMER_TO_START_TRIGGERING - Time_Now,Boredom_cooldown - Time_Now );
	if( 
		First_noaction_stamp
		&& First_noaction_stamp + BOREDOM_TIMER_TO_START_TRIGGERING < Time_Now 
		&& Boredom_cooldown < Time_Now
		)
	{
		//some chance to say something
		if( Rand( 50 ) )
			m_Unit->SendChatMessage(CHAT_MSG_MONSTER_SAY, LANG_UNIVERSAL, bored_texts[ RandomUInt( BOREDOM_TEXTCOUNT ) ]);
		else
			m_Unit->SetUInt32Value ( UNIT_NPC_EMOTESTATE, bored_emotes[ RandomUInt( BOREDOM_EMOTECOUNT ) ] );
		Boredom_cooldown = Time_Now + BOREDOM_TRIGGER_INTERVAL;
	}
}