void clRailPositioner::Update( float dt )
{
	float S = GetSpeed( dt );

	// move to properties
	float PitchRate = 90.0f * dt;
	float PanRate = 90.0f * dt;

	PitchRate *= Env->Console->IsKeyPressed( LK_SHIFT ) ? 3.0f : 1.0f;
	PanRate *= Env->Console->IsKeyPressed( LK_SHIFT ) ? 3.0f : 1.0f;

	if ( Env->Console->IsKeyPressed( LK_LEFT  ) ) { FPitch -= PitchRate; }

	if ( Env->Console->IsKeyPressed( LK_RIGHT ) ) { FPitch += PitchRate; }

	if ( Env->Console->IsKeyPressed( LK_E ) )     { FPan -= PanRate; }

	if ( Env->Console->IsKeyPressed( LK_C ) )     { FPan += PanRate; }

	FPitch = Math::ClipAngleTo0_360( FPitch );
	FPan   = Math::ClipAngleTo0_360( FPan );

	LMatrix4 PitchMtx;
	PitchMtx.IdentityMatrix();
	PitchMtx.RotateMatrixAxis( Linderdaum::Math::DegToRad( -FPitch ), FUpVector );

	LVector3 ViewDir = -( PitchMtx * FDirVector );
	LVector3 SideDir = -( FUpVector.Cross( ViewDir ) );

	if ( Env->Console->IsKeyPressed( LK_Q ) || Env->Console->IsKeyPressed( LK_1 ) ) { FPosition += S * FUpVector; }

	if ( Env->Console->IsKeyPressed( LK_Z ) || Env->Console->IsKeyPressed( LK_2 ) ) { FPosition -= S * FUpVector; }

	if ( Env->Console->IsKeyPressed( LK_W ) || Env->Console->IsKeyPressed( LK_UP   ) ) { FPosition += -ViewDir * S; }

	if ( Env->Console->IsKeyPressed( LK_S ) || Env->Console->IsKeyPressed( LK_DOWN ) ) { FPosition += ViewDir * S; }

	if ( Env->Console->IsKeyPressed( LK_A ) ) { FPosition +=  SideDir * S; }

	if ( Env->Console->IsKeyPressed( LK_D ) ) { FPosition += -SideDir * S; }

	LMatrix4 Rotation = LMatrix4::GetRotateMatrixAxis( Math::DegToRad( FPan ), SideDir ) * LMatrix4::GetRotateMatrixAxis( Math::DegToRad( FPitch ), FUpVector );

	FCurrentTransform = LMatrix4::GetTranslateMatrix( -FPosition ) * Rotation;
}