void YoYoParticleModel::func(myState& preState, myState& resultState,float deltaT)
{
	resultState.pos = preState.vel*deltaT;

	Vector3 e = (m_yoyoParticle.m_position - m_topParticle.m_position);
	e.Normalize();
	Vector3 Fk = -m_stiffness*((m_yoyoParticle.m_position - m_topParticle.m_position).CalcLength() - m_stringLength) * e;
	Vector3 Fc = -m_cofficient * (DotProduct(e, (m_yoyoParticle.m_velocity - m_topParticle.m_velocity))) *e;
	Vector3 A = Fk + Fc - m_yoyoParticle.m_mass*m_gravityVector - m_stringCofficient*m_yoyoParticle.m_velocity;
	
	Vector3 delta_prev_velocity = A*deltaT;
	delta_prev_velocity.z = -m_gravityVector.z*deltaT;
	resultState.vel = delta_prev_velocity;
	
}