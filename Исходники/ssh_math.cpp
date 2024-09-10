	quat quat::squad(const quat& q1, const quat& q2, const quat& q3, float t, bool shortestPath) const
	{
		float slerpT(2.0f * t * (1.0f - t));
		quat slerpP(slerp(q3, t, shortestPath));
		quat slerpQ(q1.slerp(q2, t, false));
		return slerpP.slerp(slerpQ, slerpT, shortestPath);
	}