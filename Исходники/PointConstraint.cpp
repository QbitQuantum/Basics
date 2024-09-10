Imath::M44f PointConstraint::computeConstraint( const Imath::M44f &fullTargetTransform, const Imath::M44f &fullInputTransform ) const
{
	const V3f worldPosition = fullTargetTransform.translation() + offsetPlug()->getValue();
	M44f result = fullInputTransform;
	
	if( xEnabledPlug()->getValue() )
	{
		result[3][0] = worldPosition[0];
	}
	
	if( yEnabledPlug()->getValue() )
	{
		result[3][1] = worldPosition[1];
	}
	
	if( zEnabledPlug()->getValue() )
	{
		result[3][2] = worldPosition[2];
	}
	
	return result;
}