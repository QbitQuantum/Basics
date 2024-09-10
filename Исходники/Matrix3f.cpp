Matrix3f Matrix3f::inverse() const
{
	bool isSingular;
	return inverse( isSingular );
}