void SliderJointSW::testAngLimits(void) {
	m_angDepth = real_t(0.);
	m_solveAngLim = false;
	if (m_lowerAngLimit <= m_upperAngLimit) {
		const Vector3 axisA0 = m_calculatedTransformA.basis.get_axis(1);
		const Vector3 axisA1 = m_calculatedTransformA.basis.get_axis(2);
		const Vector3 axisB0 = m_calculatedTransformB.basis.get_axis(1);
		real_t rot = atan2fast(axisB0.dot(axisA1), axisB0.dot(axisA0));
		if (rot < m_lowerAngLimit) {
			m_angDepth = rot - m_lowerAngLimit;
			m_solveAngLim = true;
		} else if (rot > m_upperAngLimit) {
			m_angDepth = rot - m_upperAngLimit;
			m_solveAngLim = true;
		}
	}
} // SliderJointSW::testAngLimits()