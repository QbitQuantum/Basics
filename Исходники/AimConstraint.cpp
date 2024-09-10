Imath::M44f AimConstraint::computeConstraint( const Imath::M44f &fullTargetTransform, const Imath::M44f &fullInputTransform ) const
{
	// decompose into scale, shear, rotate and translate
	V3f s, h, r, t;
	extractSHRT( fullInputTransform, s, h, r, t );

	// figure out the aim matrix
	const V3f toDir = ( fullTargetTransform.translation() - t ).normalized();
	const M44f rotationMatrix = rotationMatrixWithUpDir( aimPlug()->getValue(), toDir, upPlug()->getValue() );

	// rebuild, replacing rotate with the aim matrix
	M44f result;
	result.translate( t );
	result.shear( h );
	result = rotationMatrix * result;
	result.scale( s );

	return result;
}