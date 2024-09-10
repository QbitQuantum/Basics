void BoundingBoxDrawer::drawSingle(const BoundingBox& bbox) {
	// TODO: optimize!!!!

	auto bmin = bbox.min();
	auto bmax = bbox.max();

	glm::vec3 vertices[BOX_VERTICES] = {
		glm::vec3(bmax.x, bmax.y, bmin.z), glm::vec3(bmin.x, bmax.y, bmin.z), bmax,
		glm::vec3(bmin.x, bmax.y, bmax.z), glm::vec3(bmax.x, bmin.y, bmin.z),
		bmin, glm::vec3(bmin.x, bmin.y, bmax.z), glm::vec3(bmax.x, bmin.y, bmax.z) 
	};

	if (m_state->shader != m_shader.get()) {
		m_shader->use();
		m_state->shader = m_shader.get();
	}

	m_vao.bind();
	m_vbo.updateData(0, sizeof(vertices), vertices);
	glDrawElements(GL_TRIANGLE_STRIP, BOX_INDICES, GL_UNSIGNED_SHORT, 0);
}