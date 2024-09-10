Vector4F operator - (const Vector4F& rVector)
{
	return Vector4F(-rVector.x(), -rVector.y(), -rVector.z(), rVector.w());
}