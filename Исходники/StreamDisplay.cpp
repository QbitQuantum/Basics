void StreamDisplay::Load( const RString & /* unreferenced: _sMetricsGroup  */)
{
	// XXX: actually load from the metrics group passed in -aj
	RString sMetricsGroup = "StreamDisplay";

	m_transformPill.SetFromReference( THEME->GetMetricR(sMetricsGroup,"PillTransformFunction") );
	VELOCITY_MULTIPLIER.Load(sMetricsGroup, "VelocityMultiplier");
	VELOCITY_MIN.Load(sMetricsGroup, "VelocityMin");
	VELOCITY_MAX.Load(sMetricsGroup, "VelocityMax");
	SPRING_MULTIPLIER.Load(sMetricsGroup, "SpringMultiplier");
	VISCOSITY_MULTIPLIER.Load(sMetricsGroup, "ViscosityMultiplier");

	float fTextureCoordScaleX = THEME->GetMetricF(sMetricsGroup,"TextureCoordScaleX");
	int iNumPills = static_cast<int>(THEME->GetMetricF(sMetricsGroup,"NumPills"));
	m_bAlwaysBounce = THEME->GetMetricB(sMetricsGroup,"AlwaysBounceNormalBar");

	FOREACH_ENUM( StreamType, st )
	{
		ASSERT( m_vpSprPill[st].empty() );

		for( int i=0; i<iNumPills; i++ )
		{
			Sprite *pSpr = new Sprite;

			pSpr->Load( THEME->GetPathG( sMetricsGroup, StreamTypeToString(st) ) );
			m_vpSprPill[st].push_back( pSpr );

			m_transformPill.TransformItemDirect( *pSpr, -1, i, iNumPills );
			float f = 1 / fTextureCoordScaleX;
			pSpr->SetCustomTextureRect( RectF(f*i,0,f*(i+1),1) );

			this->AddChild( pSpr );
		}
	}