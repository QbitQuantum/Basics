// This algorithm comes from Sebastian O.H. Madgwick's 2010 paper:
// "An efficient orientation filter for inertial and inertial/magnetic sensor arrays"
// https://www.samba.org/tridge/UAV/madgwick_internal_report.pdf
static void _psmove_orientation_fusion_imu_update(
	PSMoveOrientation *orientation_state,
	float delta_t,
	const Eigen::Vector3f &current_omega,
	const Eigen::Vector3f &current_g)
{
	// Current orientation from earth frame to sensor frame
	Eigen::Quaternionf SEq = orientation_state->quaternion;
	Eigen::Quaternionf SEq_new = SEq;

	// Compute the quaternion derivative measured by gyroscopes
	// Eqn 12) q_dot = 0.5*q*omega
	Eigen::Quaternionf omega = Eigen::Quaternionf(0.f, current_omega.x(), current_omega.y(), current_omega.z());
	Eigen::Quaternionf SEqDot_omega = Eigen::Quaternionf(SEq.coeffs() * 0.5f) *omega;

	if (current_g.isApprox(Eigen::Vector3f::Zero(), k_normal_epsilon))
	{
		// Get the direction of the gravitational fields in the identity pose		
		PSMove_3AxisVector identity_g= psmove_orientation_get_gravity_calibration_direction(orientation_state);
		Eigen::Vector3f k_identity_g_direction = Eigen::Vector3f(identity_g.x, identity_g.y, identity_g.z);

		// Eqn 15) Applied to the gravity vector
		// Fill in the 3x1 objective function matrix f(SEq, Sa) =|f_g|
		Eigen::Matrix<float, 3, 1> f_g;
		psmove_alignment_compute_objective_vector(SEq, k_identity_g_direction, current_g, f_g, NULL);

		// Eqn 21) Applied to the gravity vector
		// Fill in the 4x3 objective function Jacobian matrix: J_gb(SEq)= [J_g]
		Eigen::Matrix<float, 4, 3> J_g;
		psmove_alignment_compute_objective_jacobian(SEq, k_identity_g_direction, J_g);

		// Eqn 34) gradient_F= J_g(SEq)*f(SEq, Sa)
		// Compute the gradient of the objective function
		Eigen::Matrix<float, 4, 1> gradient_f = J_g * f_g;
		Eigen::Quaternionf SEqHatDot =
			Eigen::Quaternionf(gradient_f(0, 0), gradient_f(1, 0), gradient_f(2, 0), gradient_f(3, 0));

		// normalize the gradient
		psmove_quaternion_normalize_with_default(SEqHatDot, *k_psmove_quaternion_zero);

		// Compute the estimated quaternion rate of change
		// Eqn 43) SEq_est = SEqDot_omega - beta*SEqHatDot
		Eigen::Quaternionf SEqDot_est = Eigen::Quaternionf(SEqDot_omega.coeffs() - SEqHatDot.coeffs()*beta);

		// Compute then integrate the estimated quaternion rate
		// Eqn 42) SEq_new = SEq + SEqDot_est*delta_t
		SEq_new = Eigen::Quaternionf(SEq.coeffs() + SEqDot_est.coeffs()*delta_t);
	}
	else
	{
		SEq_new = Eigen::Quaternionf(SEq.coeffs() + SEqDot_omega.coeffs()*delta_t);
	}

	// Make sure the net quaternion is a pure rotation quaternion
	SEq_new.normalize();

	// Save the new quaternion back into the orientation state
	orientation_state->quaternion = SEq_new;
}