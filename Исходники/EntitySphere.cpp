	void EntitySphere::render()
	{
		XMMATRIX translation = XMMatrixTranslationFromVector(m_position);
		XMMATRIX orientation = XMMatrixRotationRollPitchYaw(m_orientation.x, m_orientation.y, m_orientation.z);
		XMMATRIX scaling = XMMatrixScaling(m_diameter, m_diameter, m_diameter);

		XMMATRIX viewMatrix, projectionMatrix, transform;
		transform = scaling * orientation * translation;

		GRAPHICS->getCamera()->GetViewMatrix(viewMatrix);
		GRAPHICS->getDirectXWrapper()->getProjectionMatrix(projectionMatrix);
	
		m_gfx->render(transform, viewMatrix, projectionMatrix, m_color, m_texture, m_wireframe);
	}