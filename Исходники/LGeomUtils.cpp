// build the basis of complementary 2-dimensional space
void BuildComplementaryBasis( const LVector3& N, LVector3& V1, LVector3& V2 )
{
	V1 = N.Cross( vec3( 1, 0, 0 ) );

	if ( V1.SqrLength() <= Linderdaum::Math::EPSILON )
	{
		V1 = N.Cross( vec3( 0, 1, 0 ) );

		if ( V1.SqrLength() <= Linderdaum::Math::EPSILON )
		{
			V1 = N.Cross( vec3( 0, 0, 1 ) );
		}
	}

	V2 = N.Cross( V1 );

	V1.Normalize();
	V2.Normalize();
}