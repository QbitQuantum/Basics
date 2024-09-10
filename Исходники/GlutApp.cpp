	void GlutApp::update()
	{
		if (m_translating)
		{
			m_cameraController.moveForward(m_reversing ? m_motionSpeed * -1 : m_motionSpeed);
		}

		m_cameraController.updateCamera();

		const oplo::Matrix4<float>& proj = m_camera.GetProjectionMatrix();
		const oplo::Matrix4<float>& cam = m_camera.GetViewMatrix();

		Matrix4<float> mvp = proj * cam;

		m_uniforms.setUniform("modelview", cam.begin(), 16);
		m_uniforms.setUniform("modelviewProjection", mvp.begin(), 16);

		mvp.invert();
		m_uniforms.setUniform("inverseModelviewProjection", mvp.begin(), 16);


		//elevationPage.beginFrame(camera);
		//cameraController.UpdateCamera();
		float cosLight = cos(m_globalLightDirection.getRadians());
		float sinLight = sin(m_globalLightDirection.getRadians());

		Vec3F lightDir = Vec3F(cosLight, sinLight, 0.15f);
		lightDir.normalize();
		m_uniforms.setUniform("lightDirection", lightDir);

		//float maxTan = camera.GetTangentFOV();
		//const float tangentAxisDivisor = static_cast<float>(std::max(camera.GetViewingWidth(), camera.GetViewingHeight()));

		//maxTan = std::max(maxTan * camera.GetAspect(), maxTan) * 2;

		//Math::AffineMatrix< float > mModelview = camera.GetViewMatrix();
		//Math::AffineMatrix< float > mProjection = camera.GetProjectionMatrix();
		//Math::AffineMatrix< float > mModelviewProjection = mProjection * mModelview;


		//mModelviewProjection.Invert();

		//Engine::staticGet<UniformHandler>().SetUniform("sunDir", vLightDirDowncast[0], vLightDirDowncast[1], vLightDirDowncast[2]);
		//Engine::staticGet<UniformHandler>().SetUniform("cameraPos", camera.GetWorldPosition()[0], camera.GetWorldPosition()[1], camera.GetWorldPosition()[2]);
		//Engine::staticGet<UniformHandler>().SetUniform("maximumFrustumTangentAxis", tangentAxisDivisor * (1.f / (lodAggressiveness * maxTan)));
		//Engine::staticGet<UniformHandler>().SetUniform("inverseScreenWidthHeight", 1.f / camera.GetViewingWidth(), 1.f / camera.GetViewingHeight());
		//Engine::staticGet<UniformHandler>().SetUniform("inverseModelviewProjection", mModelviewProjection.Begin(), 16, true);
		//Engine::staticGet<UniformHandler>().SetUniform("hg", hg_[0], hg_[1], hg_[2]);
		//Engine::staticGet<UniformHandler>().SetUniform("hgHalf", hgHalf_[0], hgHalf_[1], hgHalf_[2]);

	}