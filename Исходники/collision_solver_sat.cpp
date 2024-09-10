static void _generate_contacts_edge_edge(const Vector3 *p_points_A, int p_point_count_A, const Vector3 *p_points_B, int p_point_count_B, _CollectorCallback *p_callback) {

#ifdef DEBUG_ENABLED
	ERR_FAIL_COND(p_point_count_A != 2);
	ERR_FAIL_COND(p_point_count_B != 2); // circle is actually a 4x3 matrix
#endif

	Vector3 rel_A = p_points_A[1] - p_points_A[0];
	Vector3 rel_B = p_points_B[1] - p_points_B[0];

	Vector3 c = rel_A.cross(rel_B).cross(rel_B);

	//if ( Math::abs(rel_A.dot(c) )<_EDGE_IS_VALID_SUPPORT_TRESHOLD ) {
	if (Math::abs(rel_A.dot(c)) < CMP_EPSILON) {

		// should handle somehow..
		//ERR_PRINT("TODO FIX");
		//return;

		Vector3 axis = rel_A.normalized(); //make an axis
		Vector3 base_A = p_points_A[0] - axis * axis.dot(p_points_A[0]);
		Vector3 base_B = p_points_B[0] - axis * axis.dot(p_points_B[0]);

		//sort all 4 points in axis
		real_t dvec[4] = { axis.dot(p_points_A[0]), axis.dot(p_points_A[1]), axis.dot(p_points_B[0]), axis.dot(p_points_B[1]) };

		SortArray<real_t> sa;
		sa.sort(dvec, 4);

		//use the middle ones as contacts
		p_callback->call(base_A + axis * dvec[1], base_B + axis * dvec[1]);
		p_callback->call(base_A + axis * dvec[2], base_B + axis * dvec[2]);

		return;
	}

	real_t d = (c.dot(p_points_B[0]) - p_points_A[0].dot(c)) / rel_A.dot(c);

	if (d < 0.0)
		d = 0.0;
	else if (d > 1.0)
		d = 1.0;

	Vector3 closest_A = p_points_A[0] + rel_A * d;
	Vector3 closest_B = Geometry::get_closest_point_to_segment_uncapped(closest_A, p_points_B);
	p_callback->call(closest_A, closest_B);
}