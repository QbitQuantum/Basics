void DepthImageSensor::DistanceSensor::updateValue()
{
  // make sure the poses of all movable objects are up to date
  Simulation::simulation->scene->updateTransformations();
  
  OffscreenRenderer& renderer = Simulation::simulation->renderer;

  renderer.makeCurrent(renderWidth, renderHeight);
  glViewport(0, 0, renderWidth, renderHeight);

  // setup image size and angle of view
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixf(projection);
  glMatrixMode(GL_MODELVIEW);
  
  // disable lighting and textures, and use flat shading
  glDisable(GL_LIGHTING);
  glDisable(GL_TEXTURE_2D);
  glPolygonMode(GL_FRONT, GL_FILL);
  glShadeModel(GL_FLAT);

  // setup camera position
  Pose3<> pose = physicalObject->pose;
  pose.conc(offset);
  static const Matrix3x3<> cameraRotation(Vector3<>(0.f, -1.f, 0.f), Vector3<>(0.f, 0.f, 1.f), Vector3<>(-1.f, 0.f, 0.f));
  pose.rotate(cameraRotation);
  pose.rotate(Matrix3x3<>(Vector3<>(0, (depthImageSensor->angleX - renderAngleX) / 2.0f, 0)));
  
  float* val = imageBuffer;
  unsigned int widthLeft = depthImageSensor->imageWidth;
  for(unsigned int i = 0; i < numOfBuffers; ++i)
  {
    float transformation[16];
    OpenGLTools::convertTransformation(pose.invert(), transformation);
    glLoadMatrixf(transformation);

    // disable color rendering
    glColorMask(0, 0, 0, 0);
    
    // draw all objects
    glClear(GL_DEPTH_BUFFER_BIT);
    Simulation::simulation->scene->drawAppearances();

    // enable color rendering again
    glColorMask(1, 1, 1, 1);

    // read frame buffer
    renderer.finishDepthRendering(renderBuffer, renderWidth, renderHeight);

    if(depthImageSensor->projection == perspectiveProjection)
    {
      // convert pixels to points in world and compute the depth (renderBuffer == imageBuffer)
      const float halfP34 = projection[14] * 0.5f;
      const float halfP33m1 = projection[10] * 0.5f - 0.5f;
      for(float* end = val + renderWidth * renderHeight; val < end; ++val)
        *val = halfP34 / (*val + halfP33m1);
    }
    else
    {
      // convert pixels to points in world and compute the distances (renderBuffer != imageBuffer)
      const float fInvSqr = 1.f / (projection[0] * projection[0]);
      const float halfP34 = projection[14] * 0.5f;
      const float halfP33m1 = projection[10] * 0.5f - 0.5f;
      float* const mid = lut[bufferWidth / 2];
      const float factor = 2.0f / float(renderWidth);
      const unsigned int end = std::min(bufferWidth, widthLeft);
      for(unsigned int i = 0; i < end; ++i)
      {
        const float vx = (lut[i] - mid) * factor;
        *val++ = std::min<float>(halfP34 / (*lut[i] + halfP33m1) * sqrt(1.f + vx * vx * fInvSqr), max);
      }
      widthLeft -= end;
      pose.rotate(Matrix3x3<>(Vector3<>(0, -renderAngleX, 0)));
    }
  }
}