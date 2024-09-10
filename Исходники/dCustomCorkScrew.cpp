void dCustomCorkScrew::SubmitAngularRow(const dMatrix& matrix0, const dMatrix& matrix1, dFloat timestep)
{
	dMatrix localMatrix(matrix0 * matrix1.Inverse());
	dVector euler0;
	dVector euler1;
	localMatrix.GetEulerAngles(euler0, euler1, m_pitchRollYaw);

	dVector rollPin(dSin(euler0[1]), dFloat(0.0f), dCos(euler0[1]), dFloat(0.0f));
	rollPin = matrix1.RotateVector(rollPin);

	NewtonUserJointAddAngularRow(m_joint, -euler0[1], &matrix1[1][0]);
	NewtonUserJointSetRowStiffness(m_joint, m_stiffness);
	NewtonUserJointAddAngularRow(m_joint, -euler0[2], &rollPin[0]);
	NewtonUserJointSetRowStiffness(m_joint, m_stiffness);

	// the joint angle can be determined by getting the angle between any two non parallel vectors
	m_curJointAngle.Update(euler0.m_x);

	// save the current joint Omega
	dVector omega0(0.0f);
	dVector omega1(0.0f);
	NewtonBodyGetOmega(m_body0, &omega0[0]);
	if (m_body1) {
		NewtonBodyGetOmega(m_body1, &omega1[0]);
	}
	m_angularOmega = (omega0 - omega1).DotProduct3(matrix1.m_front);

	if (m_options.m_option2) {
		if (m_options.m_option3) {
			dCustomCorkScrew::SubmitConstraintLimitSpringDamper(matrix0, matrix1, timestep);
		} else {
			dCustomCorkScrew::SubmitConstraintLimits(matrix0, matrix1, timestep);
		}
	} else if (m_options.m_option3) {
		dCustomCorkScrew::SubmitConstraintSpringDamper(matrix0, matrix1, timestep);
	} else if (m_angularFriction != 0.0f) {
		NewtonUserJointAddAngularRow(m_joint, 0, &matrix1.m_front[0]);
		NewtonUserJointSetRowStiffness(m_joint, m_stiffness);
		NewtonUserJointSetRowAcceleration(m_joint, -m_angularOmega / timestep);
		NewtonUserJointSetRowMinimumFriction(m_joint, -m_angularFriction);
		NewtonUserJointSetRowMaximumFriction(m_joint, m_angularFriction);
	}
}