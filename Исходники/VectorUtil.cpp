void rms::ComputeAlignAxisMatrix( const Vector3<Real> & vInitial,
								  const Vector3<Real> & vAlignWith, Matrix3<Real> & matrix )
{
	// compute cosine of angle between vectors
	Real axisDot = vAlignWith.Dot( vInitial );

	// compute rotation axis
	Vector3<Real> axisCross( vInitial.Cross( vAlignWith ) );

	// apply rotation if necessary
	if (axisCross.SquaredLength() > Wml::Math<Real>::EPSILON) {

		// compute normalized axis and angle, then create rotation around axis
		axisCross.Normalize();
		Real fAngle = Math<Real>::ACos( axisDot / vAlignWith.Length() );
		matrix.FromAxisAngle( axisCross, fAngle );

	} else if (axisDot < (Real)0) {

		// find some perpendicular vectors
		Wml::Vector3<Real> vPerp1, vPerp2;
		ComputePerpVectors( vInitial, vPerp1, vPerp2 );

		matrix.FromAxisAngle( vPerp1, (Real)180 * Math<Real>::DEG_TO_RAD );
	} else {
		matrix = Matrix3<Real>::IDENTITY;
	}
}