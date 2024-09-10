//------------------------------------------------------------------------------
// Purpose :
// Input   :
// Output  :
//------------------------------------------------------------------------------
void CNPC_CombineDropship::Spawn( void )
{
	Precache( );

	SetModel( "models/combine_dropship.mdl" );
	BaseClass::Spawn();

	ExtractBbox( SelectHeaviestSequence( ACT_DROPSHIP_DEPLOY_IDLE ), m_cullBoxMins, m_cullBoxMaxs ); 
	BaseClass::Spawn();

	InitPathingData( DROPSHIP_LEAD_DISTANCE, DROPSHIP_MIN_CHASE_DIST_DIFF, DROPSHIP_AVOID_DIST );

	// create the correct bin for the ship to carry
	switch ( m_iCrateType )
	{
	case CRATE_ROLLER_HOPPER:
		break;
	case CRATE_SOLDIER:
		m_hContainer = CreateEntityByName( "prop_dynamic" );
		if ( m_hContainer )
		{
			m_hContainer->SetModel( "models/props_junk/trashdumpster02.mdl" );
			m_hContainer->SetLocalOrigin( GetAbsOrigin() );
			m_hContainer->SetLocalAngles( GetLocalAngles() );
			m_hContainer->SetAbsAngles( GetAbsAngles() );
			m_hContainer->SetParent(this, 0);
			m_hContainer->SetOwnerEntity(this);
			m_hContainer->SetSolid( SOLID_VPHYSICS );
			m_hContainer->Spawn();
		}
		break;

	case CRATE_NONE:
	default:
		break;
	}

	m_iHealth = 100;
	m_flFieldOfView = 0.5; // 60 degrees
	m_iContainerMoveType = MOVETYPE_NONE;

	//InitBoneControllers();
	InitCustomSchedules();

	if ( m_hContainer )
	{
		SetIdealActivity( (Activity)ACT_DROPSHIP_FLY_IDLE_CARGO );
	}
	else
	{
		SetIdealActivity( (Activity)ACT_DROPSHIP_FLY_IDLE_EXAGG );
	}

	m_flMaxSpeed = DROPSHIP_MAX_SPEED;
	m_flMaxSpeedFiring = BASECHOPPER_MAX_FIRING_SPEED;
	m_hPickupTarget = NULL;

	//!!!HACKHACK
	// This tricks the AI code that constantly complains that the vehicle has no schedule.
	SetSchedule( SCHED_IDLE_STAND );

	m_iLandState = LANDING_NO;
}