void VPLShaderManager::drawBackground(const Sensor *sensor,
		const Transform &projectionTransform, Float scaleFactor) {
	if (m_backgroundProgram == NULL)
		return;

	const Transform &trafo = sensor->getWorldTransform()->eval(0);

	Transform clipToWorld = trafo
		* Transform::scale(Vector(-1, 1, -1)) * projectionTransform.inverse();

	GPUProgram *prog = m_backgroundProgram;
	int tuOffset = 0;
	prog->bind();
	m_backgroundDependencies.bind(prog, m_backgroundDependencies, tuOffset);

	if (sensor->getType() & Sensor::EOrthographicCamera) {
		Vector d = trafo(Vector(0.0f, 0.0f, 1.0f));
		prog->setParameter(m_backgroundParam_camDirection, d);
	} else {
		Point p = trafo(Point(0.0f));
		prog->setParameter(m_backgroundParam_camPosition, p);
	}

	prog->setParameter(m_backgroundParam_emitterScale, scaleFactor);
	prog->setParameter(m_backgroundParam_clipToWorld, clipToWorld);
	m_renderer->blitQuad(false);
	prog->unbind();
	m_backgroundDependencies.unbind();
}