//=========================================================
// Spawn
//=========================================================
void CIchthyosaur :: Spawn()
{
	Precache( );

	SET_MODEL(ENT(pev), "models/icky.mdl");
	UTIL_SetSize( pev, Vector( -32, -32, -32 ), Vector( 32, 32, 32 ) );

	pev->solid			= SOLID_BBOX;
	pev->movetype		= MOVETYPE_FLY;
	m_bloodColor		= BLOOD_COLOR_GREEN;
	pev->health			= gSkillData.ichthyosaurHealth;
	pev->view_ofs		= Vector ( 0, 0, 16 );
	m_flFieldOfView		= VIEW_FIELD_WIDE;
	m_MonsterState		= MONSTERSTATE_NONE;
	SetBits(pev->flags, FL_SWIM);
	SetFlyingSpeed( ICHTHYOSAUR_SPEED );
	SetFlyingMomentum( 2.5 );	// Set momentum constant

	m_afCapability		= bits_CAP_RANGE_ATTACK1 | bits_CAP_SWIM;

	MonsterInit();

	SetTouch( BiteTouch );
	SetUse( CombatUse );

	m_idealDist = 384;
	m_flMinSpeed = 80;
	m_flMaxSpeed = 300;
	m_flMaxDist = 384;

	Vector Forward;
	UTIL_MakeVectorsPrivate(pev->angles, Forward, 0, 0);
	pev->velocity = m_flightSpeed * Forward.Normalize();
	m_SaveVelocity = pev->velocity;
}