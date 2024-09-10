void DebugLineSystem::AddArrow( const LTVector & vStart, const LTVector & vEnd,
								const DebugLine::Color & color /* = Color::White */,
								uint8 nAlpha /* = 255 */ )
{
	const float fHeadSize = 4.0f;
	LTVector vStartToEnd = vEnd - vStart;
	float fLen = vStartToEnd.Mag();
	if( vStartToEnd != LTVector::GetIdentity() )
	{
		vStartToEnd.Normalize();
	}

	AddLine( vStart, vEnd, color, nAlpha);

	LTVector vArrow = vStart + ( ( fLen * 0.9f ) * vStartToEnd );

	LTVector vUp( 0.f, 1.f, 0.f );
	LTVector vNorm;
	if( vStartToEnd != vUp )
	{
		vNorm = vStartToEnd.Cross( vUp );
	}
	else {
		vNorm = LTVector( 1.f, 0.f, 0.f );
	}

	vNorm *= ( fHeadSize/2.0f );
	AddLine( vArrow - vNorm, vArrow + vNorm, color, nAlpha);

	AddLine( vArrow + vNorm, vEnd, color, nAlpha);
	AddLine( vArrow - vNorm, vEnd, color, nAlpha);
}