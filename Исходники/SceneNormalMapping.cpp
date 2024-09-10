void SceneNormalMapping::update(double delta)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	m_program->use();

	m_sceneCam->update();

	//m_sceneLight->rotate(200 * delta, vec3(.5, 1, -1));
	m_program->setUniform("Light.lightPos_CAM",
		(m_sceneCam->getViewMatrix() * m_sceneLight->getWorldTransform()) * m_sceneLight->getPosition());

	{
		SceneObject* obj = m_sceneObjects.at(0);

		//obj->rotate(75 * delta, vec3(.75, .5, -1));
		//obj->rotate(75 * delta, vec3(0, 1, 0));
		obj->update(delta);

		mat4 mvp, mv;
		mat3 normal;
		mv = m_sceneCam->getViewMatrix() * obj->getWorldTransform();
		mvp = m_sceneCam->getMVP(obj->getWorldTransform());

		normal = mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]));

		m_program->setUniform("MODELVIEW", mv);
		m_program->setUniform("MVP", mvp);
		m_program->setUniform("NORMAL", normal);
		obj->getMesh()->uploadMaterialProperties(m_program);

		obj->render();
	}
}