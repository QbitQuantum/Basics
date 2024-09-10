void RigidBody3::ApplyForceAtBodyPoint(const vec3& force, const vec3& point)
{
	// forces += force;
	torques += force.Cross( modelMatrix.RotateFromLocalToGlobal(point) );
}