	//-----------------------------------------------------------------------
	Quaternion Quaternion::Slerp(const Quaternion& rkP,
		const Quaternion& rkQ, Real fT)
	{
		return Slerp(fT, rkP, rkQ, false);
	}