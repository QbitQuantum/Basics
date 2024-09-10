inline btVector3 evalEulerEqn(const btVector3& w1, const btVector3& w0, const btVector3& T, const btScalar dt,
	const btMatrix3x3 &I)
{
	const btVector3 w2 = I*w1 + w1.cross(I*w1)*dt - (T*dt + I*w0);
	return w2;
}