	HawkQuaternion HawkQuaternion::Squad (Float fT,const HawkQuaternion& rkP, const HawkQuaternion& rkA,const HawkQuaternion& rkB, const HawkQuaternion& rkQ, bool shortestPath)
	{
		Float fSlerpT = 2.0f*fT*(1.0f-fT);
		HawkQuaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
		HawkQuaternion kSlerpQ = Slerp(fT, rkA, rkB);
		return Slerp(fSlerpT, kSlerpP ,kSlerpQ);
	}