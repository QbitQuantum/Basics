void RotateGizmoRing::render(IViewer* viewer) const {
  GraphicsInterface::beginPerformanceEvent("Ring");

  GraphicsInterface::resetRenderTarget(true);
  GraphicsInterface::setViewport(GraphicsInterface::backBufferSize());
  GraphicsInterface::setBlendState(IGraphicsInterface::NOBLEND);
  GraphicsInterface::setRenderState(CULL_MODE_NONE, true);

  if (drawBounds_)
  {
    effect_->beginDraw();

    BoundingBox bounds = boundingBox();

    Vector4 scale(bounds.max.x - bounds.min.x, bounds.max.y - bounds.min.y, bounds.max.z - bounds.min.z, 2.0f);
    scale /= 2.0f;

    Vector4 translation(bounds.max.x + bounds.min.x, bounds.max.y + bounds.min.y, bounds.max.z + bounds.min.z, 2.0f);
    translation /= 2.0f;

    Matrix4x4 model = localToWorld() * Matrix4x4::translation(translation) * Matrix4x4::scale(scale);
    Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * model * Matrix4x4::scale(1.0001f);

    effect_->setUniform(modelViewProjection, "ModelViewProj");
    effect_->setUniform(ringColor_, "Color");

    effect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(Geometry::UNIT_CUBE_VERTEX_BUFFER, Geometry::UNIT_CUBE_VERTEX_COUNT, Geometry::UNIT_CUBE_VERTEX_FORMAT);
    effect_->endDraw();
  }

  // ring
  { 
    effect_->beginDraw();

    Color3 color = ringColor_;

    if (isHighlighted_) {
      color = Color3::YELLOW;
    }

    effect_->setUniform(color, "Color");

    Matrix4x4 modelViewProjection = viewer->projection() * viewer->viewTransform() * localToWorld();
    effect_->setUniform(modelViewProjection, "ModelViewProj");
    
    Matrix4x4 model = localToWorld();
    effect_->setUniform(model, "Model");

    effect_->commitBuffers();
    GraphicsInterface::drawVertexBuffer(Geometry::UNIT_CIRCLE_VERTEX_BUFFER, Geometry::UNIT_CIRCLE_VERTEX_COUNT, Geometry::UNIT_CIRCLE_VERTEX_FORMAT);
    effect_->endDraw();
  }

  GraphicsInterface::endPerformanceEvent();
}