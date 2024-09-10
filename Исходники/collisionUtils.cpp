// Does the same as capsuleCapsuleDistance except that b_end is automatically set to b_start. Should be improved.
double capsuleSphereDistance(const Vector3d& a_start, const Vector3d& a_end, const double a_radius, const Vector3d& b_start, const double b_radius, Vector3d& direction)
{
	Vector3d b_end = b_start;
	
	// Line parametrization
	// L1 : P(s) = a_start + s * (a_end - a_start) = a_start + s * u
	// L2 : Q(t) = b_start + t * (b_end - b_start) = b_start + t * v
	Vector3d u = a_end - a_start;
	Vector3d v = b_end - b_start;
	Vector3d w = a_start - b_start;
	Vector3d a_end_minus_b_start = a_end - b_start;
	Vector3d a_start_minus_b_end = a_start - b_end;
	double u_dot_u = u.dot(u);
	double u_dot_v = u.dot(v);
	double v_dot_v = v.dot(v);
	double u_dot_w = u.dot(w);
	double v_dot_w = v.dot(w);
	
	// SPHERE-SPHERE collision
	Vector3d start_sphere_start_sphere = w;
	double start_sphere_start_sphere_squared_dist = start_sphere_start_sphere.squaredNorm();
	Vector3d start_sphere_end_sphere = a_start_minus_b_end;
	double start_sphere_end_sphere_squared_dist = start_sphere_end_sphere.squaredNorm();
	Vector3d end_sphere_start_sphere = a_end_minus_b_start;
	double end_sphere_start_sphere_squared_dist = end_sphere_start_sphere.squaredNorm();
	Vector3d end_sphere_end_sphere = a_end - b_end;
	double end_sphere_end_sphere_squared_dist = end_sphere_end_sphere.squaredNorm();
	
	// SPHERE-CYLINDER collision
	// Ignores the case when the center of the sphere is outside the range of the line segment even though the sphere might still collide with the cylinder's end cap.
	// This case is taken care by sphere-sphere collision.
	double t;			// line parameter of the cylinder's axis
	Vector3d start_sphere_cyl, end_sphere_cyl, cyl_start_sphere, cyl_end_sphere;
	double start_sphere_cyl_squared_dist, end_sphere_cyl_squared_dist, cyl_start_sphere_squared_dist, cyl_end_sphere_squared_dist;
	
	t = v_dot_w/v.squaredNorm();
	if (t < 0 || t > 1) {
		start_sphere_cyl_squared_dist = numeric_limits<double>::max();
	} else {
		start_sphere_cyl = (w - t*v);
		start_sphere_cyl_squared_dist = start_sphere_cyl.squaredNorm();
	}
	
	t = a_end_minus_b_start.dot(v)/v.squaredNorm();
	if (t < 0 || t > 1) {
		end_sphere_cyl_squared_dist = numeric_limits<double>::max();
	} else {
		end_sphere_cyl = (a_end_minus_b_start - t*v);
		end_sphere_cyl_squared_dist = end_sphere_cyl.squaredNorm();
	}
	
	t = -u_dot_w/u.squaredNorm();
	if (t < 0 || t > 1) {
		cyl_start_sphere_squared_dist = numeric_limits<double>::max();
	} else {
		cyl_start_sphere = (w + t*u);
		cyl_start_sphere_squared_dist = cyl_start_sphere.squaredNorm();
	}
		
	t = -a_start_minus_b_end.dot(u)/u.squaredNorm();
	if (t < 0 || t > 1) {
		cyl_end_sphere_squared_dist = numeric_limits<double>::max();
	} else {
		cyl_end_sphere = (a_start_minus_b_end + t*u);
		cyl_end_sphere_squared_dist = cyl_end_sphere.squaredNorm();
	}

	// CYLINDER-CYLINDER collision
	// Ignores the case when the closest distance vector is not perpendicular to the line segment.
	// This case is taken care by the other two cases.
	double D = u_dot_u * v_dot_v - u_dot_v * u_dot_v;       									// denominator for s and t parameter
	Vector3d cyl_cyl;
	double cyl_cyl_squared_dist;
	
  if (D < INTERSECTION_PARALLEL_CHECK_FACTOR) { 														// the lines are almost parallel
    if (start_sphere_cyl_squared_dist == numeric_limits<double>::max() &&
    		end_sphere_cyl_squared_dist == numeric_limits<double>::max() &&
    		cyl_start_sphere_squared_dist == numeric_limits<double>::max() &&
    		cyl_end_sphere_squared_dist == numeric_limits<double>::max()) {			// If the closest distance vector is not perpendicular to the line segments.
    																																				// In other words, if the closest distance of the infinite lines is not the same as the closest distance of the finite segments.
    	cyl_cyl_squared_dist = numeric_limits<double>::max();
    } else {
    	cyl_cyl = (w - (v_dot_w/v_dot_v) * v);
			cyl_cyl_squared_dist = cyl_cyl.squaredNorm();
		}
  } else {																																	// the line segements are not almost parallel
    double sN = (u_dot_v * v_dot_w - v_dot_v * u_dot_w);										// nominator of s parameter
    double tN = (u_dot_u * v_dot_w - u_dot_v * u_dot_w);										// nominator of t parameter
    if (sN < 0.0 || sN > D || tN < 0.0 || tN > D) { 											// If the closest distance vector is not perpendicular to the line segments.
    																																				// In other words, if the closest distance doesn't happen within the segment limits.
    	cyl_cyl_squared_dist = numeric_limits<double>::max();
    } else {
    	cyl_cyl = (w + (sN/D * u) - (tN/D * v));
    	cyl_cyl_squared_dist = cyl_cyl.squaredNorm();
    }
  }
	
	// MINIMUN OF THE SQUARED DISTANCES
	double min_squared_dist = start_sphere_start_sphere_squared_dist;
	direction = start_sphere_start_sphere;
	
	if (min_squared_dist >= start_sphere_end_sphere_squared_dist) {
		min_squared_dist = start_sphere_end_sphere_squared_dist;
		direction = start_sphere_end_sphere;
	}
	
	if (min_squared_dist >= end_sphere_start_sphere_squared_dist) {
		min_squared_dist = end_sphere_start_sphere_squared_dist;
		direction = end_sphere_start_sphere;
	}

	if (min_squared_dist >= end_sphere_end_sphere_squared_dist) {
		min_squared_dist = end_sphere_end_sphere_squared_dist;
		direction = end_sphere_end_sphere;
	}
	
	if (min_squared_dist >= start_sphere_cyl_squared_dist) {
		min_squared_dist = start_sphere_cyl_squared_dist;
		direction = start_sphere_cyl;
	}
	
	if (min_squared_dist >= end_sphere_cyl_squared_dist) {
		min_squared_dist = end_sphere_cyl_squared_dist;
		direction = end_sphere_cyl;
	}
	
	if (min_squared_dist >= cyl_start_sphere_squared_dist) {
		min_squared_dist = cyl_start_sphere_squared_dist;
		direction = cyl_start_sphere;
	}
	
	if (min_squared_dist >= cyl_end_sphere_squared_dist) {
		min_squared_dist = cyl_end_sphere_squared_dist;
		direction = cyl_end_sphere;
	}
	
	if (min_squared_dist >= cyl_cyl_squared_dist) {
		min_squared_dist = cyl_cyl_squared_dist;
		direction = cyl_cyl;
	}
	
	return sqrt(min_squared_dist) - a_radius - b_radius;
}