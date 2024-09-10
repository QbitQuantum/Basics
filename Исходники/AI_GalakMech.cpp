void	Pilot_Steer_Vehicle()
{
	if (!NPC->enemy || !NPC->enemy->client)
	{
		return;
	}






// SETUP
//=======
	// Setup Actor Data
	//------------------
	CVec3		ActorPos(NPC->currentOrigin);
	CVec3		ActorAngles(NPC->currentAngles);
				ActorAngles[2]	= 0;
	Vehicle_t*	ActorVeh		= NPCInfo->greetEnt->m_pVehicle;
	bool		ActorInTurbo	= (ActorVeh->m_iTurboTime>level.time);
	float		ActorSpeed		= (ActorVeh)?(VectorLength(ActorVeh->m_pParentEntity->client->ps.velocity)):(NPC->client->ps.speed);


	// If my vehicle is spinning out of control, just hold on, we're going to die!!!!!
	//---------------------------------------------------------------------------------
	if (ActorVeh && (ActorVeh->m_ulFlags & VEH_OUTOFCONTROL))
	{
		if (NPC->client->ps.weapon!=WP_NONE)
		{
			NPC_ChangeWeapon(WP_NONE);
		}
		ucmd.buttons	&=~BUTTON_ATTACK;
		ucmd.buttons	&=~BUTTON_ALT_ATTACK;
		return;
	}

	CVec3		ActorDirection;
				AngleVectors(ActorAngles.v, ActorDirection.v, 0, 0);

	CVec3		ActorFuturePos(ActorPos);
				ActorFuturePos.ScaleAdd(ActorDirection, FUTURE_PRED_DIST);

	bool		ActorDoTurbo	= false;
	bool		ActorAccelerate	= false;
	bool		ActorAimAtTarget= true;
	float		ActorYawOffset	= 0.0f;


	// Setup Enemy Data
	//------------------
	CVec3		EnemyPos(NPC->enemy->currentOrigin);
	CVec3		EnemyAngles(NPC->enemy->currentAngles);
				EnemyAngles[2]	= 0;
	Vehicle_t*	EnemyVeh		= (NPC->enemy->s.m_iVehicleNum)?(g_entities[NPC->enemy->s.m_iVehicleNum].m_pVehicle):(0);
	bool		EnemyInTurbo	= (EnemyVeh && EnemyVeh->m_iTurboTime>level.time);
	float		EnemySpeed		= (EnemyVeh)?(EnemyVeh->m_pParentEntity->client->ps.speed):(NPC->enemy->resultspeed);
	bool		EnemySlideBreak	= (EnemyVeh && (EnemyVeh->m_ulFlags&VEH_SLIDEBREAKING || EnemyVeh->m_ulFlags&VEH_STRAFERAM));
	bool		EnemyDead		= (NPC->enemy->health<=0);

	bool		ActorFlank		= (NPCInfo->lastAvoidSteerSideDebouncer>level.time && EnemyVeh && EnemySpeed>10.0f);

	CVec3		EnemyDirection;
	CVec3		EnemyRight;
				AngleVectors(EnemyAngles.v, EnemyDirection.v, EnemyRight.v, 0);

	CVec3		EnemyFuturePos(EnemyPos);
				EnemyFuturePos.ScaleAdd(EnemyDirection, FUTURE_PRED_DIST);

	ESide		EnemySide		= ActorPos.LRTest(EnemyPos, EnemyFuturePos);
	CVec3		EnemyFlankPos(EnemyFuturePos);
				EnemyFlankPos.ScaleAdd(EnemyRight, (EnemySide==Side_Right)?(FUTURE_SIDE_DIST):(-FUTURE_SIDE_DIST));

	// Debug Draw Enemy Data
	//-----------------------
	if (false)
	{
		CG_DrawEdge(EnemyPos.v,			EnemyFuturePos.v, EDGE_IMPACT_SAFE);
		CG_DrawEdge(EnemyFuturePos.v,	EnemyFlankPos.v, EDGE_IMPACT_SAFE);
	}


	// Setup Move And Aim Directions
	//-------------------------------
	CVec3		MoveDirection((ActorFlank)?(EnemyFlankPos):(EnemyFuturePos));
				MoveDirection	-= ActorPos;
	float		MoveDistance	= MoveDirection.SafeNorm();
	float		MoveAccuracy	= MoveDirection.Dot(ActorDirection);

	CVec3		AimDirection(EnemyPos);
				AimDirection	-= ActorPos;
	float		AimDistance		= AimDirection.SafeNorm();
	float		AimAccuracy		= AimDirection.Dot(ActorDirection);



	if (!ActorFlank && TIMER_Done(NPC, "FlankAttackCheck"))
	{
		TIMER_Set(NPC, "FlankAttackCheck", Q_irand(1000, 3000));
		if (MoveDistance<4000 && Q_irand(0, 1)==0)
		{
			NPCInfo->lastAvoidSteerSideDebouncer	= level.time + Q_irand(8000, 14000);
		}
	}



	// Fly By Sounds
	//---------------
	if ((ActorVeh->m_pVehicleInfo->soundFlyBy || ActorVeh->m_pVehicleInfo->soundFlyBy2) &&
		EnemyVeh &&
		MoveDistance<800 &&
		ActorSpeed>500.0f &&
		TIMER_Done(NPC, "FlybySoundDebouncer")
		)
	{
		if (EnemySpeed<100.0f || (ActorDirection.Dot(EnemyDirection)*(MoveDistance/800.0f))<-0.5f)
		{
			TIMER_Set(NPC, "FlybySoundDebouncer", 2000);
			int soundFlyBy = ActorVeh->m_pVehicleInfo->soundFlyBy;
			if (ActorVeh->m_pVehicleInfo->soundFlyBy2 && (!soundFlyBy || !Q_irand(0,1)))
			{
				soundFlyBy = ActorVeh->m_pVehicleInfo->soundFlyBy2;
			}
			G_Sound(ActorVeh->m_pParentEntity, soundFlyBy);		
		}
	}



// FLY PAST BEHAVIOR
//===================
 	if (EnemySlideBreak || !TIMER_Done(NPC, "MinHoldDirectionTime"))
	{
		if (TIMER_Done(NPC, "MinHoldDirectionTime"))
		{ 
			TIMER_Set(NPC, "MinHoldDirectionTime", 500);	// Hold For At Least 500 ms
		}
		ActorAccelerate		= true;							// Go
		ActorAimAtTarget	= false;						// Don't Alter Our Aim Direction
		ucmd.buttons		&=~BUTTON_VEH_SPEED;			// Let Normal Vehicle Controls Go
	}


// FLANKING BEHAVIOR
//===================
	else if (ActorFlank)
	{
  		ActorAccelerate	= true;
		ActorDoTurbo	= (MoveDistance>2500 || EnemyInTurbo);
		ucmd.buttons	|= BUTTON_VEH_SPEED;			// Tells PMove to use the ps.speed we calculate here, not the one from g_vehicles.c


		// For Flanking, We Calculate The Speed By Hand, Rather Than Using Pure Accelerate / No Accelerate Functionality
		//---------------------------------------------------------------------------------------------------------------
		NPC->client->ps.speed = ActorVeh->m_pVehicleInfo->speedMax * ((ActorInTurbo)?(1.35f):(1.15f));


		// If In Slowing Distance, Scale Down The Speed As We Approach Our Move Target
		//-----------------------------------------------------------------------------
		if (MoveDistance<ATTACK_FLANK_SLOWING)
		{
			NPC->client->ps.speed *= (MoveDistance/ATTACK_FLANK_SLOWING);
			NPC->client->ps.speed += EnemySpeed;

			// Match Enemy Speed
			//-------------------
			if (NPC->client->ps.speed<5.0f && EnemySpeed<5.0f)
			{
				NPC->client->ps.speed = EnemySpeed;
			}

			// Extra Slow Down When Out In Front
			//-----------------------------------
 			if  (MoveAccuracy<0.0f)
			{
				NPC->client->ps.speed *= (MoveAccuracy + 1.0f);
			}

	
			MoveDirection	*=        (MoveDistance/ATTACK_FLANK_SLOWING);
			EnemyDirection	*= 1.0f - (MoveDistance/ATTACK_FLANK_SLOWING);
			MoveDirection	+= EnemyDirection;

			if (TIMER_Done(NPC, "RamCheck"))
			{
				TIMER_Set(NPC, "RamCheck", Q_irand(1000, 3000));
				if (MoveDistance<RAM_DIST && Q_irand(0, 2)==0)
				{
					VEH_StartStrafeRam(ActorVeh, (EnemySide==Side_Left));
				}
			}
		}
	}


// NORMAL CHASE BEHAVIOR
//=======================
	else
	{
		if (!EnemyVeh && AimAccuracy>0.99f && MoveDistance<500 && !EnemyDead)
		{
			ActorAccelerate = true;
			ActorDoTurbo	= false;
		}
		else
		{
			ActorAccelerate = ((MoveDistance>500 && EnemySpeed>20.0f) || MoveDistance>1000);
			ActorDoTurbo	= (MoveDistance>3000 && EnemySpeed>20.0f);
		}
		ucmd.buttons	&=~BUTTON_VEH_SPEED;
	}




// APPLY RESULTS
//=======================
	// Decide Turbo
	//--------------
	if (ActorDoTurbo || ActorInTurbo)
	{
		ucmd.buttons |= BUTTON_ALT_ATTACK;
	}
	else
	{
		ucmd.buttons &=~BUTTON_ALT_ATTACK;
	}

	// Decide Acceleration
	//---------------------
	ucmd.forwardmove = (ActorAccelerate)?(127):(0);



	// Decide To Shoot
	//-----------------
	ucmd.buttons	&=~BUTTON_ATTACK;
	ucmd.rightmove	= 0;
 	if (AimDistance<2000 && !EnemyDead)
	{
		// If Doing A Ram Attack
		//-----------------------
		if (ActorYawOffset!=0)
		{
			if (NPC->client->ps.weapon!=WP_NONE)
			{
				NPC_ChangeWeapon(WP_NONE);
			}
			ucmd.buttons	&=~BUTTON_ATTACK;
		}
 		else if (AimAccuracy>ATTACK_FWD)
		{
			if (NPC->client->ps.weapon!=WP_NONE)
			{
				NPC_ChangeWeapon(WP_NONE);
			}
			ucmd.buttons	|= BUTTON_ATTACK;
		}
		else if (AimAccuracy<AIM_SIDE && AimAccuracy>-AIM_SIDE)
		{
			if (NPC->client->ps.weapon!=WP_BLASTER)
			{
				NPC_ChangeWeapon(WP_BLASTER);
			}

			if (AimAccuracy<ATTACK_SIDE && AimAccuracy>-ATTACK_SIDE)
			{
				//if (!TIMER_Done(NPC, "RiderAltAttack"))
				//{
				//	ucmd.buttons |= BUTTON_ALT_ATTACK;
				//}
				//else
				//{
                    ucmd.buttons |= BUTTON_ATTACK;

			/*		if (TIMER_Done(NPC, "RiderAltAttackCheck"))
					{
						TIMER_Set(NPC, "RiderAltAttackCheck", Q_irand(1000, 3000));
						if (Q_irand(0, 2)==0)
						{
							TIMER_Set(NPC, "RiderAltAttack", 300);
						}
					}*/
				//}
				WeaponThink(true);
			}
			ucmd.rightmove = (EnemySide==Side_Left)?( 127):(-127);
		}
		else
		{
			if (NPC->client->ps.weapon!=WP_NONE)
			{
				NPC_ChangeWeapon(WP_NONE);
			}
		}
	}
	else
	{
		if (NPC->client->ps.weapon!=WP_NONE)
		{
			NPC_ChangeWeapon(WP_NONE);
		}
	}


	// Aim At Target
	//---------------
	if (ActorAimAtTarget)
	{
		MoveDirection.VecToAng();
		NPCInfo->desiredPitch	= AngleNormalize360(MoveDirection[PITCH]);
		NPCInfo->desiredYaw		= AngleNormalize360(MoveDirection[YAW] + ActorYawOffset);
	}
	NPC_UpdateAngles(qtrue, qtrue);
}