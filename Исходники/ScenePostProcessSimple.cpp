void ScenePostProcessSimple::renderScene(double delta)
{
	m_shadingProg->use();

	glClearColor(.5f, .5f, .5f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	m_sceneCam->update();

	m_shadingProg->setUniform("Light.lightPos_CAM",
		(m_sceneCam->getViewMatrix() * m_light->getWorldTransform()) * m_light->getPosition());

	// Render plane
	{
		m_shadingProg->setUniform("MainTex", 0);
		SceneObject* obj = m_sceneObjects[1];
		obj->update(delta);

		mat4 mvp, mv;
		mat3 normal;
		mv = m_sceneCam->getViewMatrix() * obj->getWorldTransform();
		mvp = m_sceneCam->getMVP(obj->getWorldTransform());

		normal = mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]));

		m_shadingProg->setUniform("MODELVIEW", mv);
		m_shadingProg->setUniform("MVP", mvp);
		m_shadingProg->setUniform("NORMAL", normal);
		obj->getMesh()->uploadMaterialProperties(m_shadingProg);

		obj->render();
	}

	// Render box
	{
		m_shadingProg->setUniform("MainTex", 1);
		SceneObject* obj = m_sceneObjects[0];
		obj->rotate(25 * delta, vec3(0, 1, 0));
		obj->update(delta);

		mat4 mvp, mv;
		mat3 normal;
		mv = m_sceneCam->getViewMatrix() * obj->getWorldTransform();
		mvp = m_sceneCam->getMVP(obj->getWorldTransform());

		normal = mat3(vec3(mv[0]), vec3(mv[1]), vec3(mv[2]));

		m_shadingProg->setUniform("MODELVIEW", mv);
		m_shadingProg->setUniform("MVP", mvp);
		m_shadingProg->setUniform("NORMAL", normal);
		obj->getMesh()->uploadMaterialProperties(m_shadingProg);

		obj->render();
	}
}