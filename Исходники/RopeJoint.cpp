bool RopeJoint::SolvePositionConstraints(const SolverData& data)
{
	Vec2 cA = data.positions[m_indexA].c;
	float32 aA = data.positions[m_indexA].a;
	Vec2 cB = data.positions[m_indexB].c;
	float32 aB = data.positions[m_indexB].a;

	Rot qA(aA), qB(aB);

	Vec2 rA = Mul(qA, m_localAnchorA - m_localCenterA);
	Vec2 rB = Mul(qB, m_localAnchorB - m_localCenterB);
	Vec2 u = cB + rB - cA - rA;

	float32 length = u.Normalize();
	float32 C = length - m_maxLength;

	C = Clamp(C, 0.0f, maxLinearCorrection);

	float32 impulse = -m_mass * C;
	Vec2 P = impulse * u;

	cA -= m_invMassA * P;
	aA -= m_invIA * Cross(rA, P);
	cB += m_invMassB * P;
	aB += m_invIB * Cross(rB, P);

	data.positions[m_indexA].c = cA;
	data.positions[m_indexA].a = aA;
	data.positions[m_indexB].c = cB;
	data.positions[m_indexB].a = aB;

	return length - m_maxLength < linearSlop;
}