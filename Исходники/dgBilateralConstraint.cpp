dgVector dgBilateralConstraint::CalculateGlobalMatrixAndAngle (dgMatrix& globalMatrix0, dgMatrix& globalMatrix1) const
{
	_ASSERTE (m_body0);
	_ASSERTE (m_body1);
	const dgMatrix& body0Matrix = m_body0->GetMatrix();
	const dgMatrix& body1Matrix = m_body1->GetMatrix();
//	dgMatrix body1Matrix (dgGetIdentityMatrix());
//	if (m_body1) {
//		body1Matrix = m_body1->GetMatrix();
//	}

	globalMatrix0 = m_localMatrix0 * body0Matrix;
	globalMatrix1 = m_localMatrix1 * body1Matrix;

	dgMatrix relMatrix (globalMatrix1 * globalMatrix0.Inverse());

	_ASSERTE (dgAbsf (dgFloat32 (1.0f) - (relMatrix.m_front % relMatrix.m_front)) < 1.0e-5f); 
	_ASSERTE (dgAbsf (dgFloat32 (1.0f) - (relMatrix.m_up % relMatrix.m_up)) < 1.0e-5f); 
	_ASSERTE (dgAbsf (dgFloat32 (1.0f) - (relMatrix.m_right % relMatrix.m_right)) < 1.0e-5f); 
//	_ASSERTE ((relMatrix.m_posit % relMatrix.m_posit) < 1.0e-3f);

	return relMatrix.CalcPitchYawRoll ();
}