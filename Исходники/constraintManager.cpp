void ConstraintManager::computeConstraintForces()
{
	for (std::vector< FixedDistanceConstraint* >::iterator iter = m_constraintForces.begin(); iter < m_constraintForces.end(); ++iter)
	{
		(*iter)->populateConstraintMatrix( m_constraint );
		(*iter)->populateJacobian( m_jacobian );
		(*iter)->populateJacobianDerivative( m_jacobianDeriv );
	}
	Eigen::Matrix< double, Eigen::Dynamic, Eigen::Dynamic > invMassMatrix;
	Eigen::Matrix< double, Eigen::Dynamic, 1 > velocityCurrent;
	Eigen::Matrix< double, Eigen::Dynamic, 1 > forceCurrent;
	m_particleManager.getInvMassMatrix( invMassMatrix );
	m_particleManager.getCurrentState( velocityCurrent, false, true );
	m_particleManager.getCurrentDerivative( forceCurrent, false, true );
	m_constraintDeriv = m_jacobian * velocityCurrent;
	Eigen::Matrix< double, Eigen::Dynamic, Eigen::Dynamic > jacobianInvJacobianT = m_jacobian * invMassMatrix * m_jacobian.transpose();
	Eigen::Matrix< double, Eigen::Dynamic, 1 > jacobianDerivVelocity = m_jacobianDeriv * velocityCurrent;
	Eigen::Matrix< double, Eigen::Dynamic, 1 > jacobianInvMassForce = m_jacobian * invMassMatrix * forceCurrent;
	Eigen::Matrix< double, Eigen::Dynamic, 1 > b = -jacobianDerivVelocity - jacobianInvMassForce - m_ks*m_constraint - m_kd*m_constraintDeriv;
	if (jacobianInvJacobianT.determinant() != 0)
	{
		m_lagrangeMultipliers = jacobianInvJacobianT.ldlt().solve( b );
	}
	else
	{
		m_lagrangeMultipliers.resize( m_constraintForces.size() );
		m_lagrangeMultipliers.setZero();
	}
}