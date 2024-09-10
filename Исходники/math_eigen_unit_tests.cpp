static bool math_eigen_test_rotation_method_consistency(const Eigen::Quaternionf &q, const Eigen::Vector3f &v)
{
	bool success = true;

	assert_eigen_quaternion_is_normalized(q);

	// This is the same as computing the rotation by computing: q^-1*[0,v]*q, but cheaper
	Eigen::Vector3f v_rotated = eigen_vector3f_clockwise_rotate(q, v);

	// Make sure doing the matrix based rotation performs the same result
	{
		Eigen::Matrix3f m = eigen_quaternion_to_clockwise_matrix3f(q);
		Eigen::Vector3f v_test = m * v;

		success &= v_test.isApprox(v_rotated, k_normal_epsilon);
		assert(success);
	}

	// Make sure the Hamilton product style rotation matches
	{
		Eigen::Quaternionf v_as_quaternion = Eigen::Quaternionf(0.f, v.x(), v.y(), v.z());
		Eigen::Quaternionf q_inv = q.conjugate();
		Eigen::Quaternionf qinv_v = q_inv * v_as_quaternion;
		Eigen::Quaternionf qinv_v_q = qinv_v * q;

		success &=
			is_nearly_equal(qinv_v_q.w(), 0.f, k_normal_epsilon) &&
			is_nearly_equal(qinv_v_q.x(), v_rotated.x(), k_normal_epsilon) &&
			is_nearly_equal(qinv_v_q.y(), v_rotated.y(), k_normal_epsilon) &&
			is_nearly_equal(qinv_v_q.z(), v_rotated.z(), k_normal_epsilon);
		assert(success);
	}

	return success;
}