void StringElement::buildParticlesAndSprings() {
	Vector2d xAxis = getEndPosition() - getStartPosition();
	double length = xAxis.norm();
	int requiredMasses = static_cast<int>(ceil(length / stdMaxMassDistance) + 1.0);
	double massDistance = length / requiredMasses;

	xAxis.normalize();

	for (int i = 0; i < requiredMasses; i++) {
		Vector2d massPosition = getStartPosition() + (xAxis * (i * massDistance));
		particles.push_back(createParticle(stdMassValue, stdMassRadius, massPosition));
	}

	for (int i = 0; i < requiredMasses - 1; i++) {
		springs.push_back(new Spring(*particles[i], *particles[i + 1], stdK));
	}

	if (getFromConnectionPoint().isConnected()) {
		ConnectionPoint::particle_list connectionParticles = getFromConnectionPoint().getConnectionParticles();
		for (ConnectionPoint::particle_list::iterator it = connectionParticles.begin(); it != connectionParticles.end(); ++it) {
			springs.push_back(new Spring(*particles[0], **it, stdK));
		}
	}

	if (getToConnectionPoint().isConnected()) {
		ConnectionPoint::particle_list connectionParticles = getToConnectionPoint().getConnectionParticles();
		for (ConnectionPoint::particle_list::iterator it = connectionParticles.begin(); it != connectionParticles.end(); ++it) {
			springs.push_back(new Spring(*particles[particles.size() - 1], **it, stdK));
		}
	}

}