void DeferredDirectionalLightsPass::render(IViewer* viewer, World& world, const SceneContext& sceneContext, unsigned int lightMapFrameBuffer, const DeferredInitRenderStage& initStage) {
  GraphicsInterface::beginPerformanceEvent("Directional");
  
  {
    GraphicsInterface::beginPerformanceEvent("Lighting");

    GraphicsInterface::setFrameBuffer(directionalLightFrameBuffer_);

    std::vector<DirectionalLight> directionalLights = sceneContext.directionalLights();
    for (std::vector<DirectionalLight>::iterator light = directionalLights.begin(); light != directionalLights.end(); ++light) {
      directionalLightEffect_->beginDraw();

      directionalLightEffect_->setTexture(GraphicsInterface::depthBufferTexture(), "DepthMap");
      directionalLightEffect_->setTexture(initStage.normalMap(), "NormalMap");
      
      directionalLightEffect_->setUniform(viewer->viewTransform(), "View");
      Matrix4x4 viewProjection = viewer->projection() * viewer->viewTransform();
      directionalLightEffect_->setUniform(viewProjection, "ViewProj");
      directionalLightEffect_->setUniform(viewProjection.inverse(), "ViewProjInv");
      directionalLightEffect_->setUniform(viewer->position(), "ViewPosition");
      directionalLightEffect_->setUniform((*light).direction(), "LightDirection");
      directionalLightEffect_->setUniform((*light).color(), "LightColor");

			directionalLightEffect_->setUniform(GraphicsInterface::halfBackBufferPixel(), "HalfPixel");

      //Matrix4x4 normalMatrix = viewer->viewTransform().mat3x3().inverseTranspose();
      directionalLightEffect_->setUniform(Matrix4x4::IDENTITY.mat3x3(), "NormalMatrix");

			directionalLightEffect_->commitBuffers();
      GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
      directionalLightEffect_->endDraw();
    }

    GraphicsInterface::endPerformanceEvent();
  }

  {
    GraphicsInterface::beginPerformanceEvent("Accumulation");

    GraphicsInterface::setFrameBuffer(lightMapFrameBuffer);
    GraphicsInterface::setBlendState(IGraphicsInterface::ADDITIVE);
    
    accumulationEffect_->beginDraw();
    accumulationEffect_->setTexture(directionalLightRenderTexture_, "LightSourceMap");
    accumulationEffect_->setTexture(initStage.colorMap(), "ColorMap");
		accumulationEffect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(quadVbo_, Geometry::SCREEN_PLANE_VERTEX_COUNT, Geometry::SCREEN_PLANE_VERTEX_FORMAT);
    accumulationEffect_->endDraw();
    GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);

    GraphicsInterface::endPerformanceEvent();
  }

  GraphicsInterface::endPerformanceEvent();
}