LLQuaternion nlerp(F32 t, const LLQuaternion &q)
{
	if (q.mQ[VW] < 0.f)
	{
		return slerp(t, q);
	}
	else
	{
		return lerp(t, q);
	}
}