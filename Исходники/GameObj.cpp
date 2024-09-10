//---------------------------------------------------------
Point3f GameObj::UnitVectorVelocity()
{
	Point3f temp = m_velocity;
	temp.Normalize();
	return temp;
}; 