/////////////////////////////////////////////////////////////////////
// get the closest point to pt in the primative
bool
sphere::
closestPtIn ( vec3& dest, ValueType xval, ValueType yval, ValueType zval ) const
{
	if ( isEmpty () )
		return false;

	if ( contains ( xval, yval, zval ) )
		dest.set ( xval, yval, zval );
	else
	{
		dest.set ( xval, yval, zval );
		dest -= center;
		dest.normalize ();
		dest *= radius;
		dest += center;
	}
	
	return true;
}