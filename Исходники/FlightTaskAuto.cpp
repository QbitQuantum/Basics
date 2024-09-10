bool FlightTaskAuto::_compute_heading_from_2D_vector(float &heading, Vector2f v)
{
	if (PX4_ISFINITE(v.length()) && v.length() > SIGMA_NORM) {
		v.normalize();
		// To find yaw: take dot product of x = (1,0) and v
		// and multiply by the sign given of cross product of x and v.
		// Dot product: (x(0)*v(0)+(x(1)*v(1)) = v(0)
		// Cross product: x(0)*v(1) - v(0)*x(1) = v(1)
		heading =  math::sign(v(1)) * wrap_pi(acosf(v(0)));
		return true;
	}

	// heading unknown and therefore do not change heading
	return false;
}