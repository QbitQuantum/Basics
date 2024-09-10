float3	EffectTranslucency::ComputePhase( const float3& _Anisotropy, int _PixelDistance, int _SamplesCount, float _TexelSize, float _SliceThickness )
{
	// Imagine receiving light from a point above you offset by a distance d
	//
	//                    0      Source
	// -------------------*--------*-------------
	//                    |      /
	//                    |    /
	//                    |  /
	//                    |/
	// -------------------*----------------------
	//                 Receiver
	//
	// The source and receiver make an angle with the vertical, diffusion direction.
	// This is that angle we compute the phase for.
	//
	float		Theta = atanf( _PixelDistance * _TexelSize / _SliceThickness );
	float		CosTheta = cosf( Theta );

	float3	P;
	P.x = (1.0f - _Anisotropy.x*_Anisotropy.x) * powf( 1.0f + _Anisotropy.x*_Anisotropy.x - 2.0f*_Anisotropy.x*CosTheta, -1.5f );
	P.y = (1.0f - _Anisotropy.y*_Anisotropy.y) * powf( 1.0f + _Anisotropy.y*_Anisotropy.y - 2.0f*_Anisotropy.y*CosTheta, -1.5f );
	P.z = (1.0f - _Anisotropy.z*_Anisotropy.z) * powf( 1.0f + _Anisotropy.z*_Anisotropy.z - 2.0f*_Anisotropy.z*CosTheta, -1.5f );
	P = INV4PI * P;	// Normalize over hemisphere

	// Now, compute the weight to give this phase function
	// The weight is simply the solid angle covered by all the texels using the phase function
	// This solid angle is a spherical band between current and next pixel angles, divided by the amount of samples taken in that band
	//
	float		NextTheta = atanf( (1+_PixelDistance) * _TexelSize / _SliceThickness );
	float		CosNextTheta = cosf( NextTheta );

	float		SolidAngle = TWOPI * (CosTheta - CosNextTheta);	// Solid angle covered by the spherical band in [Theta,NextTheta]
	SolidAngle /= _SamplesCount;								// Solid angle of a single sample in that band

	return SolidAngle * P;
}