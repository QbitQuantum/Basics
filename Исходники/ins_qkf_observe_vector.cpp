void
basic_ins_qkf::obs_vector(const Vector3d& ref,
		const Vector3d& obs,
		double error)
{
#ifdef TIME_OPS
	timer clock;
	clock.start();
#endif
#define DEBUG_VECTOR_OBS 0

	Vector3d obs_ref = avg_state.orientation.conjugate()*obs;
	Vector3d v_residual = log<double>(Quaterniond().setFromTwoVectors(ref, obs_ref));

	Matrix<double, 3, 2> h_trans;
	h_trans.col(0) = ref.cross(
		(abs(ref.dot(obs_ref)) < 0.9994) ? obs_ref :
			(abs(ref.dot(Vector3d::UnitX())) < 0.707)
				? Vector3d::UnitX() : Vector3d::UnitY()).normalized();
	h_trans.col(1) = -ref.cross(h_trans.col(0));
	assert(!hasNaN(h_trans));
	assert(h_trans.isUnitary());

#ifdef RANK_ONE_UPDATES
	// Running a rank-one update here is a strict win.
	Matrix<double, 12, 1> update = Matrix<double, 12, 1>::Zero();
	for (int i = 0; i < 2; ++i) {
		double obs_error = error;
		double obs_cov = (h_trans.col(i).transpose() * cov.block<3, 3>(3, 3) * h_trans.col(i))[0];
		Matrix<double, 12, 1> gain = cov.block<12, 3>(0, 3) * h_trans.col(i) / (obs_error + obs_cov);
		update += gain * h_trans.col(i).transpose() * v_residual;
		// TODO: Get Eigen to treat cov as self-adjoint
		cov -= gain * h_trans.col(i).transpose() * cov.block<3, 12>(3, 0);
	}
#else
	// block-wise form.  This is much less efficient.
	Vector2d innovation = h_trans.transpose() * v_residual;
	Matrix<double, 12, 2> kalman_gain = cov.block<12, 3>(0, 3) * h_trans
			* (h_trans.transpose() * cov.block<3, 3>(3, 3) * h_trans
				+ (Vector2d() << error, error).finished().asDiagonal()).inverse();
	// TODO: Get Eigen to treat cov as self-adjoint
	cov -= kalman_gain * h_trans.transpose() * cov.block<3, 12>(3, 0);
	Matrix<double, 12, 1> update = (kalman_gain * innovation);
#endif


#if DEBUG_VECTOR_OBS
	// std::cout << "projected update: " << (obs_projection * update.segment<3>(3)).transpose() << "\n";
	std::cout << "deprojected update: " << update.segment<3>(3).transpose() << "\n";
#endif
	avg_state.apply_kalman_vec_update(update);

	assert(invariants_met());
#ifdef TIME_OPS
	double time = clock.stop() * 1e6;
	std::cout << "observe_vector(): " << time << "\n";
#endif

}