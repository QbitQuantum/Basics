void FGenSpring::updateForce(RigidBody &parent, const Scalar &timeStep)
{
	Vec3 relPivotInParent = parent.getPointInWorldSpace(m_pivotInParent);
	Vec3 relPivotInOther = m_other->getPointInWorldSpace(m_pivotInOther);

	Vec3 force = parent.getPosition() + relPivotInParent;
	force -= m_other->getPosition() + relPivotInOther;

	Scalar magnitude = force.length();
	magnitude -= m_restLength;

	if(!m_isStretchOnly || (m_isStretchOnly && magnitude > 0))
	{
		magnitude *= m_springConstant;

		force.normalize();
		force *= -magnitude;
		parent.applyForce(force, relPivotInParent);
	}
}