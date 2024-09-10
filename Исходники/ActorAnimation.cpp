void CActor::g_SetAnimation( u32 mstate_rl )
{


	if (!g_Alive()) {
		if (m_current_legs||m_current_torso){
			SActorState*				ST = 0;
			if (mstate_rl&mcCrouch)		ST = &m_anims->m_crouch;
			else						ST = &m_anims->m_normal;
			mstate_real					= 0;
			m_current_legs.invalidate	();
			m_current_torso.invalidate	();

			smart_cast<CKinematicsAnimated*>(Visual())->PlayCycle(m_anims->m_dead_stop);
		}

		return;
	}
	STorsoWpn::eMovingState	moving_idx 		= STorsoWpn::eIdle;
	SActorState*					ST 		= 0;
	SAnimState*						AS 		= 0;
	
	if		(mstate_rl&mcCrouch)	ST 		= &m_anims->m_crouch;
	else if	(mstate_rl&mcClimb)		ST 		= &m_anims->m_climb;
	else							ST 		= &m_anims->m_normal;

	bool bAccelerated = isActorAccelerated(mstate_rl, IsZoomAimingMode());
	if ( bAccelerated ){
		AS							= &ST->m_run;
	}else{
		AS							= &ST->m_walk;
	}
	if(mstate_rl&mcAnyMove){
		if( bAccelerated )
			moving_idx				= STorsoWpn::eRun;
		else
			moving_idx				= STorsoWpn::eWalk;
	}
	// анимации
	MotionID 						M_legs;
	MotionID 						M_torso;
	MotionID 						M_head;

	//если мы просто стоим на месте
	bool is_standing = false;

	// Legs
	if		(mstate_rl&mcLanding)	M_legs	= ST->landing[0];
	else if (mstate_rl&mcLanding2)	M_legs	= ST->landing[1];
	else if ((mstate_rl&mcTurn)&&
			!(mstate_rl&mcClimb))	M_legs	= ST->legs_turn;
	else if (mstate_rl&mcFall)		M_legs	= ST->jump_idle;
	else if (mstate_rl&mcJump)		M_legs	= ST->jump_begin;
	else if (mstate_rl&mcFwd)		M_legs	= AS->legs_fwd;
	else if (mstate_rl&mcBack)		M_legs	= AS->legs_back;
	else if (mstate_rl&mcLStrafe)	M_legs	= AS->legs_ls;
	else if (mstate_rl&mcRStrafe)	M_legs	= AS->legs_rs;
	else is_standing = true;

	if(mstate_rl&mcSprint){
		g_SetSprintAnimation			(mstate_rl,M_head,M_torso,M_legs);
		moving_idx						= STorsoWpn::eSprint;
	}
	//---------------------------------------------------------------
	if (this == Level().CurrentViewEntity())
	{	
		if ((mstate_rl&mcSprint) != (mstate_old&mcSprint))
		{
			CHudItem* pHudItem = smart_cast<CHudItem*>(inventory().ActiveItem());	
			if (pHudItem) pHudItem->onMovementChanged(mcSprint);
		};
	};
	//-----------------------------------------------------------------------
	// Torso
	if(mstate_rl&mcClimb)
	{
		if		(mstate_rl&mcFwd)		M_torso	= AS->legs_fwd;
		else if (mstate_rl&mcBack)		M_torso	= AS->legs_back;
		else if (mstate_rl&mcLStrafe)	M_torso	= AS->legs_ls;
		else if (mstate_rl&mcRStrafe)	M_torso	= AS->legs_rs;
	}
	
	if(!M_torso)
	{
		CInventoryItem* _i = inventory().ActiveItem();
		CHudItem		*H = smart_cast<CHudItem*>(_i);
		CWeapon			*W = smart_cast<CWeapon*>(_i);
		CMissile		*M = smart_cast<CMissile*>(_i);
		CArtefact		*A = smart_cast<CArtefact*>(_i);
					
		if (H) {
			VERIFY(H->animation_slot() <= _total_anim_slots_);
			STorsoWpn* TW			= &ST->m_torso[H->animation_slot() - 1];
			if (!b_DropActivated&&!fis_zero(f_DropPower)){
				M_torso					= TW->drop;
				if (!M_torso)	
				{
					Msg("! drop animation for %s", *(H->object().cName()));
					M_torso = ST->m_torso_idle;
				};
				m_bAnimTorsoPlayed		= TRUE;
			}else{
				if (!m_bAnimTorsoPlayed) {
					if (W) {
						bool K	=inventory().GetActiveSlot() == KNIFE_SLOT;
						bool R3 = W->IsTriStateReload();
						
						if(K)
						{
							switch (W->GetState()){
							case CWeapon::eIdle:		M_torso	= TW->moving[moving_idx];		break;
							
							case CWeapon::eFire:	
								if(is_standing)
														M_torso = M_legs = M_head = TW->all_attack_0;
								else
														M_torso	= TW->attack_zoom;
								break;

							case CWeapon::eFire2:
								if(is_standing)
														M_torso = M_legs = M_head = TW->all_attack_1;
								else
														M_torso	= TW->fire_idle;
								break;

							case CWeapon::eJammed:
							case CWeapon::eReload:		M_torso	= TW->reload;					break;
							case CWeapon::eShowing:		M_torso	= TW->draw;						break;
							case CWeapon::eHiding:		M_torso	= TW->holster;					break;
							default				 :  	M_torso	= TW->moving[moving_idx];		break;
							}
						}
						else
						{
							switch (W->GetState()){
							case CWeapon::eIdle:		M_torso	= W->IsZoomed()?TW->zoom:TW->moving[moving_idx];	break;
							case CWeapon::eFire:		M_torso	= W->IsZoomed()?TW->attack_zoom:TW->attack;				break;
							case CWeapon::eFire2:		M_torso	= W->IsZoomed()?TW->attack_zoom:TW->attack;				break;
							case CWeapon::eJammed:
							case CWeapon::eReload:	
								if(!R3)
									M_torso	= TW->reload;
								else{
									CWeapon::EWeaponSubStates sub_st = W->GetReloadState();
									switch (sub_st){
										case CWeapon::eSubstateReloadBegin:			M_torso	= TW->reload;	break;
										case CWeapon::eSubstateReloadInProcess:		M_torso	= TW->reload_1; break;
										case CWeapon::eSubstateReloadEnd:			M_torso	= TW->reload_2; break;
										default:									M_torso	= TW->reload;	break;
									}
								}break;

							case CWeapon::eShowing:	M_torso	= TW->draw;					break;
							case CWeapon::eHiding:	M_torso	= TW->holster;				break;
							default				 :  M_torso	= TW->moving[moving_idx];	break;
							}
						}
					}
					else if (M) {
						if(is_standing)
						{
							switch (M->GetState()){
							case MS_SHOWING	 :		M_torso	= TW->draw;			break;
							case MS_HIDING	 :		M_torso	= TW->holster;		break;
							case MS_IDLE_SPRINT:   ;
							case MS_IDLE	 :		M_torso	= TW->moving[moving_idx];		break;							
							case MS_EMPTY	 :		M_torso	= TW->zoom;		break;
							case MS_THREATEN :		M_torso = M_legs = M_head = TW->all_attack_0;	break;
							case MS_READY	 :		M_torso = M_legs = M_head = TW->all_attack_1;	break;
							case MS_THROW	 :		M_torso = M_legs = M_head = TW->all_attack_2;	break;
							case MS_END		 :		M_torso = M_legs = M_head = TW->all_attack_2;	break;
							default			 :		M_torso	= TW->draw;			break; 
							}
						}
						else
						{
							switch (M->GetState()){
							case MS_SHOWING	 :		M_torso	= TW->draw;						break;
							case MS_HIDING	 :		M_torso	= TW->holster;					break;
							case MS_IDLE_SPRINT:   ;
							case MS_IDLE	 :		M_torso	= TW->moving[moving_idx];		break;
							case MS_EMPTY	 :		M_torso	= TW->moving[moving_idx];		break;
							case MS_THREATEN :		M_torso	= TW->attack_zoom;				break;
							case MS_READY	 :		M_torso	= TW->fire_idle;				break;
							case MS_THROW	 :		M_torso	= TW->fire_end;					break;
							case MS_END		 :		M_torso	= TW->fire_end;					break;
							default			 :		M_torso	= TW->draw;						break; 
							}
						}
					}
					else if (A){
							switch(A->GetState()){
								case CArtefact::eIdle		: M_torso	= TW->moving[moving_idx];	break; 
								case CArtefact::eShowing	: M_torso	= TW->draw;					break; 
								case CArtefact::eHiding		: M_torso	= TW->holster;				break; 
								case CArtefact::eActivating : M_torso	= TW->zoom;					break; 
							default							: M_torso	= TW->moving[moving_idx];
							}
					
					}
				}
			}
		}
	}

	if (!M_legs)
	{
		if((mstate_rl&mcCrouch)&&!isActorAccelerated(mstate_rl, IsZoomAimingMode()))//!(mstate_rl&mcAccel))
		{
			M_legs=smart_cast<CKinematicsAnimated*>(Visual())->ID_Cycle("cr_idle_1");
		}
		else 
			M_legs	= ST->legs_idle;
	}
	if (!M_head)					M_head	= ST->m_head_idle;
	if (!M_torso){				
		if (m_bAnimTorsoPlayed)		M_torso	= m_current_torso;
		else						M_torso = ST->m_torso_idle;
	}
	
	// есть анимация для всего - запустим / иначе запустим анимацию по частям
	if (m_current_torso!=M_torso){
		if (m_bAnimTorsoPlayed)		m_current_torso_blend = smart_cast<CKinematicsAnimated*>	(Visual())->PlayCycle(M_torso,TRUE,AnimTorsoPlayCallBack,this);
		else						/**/m_current_torso_blend = /**/smart_cast<CKinematicsAnimated*>	(Visual())->PlayCycle(M_torso);

		m_current_torso=M_torso;
	}
	if(m_current_head!=M_head)
	{
		if(M_head)smart_cast<CKinematicsAnimated*>(Visual())->PlayCycle(M_head);
		m_current_head=M_head;
	}
	if (m_current_legs!=M_legs){
		float pos					= 0.f;
		VERIFY						(!m_current_legs_blend || !fis_zero(m_current_legs_blend->timeTotal));
		if ((mstate_real&mcAnyMove)&&(mstate_old&mcAnyMove)&&m_current_legs_blend)
			pos						= fmod(m_current_legs_blend->timeCurrent,m_current_legs_blend->timeTotal)/m_current_legs_blend->timeTotal;
		m_current_legs_blend		= smart_cast<CKinematicsAnimated*>(Visual())->PlayCycle(M_legs,TRUE,legs_play_callback,this);
		if ((!(mstate_old&mcAnyMove))&&(mstate_real&mcAnyMove))
			pos						= 0.5f*Random.randI(2);
		if (m_current_legs_blend)
			m_current_legs_blend->timeCurrent = m_current_legs_blend->timeTotal*pos;
		m_current_legs				= M_legs;

		CStepManager::on_animation_start(M_legs, m_current_legs_blend);
	}



#ifdef _DEBUG
	if(bDebug){
		HUD().Font().pFontStat->OutSetI	(0,0);
		HUD().Font().pFontStat->OutNext("[%s]",mov_state[moving_idx]);
	}
#endif

#ifdef _DEBUG
	if ((Level().CurrentControlEntity() == this) && g_ShowAnimationInfo) {
		string128 buf;
		strcpy(buf,"");
		if (isActorAccelerated(mstate_rl, IsZoomAimingMode()))		strcat(buf,"Accel ");
		if (mstate_rl&mcCrouch)		strcat(buf,"Crouch ");
		if (mstate_rl&mcFwd)		strcat(buf,"Fwd ");
		if (mstate_rl&mcBack)		strcat(buf,"Back ");
		if (mstate_rl&mcLStrafe)	strcat(buf,"LStrafe ");
		if (mstate_rl&mcRStrafe)	strcat(buf,"RStrafe ");
		if (mstate_rl&mcJump)		strcat(buf,"Jump ");
		if (mstate_rl&mcFall)		strcat(buf,"Fall ");
		if (mstate_rl&mcTurn)		strcat(buf,"Turn ");
		if (mstate_rl&mcLanding)	strcat(buf,"Landing ");
		if (mstate_rl&mcLLookout)	strcat(buf,"LLookout ");
		if (mstate_rl&mcRLookout)	strcat(buf,"RLookout ");
		if (m_bJumpKeyPressed)		strcat(buf,"+Jumping ");
		HUD().Font().pFontStat->OutNext	("MSTATE:     [%s]",buf);
/*
		switch (m_PhysicMovementControl->Environment())
		{
		case CPHMovementControl::peOnGround:	strcpy(buf,"ground");			break;
		case CPHMovementControl::peInAir:		strcpy(buf,"air");				break;
		case CPHMovementControl::peAtWall:		strcpy(buf,"wall");				break;
		}
		HUD().Font().pFontStat->OutNext	(buf);
		HUD().Font().pFontStat->OutNext	("Accel     [%3.2f, %3.2f, %3.2f]",VPUSH(NET_SavedAccel));
		HUD().Font().pFontStat->OutNext	("V         [%3.2f, %3.2f, %3.2f]",VPUSH(m_PhysicMovementControl->GetVelocity()));
		HUD().Font().pFontStat->OutNext	("vertex ID   %d",ai_location().level_vertex_id());
		
		Game().m_WeaponUsageStatistic->Draw();
		*/
	};
#endif

	if (!m_current_torso_blend)
		return;

	CKinematicsAnimated		*skeleton_animated = PKinematicsAnimated(Visual());

	CMotionDef				*motion0 = skeleton_animated->LL_GetMotionDef(m_current_torso);
	VERIFY					(motion0);
	if (!(motion0->flags & esmSyncPart))
		return;

	if (!m_current_legs_blend)
		return;

	CMotionDef				*motion1 = skeleton_animated->LL_GetMotionDef(m_current_legs);
	VERIFY					(motion1);
	if (!(motion1->flags & esmSyncPart))
		return;

	m_current_torso_blend->timeCurrent	= m_current_legs_blend->timeCurrent/m_current_legs_blend->timeTotal*m_current_torso_blend->timeTotal;
}