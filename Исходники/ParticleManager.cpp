//TODO msati: Optimize this portion
void ParticleManager::getInvMassMatrix( Eigen::Matrix< double, Eigen::Dynamic, Eigen::Dynamic >& invMassMatrix )
{
	invMassMatrix.resize( m_particles.size() * 3, m_particles.size() * 3 );
	invMassMatrix.setZero();
	for (int i = 0; i < m_particles.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			invMassMatrix.row(3*i+j).array()[3*i+j] = 1/(m_particles[i]->mMass);
		}
	}
}