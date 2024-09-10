	//! applies a force at a location R relative to the object's origin
	void applyForce(const math::matrix3x1<float> &force, const math::matrix3x1<float> &r) {
		netForce += force;
		netTorque += r.cross(force);
	}