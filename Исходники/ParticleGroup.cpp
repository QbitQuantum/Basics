	/*!
	* \brief Applies the controllers
	*
	* \param mapper Mapper containing layout information of each particle
	* \param particleCount Number of particles
	* \param elapsedTime Delta time between the previous frame
	*/
	void ParticleGroup::ApplyControllers(ParticleMapper& mapper, unsigned int particleCount, float elapsedTime)
	{
		m_processing = true;

		// To avoid a lock in case of exception
		CallOnExit onExit([this]()
		{
			m_processing = false;
		});

		for (ParticleController* controller : m_controllers)
			controller->Apply(*this, mapper, 0, particleCount - 1, elapsedTime);

		onExit.CallAndReset();

		// We only kill now the dead particles during the update
		if (m_dyingParticles.size() < m_particleCount)
		{
			// We kill them in reverse order, std::set sorting them via std::greater
			// The reason is simple, as the death of a particle means moving the last particle in the buffer,
			// without this solution, certain particles could avoid death
			for (unsigned int index : m_dyingParticles)
				KillParticle(index);
		}
		else
			KillParticles(); // Every particles are dead, this is way faster

		m_dyingParticles.clear();
	}