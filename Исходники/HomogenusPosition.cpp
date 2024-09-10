Vector3 HomogenusPosition::normalizeToVector3() const
{
	Vector3 result;
	
	result.setX(getX()/getW());
	result.setY(getY()/getW());
	result.setZ(getZ()/getW());
	
	return result;
}