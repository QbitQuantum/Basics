void PhysX::CreateSphereFromEye(int radius)
{
	NxVec3 t = m_Eye;
	NxVec3 vel = m_Dir;
	vel.normalize();
	vel *= 200.0f;
	CreateSphere(t, radius, DENSITY , &vel);
}