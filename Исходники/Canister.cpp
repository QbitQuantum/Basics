void Canister::Update(float DeltaTime, Terrain* terrain)
{
	XMFLOAT3	newPos	=	GetFloat3Value( Position );

	if ( !gPointLight )
	{
		gPointLight	=	new PointLight();
		gPointLight->GetGPULight()->Color		=	XMFLOAT4( 0.0f, 0.0f, 1.0f, 0.0f );
		gPointLight->GetGPULight()->Position	=	newPos;
		gPointLight->GetGPULight()->Range		=	33.333f * 0.40f;
		gPointLight->GetGPULight()->HasShadow	=	false;

		AddLight( gPointLight );
	}

	gTimeSpan	+=	DeltaTime;

	XMVECTOR QuatV = XMQuaternionRotationRollPitchYaw(0, DeltaTime, 0);
	XMFLOAT4 Quat;

	XMStoreFloat4(&Quat, QuatV);
	AddRotation( Quat );
	newPos.y	=	gOffset.y + ( gOffset.y - 2 ) * sin( 8 * gTimeSpan );
	MoveTo( newPos );
	newPos.y	-=	1.0f;
	if ( gPointLight )
		gPointLight->GetGPULight()->Position	=	newPos;

	Item::Update( DeltaTime, terrain );
}