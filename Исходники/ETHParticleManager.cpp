bool ETHParticleManager::UpdateParticleSystem(
	const Vector2& v2Pos,
	const Vector3& v3Pos,
	const float angle,
	const unsigned long lastFrameElapsedTime)
{
	bool anythingDrawn = false;
	const unsigned long cappedLastFrameElapsedTime = Min(lastFrameElapsedTime, static_cast<unsigned long>(250));
	const float frameSpeed = static_cast<float>((static_cast<double>(cappedLastFrameElapsedTime) / 1000.0) * 60.0);

	Matrix4x4 rot = RotateZ(DegreeToRadian(angle));
	m_nActiveParticles = 0;
	for (int t = 0; t < m_system.nParticles; t++)
	{
		PARTICLE& particle = m_particles[t];

		if (m_system.repeat > 0)
			if (particle.repeat >= m_system.repeat)
				continue;

		// check how many particles are active
		if (particle.size > 0.0f && particle.released)
		{
			if (!Killed() || (Killed() && particle.elapsed < particle.lifeTime))
				m_nActiveParticles++;
		}

		anythingDrawn = true;

		particle.elapsed += lastFrameElapsedTime;

		if (!particle.released)
		{
			// if we shouldn't release all particles at the same time, check if it's time to release this particle
			const float releaseTime = 
				((m_system.lifeTime + m_system.randomizeLifeTime) * (static_cast<float>(particle.id) / static_cast<float>(m_system.nParticles)));

			if (particle.elapsed > releaseTime || m_system.allAtOnce)
			{
				particle.elapsed = 0.0f;
				particle.released = true;
				PositionParticle(t, v2Pos, angle, rot, v3Pos);
			}
		}

		if (particle.released)
		{
			particle.dir += (m_system.gravityVector * frameSpeed);
			particle.pos += (particle.dir * frameSpeed);
			particle.angle += (particle.angleDir * frameSpeed);
			particle.size  += (m_system.growth * frameSpeed);
			const float w = particle.elapsed / particle.lifeTime;
			particle.color = m_system.color0 + (m_system.color1 - m_system.color0) * w;

			// update particle animation if there is any
			if (m_system.spriteCut.x > 1 || m_system.spriteCut.y > 1)
			{
				if (m_system.animationMode == ETHParticleSystem::PLAY_ANIMATION)
				{
					particle.currentFrame = static_cast<unsigned int>(
						Min(static_cast<int>(static_cast<float>(m_system.GetNumFrames()) * w),
							m_system.GetNumFrames() - 1));
				}
			}

			particle.size = Min(particle.size, m_system.maxSize);
			particle.size = Max(particle.size, m_system.minSize);

			if (particle.elapsed > particle.lifeTime)
			{
				particle.repeat++;
				if (!Killed())
					ResetParticle(t, v2Pos, v3Pos, angle, rot);
			}
		}
	}
	m_finished = !anythingDrawn;

	// manages the sound
	HandleSoundPlayback(v2Pos, frameSpeed);

	return true;
}