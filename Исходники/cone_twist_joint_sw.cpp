bool ConeTwistJointSW::setup(real_t p_timestep) {
	m_appliedImpulse = real_t(0.);

	//set bias, sign, clear accumulator
	m_swingCorrection = real_t(0.);
	m_twistLimitSign = real_t(0.);
	m_solveTwistLimit = false;
	m_solveSwingLimit = false;
	m_accTwistLimitImpulse = real_t(0.);
	m_accSwingLimitImpulse = real_t(0.);

	if (!m_angularOnly) {
		Vector3 pivotAInW = A->get_transform().xform(m_rbAFrame.origin);
		Vector3 pivotBInW = B->get_transform().xform(m_rbBFrame.origin);
		Vector3 relPos = pivotBInW - pivotAInW;

		Vector3 normal[3];
		if (relPos.length_squared() > CMP_EPSILON) {
			normal[0] = relPos.normalized();
		} else {
			normal[0] = Vector3(real_t(1.0), 0, 0);
		}

		plane_space(normal[0], normal[1], normal[2]);

		for (int i = 0; i < 3; i++) {
			memnew_placement(&m_jac[i], JacobianEntrySW(
												A->get_principal_inertia_axes().transposed(),
												B->get_principal_inertia_axes().transposed(),
												pivotAInW - A->get_transform().origin - A->get_center_of_mass(),
												pivotBInW - B->get_transform().origin - B->get_center_of_mass(),
												normal[i],
												A->get_inv_inertia(),
												A->get_inv_mass(),
												B->get_inv_inertia(),
												B->get_inv_mass()));
		}
	}

	Vector3 b1Axis1, b1Axis2, b1Axis3;
	Vector3 b2Axis1, b2Axis2;

	b1Axis1 = A->get_transform().basis.xform(this->m_rbAFrame.basis.get_axis(0));
	b2Axis1 = B->get_transform().basis.xform(this->m_rbBFrame.basis.get_axis(0));

	real_t swing1 = real_t(0.), swing2 = real_t(0.);

	real_t swx = real_t(0.), swy = real_t(0.);
	real_t thresh = real_t(10.);
	real_t fact;

	// Get Frame into world space
	if (m_swingSpan1 >= real_t(0.05f)) {
		b1Axis2 = A->get_transform().basis.xform(this->m_rbAFrame.basis.get_axis(1));
		//swing1  = btAtan2Fast( b2Axis1.dot(b1Axis2),b2Axis1.dot(b1Axis1) );
		swx = b2Axis1.dot(b1Axis1);
		swy = b2Axis1.dot(b1Axis2);
		swing1 = atan2fast(swy, swx);
		fact = (swy * swy + swx * swx) * thresh * thresh;
		fact = fact / (fact + real_t(1.0));
		swing1 *= fact;
	}

	if (m_swingSpan2 >= real_t(0.05f)) {
		b1Axis3 = A->get_transform().basis.xform(this->m_rbAFrame.basis.get_axis(2));
		//swing2 = btAtan2Fast( b2Axis1.dot(b1Axis3),b2Axis1.dot(b1Axis1) );
		swx = b2Axis1.dot(b1Axis1);
		swy = b2Axis1.dot(b1Axis3);
		swing2 = atan2fast(swy, swx);
		fact = (swy * swy + swx * swx) * thresh * thresh;
		fact = fact / (fact + real_t(1.0));
		swing2 *= fact;
	}

	real_t RMaxAngle1Sq = 1.0f / (m_swingSpan1 * m_swingSpan1);
	real_t RMaxAngle2Sq = 1.0f / (m_swingSpan2 * m_swingSpan2);
	real_t EllipseAngle = Math::abs(swing1 * swing1) * RMaxAngle1Sq + Math::abs(swing2 * swing2) * RMaxAngle2Sq;

	if (EllipseAngle > 1.0f) {
		m_swingCorrection = EllipseAngle - 1.0f;
		m_solveSwingLimit = true;

		// Calculate necessary axis & factors
		m_swingAxis = b2Axis1.cross(b1Axis2 * b2Axis1.dot(b1Axis2) + b1Axis3 * b2Axis1.dot(b1Axis3));
		m_swingAxis.normalize();

		real_t swingAxisSign = (b2Axis1.dot(b1Axis1) >= 0.0f) ? 1.0f : -1.0f;
		m_swingAxis *= swingAxisSign;

		m_kSwing = real_t(1.) / (A->compute_angular_impulse_denominator(m_swingAxis) +
										B->compute_angular_impulse_denominator(m_swingAxis));
	}

	// Twist limits
	if (m_twistSpan >= real_t(0.)) {
		Vector3 b2Axis2 = B->get_transform().basis.xform(this->m_rbBFrame.basis.get_axis(1));
		Quat rotationArc = Quat(b2Axis1, b1Axis1);
		Vector3 TwistRef = rotationArc.xform(b2Axis2);
		real_t twist = atan2fast(TwistRef.dot(b1Axis3), TwistRef.dot(b1Axis2));

		real_t lockedFreeFactor = (m_twistSpan > real_t(0.05f)) ? m_limitSoftness : real_t(0.);
		if (twist <= -m_twistSpan * lockedFreeFactor) {
			m_twistCorrection = -(twist + m_twistSpan);
			m_solveTwistLimit = true;

			m_twistAxis = (b2Axis1 + b1Axis1) * 0.5f;
			m_twistAxis.normalize();
			m_twistAxis *= -1.0f;

			m_kTwist = real_t(1.) / (A->compute_angular_impulse_denominator(m_twistAxis) +
											B->compute_angular_impulse_denominator(m_twistAxis));

		} else if (twist > m_twistSpan * lockedFreeFactor) {
			m_twistCorrection = (twist - m_twistSpan);
			m_solveTwistLimit = true;

			m_twistAxis = (b2Axis1 + b1Axis1) * 0.5f;
			m_twistAxis.normalize();

			m_kTwist = real_t(1.) / (A->compute_angular_impulse_denominator(m_twistAxis) +
											B->compute_angular_impulse_denominator(m_twistAxis));
		}
	}

	return true;
}