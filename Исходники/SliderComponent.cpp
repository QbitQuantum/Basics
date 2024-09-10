Vector3f MakePosition( float const fwdDist, float const upDist, float const leftDist )
{
	static const Vector3f FWD( 0.0f, 0.0f, -1.0f );
	static const Vector3f UP( 0.0f, 1.0f, 0.0f );
	static const Vector3f LEFT( FWD.Cross( UP ) );

	// we only scale left and up by texel scale because those correspond to width / height
	return FWD * fwdDist + ( UP * upDist + LEFT * leftDist ) * VRMenuObject::DEFAULT_TEXEL_SCALE;
}