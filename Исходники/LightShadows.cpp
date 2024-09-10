IC float PLC_energy	(Fvector& P, Fvector& N, light* L, float E)
{
	Fvector Ldir;
	if (L->flags.type==IRender_Light::DIRECT)
	{
		// Cos
		Ldir.invert	(L->direction);
		float D		= Ldir.dotproduct( N );
		if( D <=0 )						return 0;
		
		// Trace Light
		float A		= D*E;
		return A;
	} else {
		// Distance
		float sqD	= P.distance_to_sqr(L->position);
		if (sqD > (L->range*L->range))	return 0;
		
		// Dir
		Ldir.sub	(L->position,P);
		Ldir.normalize_safe();
		float D		= Ldir.dotproduct( N );
		if( D <=0 )						return 0;
		
		// Trace Light
		float R		= _sqrt		(sqD);
		float att	= 1-(1/(1+R));
		float A		= D * E * att;
		return A;
	}
}