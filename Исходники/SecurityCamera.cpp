/*
================
idSecurityCamera::Spawn
================
*/
void idSecurityCamera::Spawn( void ) {
	idStr	str;

	sweepAngle	= spawnArgs.GetFloat( "sweepAngle", "90" );
	health		= spawnArgs.GetInt( "health", "100" );
	scanFov		= spawnArgs.GetFloat( "scanFov", "90" );
	scanDist	= spawnArgs.GetFloat( "scanDist", "200" );
	flipAxis	= spawnArgs.GetBool( "flipAxis" );

	modelAxis	= spawnArgs.GetInt( "modelAxis" );
	if ( modelAxis < 0 || modelAxis > 2 ) {
		modelAxis = 0;
	}

	spawnArgs.GetVector( "viewOffset", "0 0 0", viewOffset );

	if ( spawnArgs.GetBool( "spotLight" ) ) {
		PostEventMS( &EV_SecurityCam_AddLight, 0 );
	}

	negativeSweep = ( sweepAngle < 0 ) ? true : false;
	sweepAngle = fabs( sweepAngle );

	scanFovCos = cos( scanFov * idMath::PI / 360.0f );

	angle = GetPhysics()->GetAxis().ToAngles().yaw;
	StartSweep();
	SetAlertMode( SCANNING );
	BecomeActive( TH_THINK );

	if ( health ) {
		fl.takedamage = true;
	}

	pvsArea = gameLocal.pvs.GetPVSArea( GetPhysics()->GetOrigin() );
	// if no target specified use ourself
	str = spawnArgs.GetString( "cameraTarget" );
	if ( str.Length() == 0 ) {
		spawnArgs.Set( "cameraTarget", spawnArgs.GetString( "name" ) );
	}

	// check if a clip model is set
	spawnArgs.GetString( "clipmodel", "", str );
	if ( !str[0] ) {
		str = spawnArgs.GetString( "model" );		// use the visual model
	}

	if ( !collisionModelManager->TrmFromModel( str, trm ) ) {
		gameLocal.Error( "idSecurityCamera '%s': cannot load collision model %s", name.c_str(), str.c_str() );
		return;
	}

	GetPhysics()->SetContents( CONTENTS_SOLID );
	// SR CONTENTS_RESPONSE FIX
	if( m_StimResponseColl->HasResponse() )
		physicsObj.SetContents( physicsObj.GetContents() | CONTENTS_RESPONSE );

	GetPhysics()->SetClipMask( MASK_SOLID | CONTENTS_BODY | CONTENTS_CORPSE | CONTENTS_MOVEABLECLIP );
	// setup the physics
	UpdateChangeableSpawnArgs( NULL );
}