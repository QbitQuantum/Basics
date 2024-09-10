void OvercrowdingDemo::update()
{
	// Clear accumulators
	world.startFrame();

    // Find the duration of the last frame in seconds
    float duration = (float)TimingData::get().lastFrameDuration * 0.001f;
    if (duration <= 0.0f) return;

	// Run the simulation
	world.runPhysics(duration);

    Application::update();

	for (unsigned i = 0; i < ParticleCount; ++i)
	{
		Particle& curParticle = particles[i].particle;
		real distFromWorldCenter = curParticle.getPosition().magnitude();

		if (distFromWorldCenter >= real(WorldRadius))
		{
			Vector3 oppositeVelocity = curParticle.getVelocity();
			oppositeVelocity.invert();
			curParticle.setVelocity(oppositeVelocity);
		}
	}
}