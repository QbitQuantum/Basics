void DeferredSpotLightsPass::renderLight(SpotLight* light, IEffect* lightEffect, IViewer* viewer, unsigned int normalMap) {
	GraphicsInterface::beginPerformanceEvent("Lighting");

	light->update();

	GraphicsInterface::setFrameBuffer(spotLightFrameBuffer_);
	GraphicsInterface::clearActiveColorBuffers(Color4::CORNFLOWERBLUE);

	lightEffect->beginDraw();
  
	GraphicsInterface::setRenderState(CULL_MODE_BACK);

	Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
	lightEffect->setUniform(viewer->viewTransform(), "View");
	lightEffect->setUniform(viewProjection, "ViewProj");
	lightEffect->setUniform(viewProjection.inverse(), "ViewProjInv");

	lightEffect->setUniform(viewer->projection().inverse(), "ProjInv");

	lightEffect->setUniform(viewer->position(), "ViewerPosition");

	Matrix4x4 worldViewProj = viewer->projection() * viewer->viewTransform() * light->transform();
	lightEffect->setUniform(worldViewProj, "WorldViewProj");

	Matrix4x4 worldView = viewer->viewTransform() * light->transform();
	lightEffect->setUniform(worldView, "WorldView");

	Matrix3x3 normalMatrix = viewer->viewTransform().inverse().transpose().mat3x3(); // strips out the translation;
	lightEffect->setUniform(normalMatrix, "NormalMatrix");

	Matrix4x4 lightViewProj = light->projection() * light->viewTransform();
	lightEffect->setUniform(lightViewProj, "LightViewProj");
	lightEffect->setUniform(lightViewProj.inverse(), "LightViewProjRaw");

	float lightDistance = light->direction().length();
	float lightDistanceSquared = lightDistance * lightDistance;
	lightEffect->setUniform(1.0f / lightDistanceSquared, "LightDistance");

	lightEffect->setUniform(light->direction().inverse().normalize(), "DirectionToLight");

	lightEffect->setUniform(light->position(), "LightPosition");
	lightEffect->setUniform(light->direction().normalize(), "LightDirection");
	lightEffect->setUniform(light->color(), "LightColor");

	lightEffect->setUniform(light->outerAngle(), "LightOuterAngle");
	lightEffect->setUniform(light->innerAngle(), "LightInnerAngle");

	lightEffect->setUniform(GraphicsInterface::halfBackBufferPixel(), "HalfPixel");

	unsigned int depthBufferId = GraphicsInterface::depthBufferTexture();
	lightEffect->setTexture(depthBufferId, "DepthMap");

	lightEffect->setTexture(normalMap, "NormalMap");

	if (light->castsShadows()) {
		CSize shadowMapResolution = light->shadowMapResolution();
		Vector2 shadowMapSize(1.0f/shadowMapResolution.width, 1.0f/shadowMapResolution.height);
		lightEffect->setUniform(shadowMapSize, "ShadowMapSize");
		lightEffect->setTexture(light->shadowMapTexture(), "ShadowMap");


    lightEffect->setUniform(light->lightBias(), "LightBias");
    lightEffect->setUniform(light->lightBleed(), "LightBleed");
    lightEffect->setUniform(light->shadowBias(), "ShadowBias");
	}

	//GraphicsInterface::setBlendState(IGraphicsInterface::ALPHA);

	lightEffect->commitBuffers();
	GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
	lightEffect->endDraw();

	GraphicsInterface::endPerformanceEvent();
}