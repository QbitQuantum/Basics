//	Find the angle between 2 vectors
float AngleBetweenVectors(tVector2D v1, tVector2D v2)
{
	//	Dot product
	float fDot = DotProduct(v1, v2);
	//	Length of those vectors
	float fLength =  Vector2DLength(v1) * Vector2DLength(v2);

	//	Make sure we don't get a divide by zero error.
	if (fLength == 0.0f)	return 0.0f;

	//	Calculate the angle between the two vectors
	float fAngle = acos( fDot / fLength );

	//	Make sure the number is not indefinite.  Shows up as -1.#IND00000.  Not a number.
	if (_isnan(fAngle))
		return 0.0f;

	//	Return the angle.
	return fAngle;
}