HingeJointSW::HingeJointSW(BodySW *rbA, BodySW *rbB, const Vector3 &pivotInA, const Vector3 &pivotInB,
		const Vector3 &axisInA, const Vector3 &axisInB) :
		JointSW(_arr, 2) {

	A = rbA;
	B = rbB;

	m_rbAFrame.origin = pivotInA;

	// since no frame is given, assume this to be zero angle and just pick rb transform axis
	Vector3 rbAxisA1 = rbA->get_transform().basis.get_axis(0);

	Vector3 rbAxisA2;
	real_t projection = axisInA.dot(rbAxisA1);
	if (projection >= 1.0f - CMP_EPSILON) {
		rbAxisA1 = -rbA->get_transform().basis.get_axis(2);
		rbAxisA2 = rbA->get_transform().basis.get_axis(1);
	} else if (projection <= -1.0f + CMP_EPSILON) {
		rbAxisA1 = rbA->get_transform().basis.get_axis(2);
		rbAxisA2 = rbA->get_transform().basis.get_axis(1);
	} else {
		rbAxisA2 = axisInA.cross(rbAxisA1);
		rbAxisA1 = rbAxisA2.cross(axisInA);
	}

	m_rbAFrame.basis = Matrix3(rbAxisA1.x, rbAxisA2.x, axisInA.x,
			rbAxisA1.y, rbAxisA2.y, axisInA.y,
			rbAxisA1.z, rbAxisA2.z, axisInA.z);

	Quat rotationArc = Quat(axisInA, axisInB);
	Vector3 rbAxisB1 = rotationArc.xform(rbAxisA1);
	Vector3 rbAxisB2 = axisInB.cross(rbAxisB1);

	m_rbBFrame.origin = pivotInB;
	m_rbBFrame.basis = Matrix3(rbAxisB1.x, rbAxisB2.x, -axisInB.x,
			rbAxisB1.y, rbAxisB2.y, -axisInB.y,
			rbAxisB1.z, rbAxisB2.z, -axisInB.z);

	//start with free
	m_lowerLimit = Math_PI;
	m_upperLimit = -Math_PI;

	m_useLimit = false;
	m_biasFactor = 0.3f;
	m_relaxationFactor = 1.0f;
	m_limitSoftness = 0.9f;
	m_solveLimit = false;

	tau = 0.3;

	m_angularOnly = false;
	m_enableAngularMotor = false;

	A->add_constraint(this, 0);
	B->add_constraint(this, 1);
}