vqs vqs::operator+( const vqs&	pVQS )
{
	CVector3 transAdd = translation() + pVQS.translation();
	DQuaternion quatAdd = orientation() + pVQS.orientation();
	float scaleAdd = scale() + pVQS.scale(); 
	vqs result;
	result.Set(transAdd, quatAdd, scaleAdd);
	return result;
}