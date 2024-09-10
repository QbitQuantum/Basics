void	CActor::Hit							(SHit* pHDS)
{
	pHDS->aim_bullet = false;

	SHit HDS = *pHDS;
	if( HDS.hit_type<ALife::eHitTypeBurn || HDS.hit_type >= ALife::eHitTypeMax )
	{
		string256	err;
		sprintf		(err, "Unknown/unregistered hit type [%d]", HDS.hit_type);
		R_ASSERT2	(0, err );
	
	}
#ifdef DEBUG
if(ph_dbg_draw_mask.test(phDbgCharacterControl))
{
	DBG_OpenCashedDraw();
	Fvector to;to.add(Position(),Fvector().mul(HDS.dir,HDS.phys_impulse()));
	DBG_DrawLine(Position(),to,D3DCOLOR_XRGB(124,124,0));
	DBG_ClosedCashedDraw(500);
}
#endif
	bool bPlaySound = true;
	if (!g_Alive()) bPlaySound = false;

	if (!IsGameTypeSingle() && !g_pGamePersistent->bDedicatedServer)
	{
		game_PlayerState* ps = Game().GetPlayerByGameID(ID());
		if (ps && ps->testFlag(GAME_PLAYER_FLAG_INVINCIBLE))
		{
			bPlaySound = false;
			if (Device.dwFrame != last_hit_frame &&
				HDS.bone() != BI_NONE)
			{		
				// вычислить позицию и направленность партикла
				Fmatrix pos; 

				CParticlesPlayer::MakeXFORM(this,HDS.bone(),HDS.dir,HDS.p_in_bone_space,pos);

				// установить particles
				CParticlesObject* ps = NULL;

				if (eacFirstEye == cam_active && this == Level().CurrentEntity())
					ps = CParticlesObject::Create(invincibility_fire_shield_1st,TRUE);
				else
					ps = CParticlesObject::Create(invincibility_fire_shield_3rd,TRUE);

				ps->UpdateParent(pos,Fvector().set(0.f,0.f,0.f));
				GamePersistent().ps_needtoplay.push_back(ps);
			};
		};
		 

		last_hit_frame = Device.dwFrame;
	};

	if(	!g_pGamePersistent->bDedicatedServer	&& 
		!sndHit[HDS.hit_type].empty()			&& 
		(ALife::eHitTypeTelepatic != HDS.hit_type))
	{
		ref_sound& S = sndHit[HDS.hit_type][Random.randI(sndHit[HDS.hit_type].size())];
		bool b_snd_hit_playing = sndHit[HDS.hit_type].end() != std::find_if(sndHit[HDS.hit_type].begin(), sndHit[HDS.hit_type].end(), playing_pred());

		if(ALife::eHitTypeExplosion == HDS.hit_type)
		{
			if (this == Level().CurrentControlEntity())
			{
				S.set_volume(10.0f);
				if(!m_sndShockEffector){
					m_sndShockEffector = xr_new<SndShockEffector>();
					m_sndShockEffector->Start(this, float(S._handle()->length_ms()), HDS.damage() );
				}
			}
			else
				bPlaySound = false;
		}
		if (bPlaySound && !b_snd_hit_playing) 
		{
			Fvector point		= Position();
			point.y				+= CameraHeight();
			S.play_at_pos		(this, point);
		};
	}

	
	//slow actor, only when he gets hit
	if(HDS.hit_type == ALife::eHitTypeWound || HDS.hit_type == ALife::eHitTypeStrike)
	{
		hit_slowmo				= HDS.damage();
		clamp					(hit_slowmo,0.0f,1.f);
	}
	else
		hit_slowmo = 0.f;
	//---------------------------------------------------------------
	if (Level().CurrentViewEntity() == this && !g_pGamePersistent->bDedicatedServer && HDS.hit_type == ALife::eHitTypeFireWound)
	{
		CObject* pLastHitter = Level().Objects.net_Find(m_iLastHitterID);
		CObject* pLastHittingWeapon = Level().Objects.net_Find(m_iLastHittingWeaponID);
		HitSector(pLastHitter, pLastHittingWeapon);
	};

	if ((mstate_real&mcSprint) && Level().CurrentControlEntity() == this && 
		HDS.hit_type != ALife::eHitTypeTelepatic &&
		HDS.hit_type != ALife::eHitTypeRadiation 
		)
	{
//		mstate_real	&=~mcSprint;
		mstate_wishful	&=~mcSprint;
	};
	if(!g_pGamePersistent->bDedicatedServer)
	{
		HitMark			(HDS.damage(), HDS.dir, HDS.who, HDS.bone(), HDS.p_in_bone_space, HDS.impulse, HDS.hit_type);
	}

	switch (GameID())
	{
	case GAME_SINGLE:		
		{
			float hit_power	= HitArtefactsOnBelt(HDS.damage(), HDS.hit_type);

			if (GodMode())//psActorFlags.test(AF_GODMODE))
			{
				HDS.power = 0.0f;
//				inherited::Hit(0.f,dir,who,element,position_in_bone_space,impulse, hit_type);
				inherited::Hit(&HDS);
				return;
			}
			else 
			{
				//inherited::Hit		(hit_power,dir,who,element,position_in_bone_space, impulse, hit_type);
				HDS.power = hit_power;
				inherited::Hit(&HDS);
			};
		}
		break;
	default:
		{
			m_bWasBackStabbed = false;
			if (HDS.hit_type == ALife::eHitTypeWound_2 && Check_for_BackStab_Bone(HDS.bone()))
			{
				// convert impulse into local coordinate system
				Fmatrix					mInvXForm;
				mInvXForm.invert		(XFORM());
				Fvector					vLocalDir;
				mInvXForm.transform_dir	(vLocalDir,HDS.dir);
				vLocalDir.invert		();

				Fvector a	= {0,0,1};
				float res = a.dotproduct(vLocalDir);
				if (res < -0.707)
				{
					game_PlayerState* ps = Game().GetPlayerByGameID(ID());
					if (!ps || !ps->testFlag(GAME_PLAYER_FLAG_INVINCIBLE))						
						m_bWasBackStabbed = true;
				}
			};
			
			float hit_power = 0;

			if (m_bWasBackStabbed) hit_power = 100000;
			else hit_power	= HitArtefactsOnBelt(HDS.damage(), HDS.hit_type);

			HDS.power = hit_power;
			inherited::Hit (&HDS);
			//inherited::Hit	(hit_power,dir,who,element,position_in_bone_space, impulse, hit_type, 0.0f);
		}		
		break;
	}
}