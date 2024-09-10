void ShadowDemo::Render(Matrix worldMatrix, Matrix viewMatrix, Matrix projectionMatrix)
{
	float posX = 0.0f;
	float posY = 2.0f;
	float posZ = -10.0f;

	float rotX = 0.0f;
	float rotY = 0.0f;
	float rotZ = 0.0f;


	Matrix translateMatrix;
	Matrix lightViewMatrix, lightProjectionMatrix;

	// Generate the light view matrix based on the light's position.
	m_Light.GenerateViewMatrix();
	// Get the light's view and projection matrices from the light object.
	m_Light.GetViewMatrix(lightViewMatrix);
	m_Light.GetProjectionMatrix(lightProjectionMatrix);


	// Setup the translation matrix for the cube model.
	m_CubeModel->GetPosition(posX, posY, posZ);
	worldMatrix.Translation(Vector3(posX, posY, posZ));
	m_CubeModel->SetGPUBuffers();
	g_objShaders.BaseShadowShader()->SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_CubeModel->GetTexture(), DX11RTTexturePtr->GetRTView());
	g_objShaders.BaseShadowShader()->SetLightBuffer(m_Light.GetPosition(), m_Light.GetAmbientColor(), m_Light.GetDiffuseColor());
	g_objShaders.BaseShadowShader()->RenderShader();

	g_objShaders.BaseShadowShader()->Render(m_CubeModel->GetIndexCount());


	m_SphereModel->GetPosition(posX, posY, posZ);
	worldMatrix.Translation(Vector3(posX, posY, posZ));
	m_SphereModel->SetGPUBuffers();
	g_objShaders.BaseShadowShader()->SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_SphereModel->GetTexture(), DX11RTTexturePtr->GetRTView());
	g_objShaders.BaseShadowShader()->SetLightBuffer(m_Light.GetPosition(), m_Light.GetAmbientColor(), m_Light.GetDiffuseColor());
	g_objShaders.BaseShadowShader()->RenderShader();
	g_objShaders.BaseShadowShader()->Render(m_SphereModel->GetIndexCount());


	m_GroundModel->GetPosition(posX, posY, posZ);
	worldMatrix.Translation(Vector3(posX, posY, posZ));
	m_GroundModel->SetGPUBuffers();
	g_objShaders.BaseShadowShader()->SetShaderParameters(worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_GroundModel->GetTexture(), DX11RTTexturePtr->GetRTView());
	g_objShaders.BaseShadowShader()->SetLightBuffer(m_Light.GetPosition(), m_Light.GetAmbientColor(), m_Light.GetDiffuseColor());
	g_objShaders.BaseShadowShader()->RenderShader();
	g_objShaders.BaseShadowShader()->Render(m_GroundModel->GetIndexCount());
}