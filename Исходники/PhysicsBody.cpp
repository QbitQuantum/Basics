void PhysicsBody::SetInertiaTensor(Matrix& inertiaTensor)
{
	mInverseInertiaTensor = inertiaTensor.Inverse();
}