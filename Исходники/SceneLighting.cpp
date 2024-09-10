void CameraFocusSceneLighting::modifyGLState(GLState* glState, const G3MRenderContext* rc) {

  const Camera* cam = rc->getCurrentCamera();
  const Vector3D camDir = cam->getViewDirection();
  const Vector3D up = cam->getUp();
  if (_cameraDirX == camDir._x && _cameraDirY == camDir._y && _cameraDirZ == camDir._z &&
      _upX == up._x && _upY == up._y && _upZ == up._z) {
    return;
  }

  const Vector3D cameraVector = camDir.times(-1);

  //Light slightly different of camera position
  const Vector3D rotationLightDirAxis = up.cross(cameraVector);
  const Vector3D lightDir = cameraVector.rotateAroundAxis(rotationLightDirAxis, Angle::fromDegrees(45.0));

  DirectionLightGLFeature* f = (DirectionLightGLFeature*) glState->getGLFeature(GLF_DIRECTION_LIGTH);
  if (f == NULL) {
    glState->clearGLFeatureGroup(LIGHTING_GROUP);
    glState->addGLFeature(new DirectionLightGLFeature(lightDir,
                                                      _diffuseColor,
                                                      _ambientColor),
                          false);
  }
  else{
    f->setLightDirection(lightDir);
  }

  //ADD MESH
  if (_meshRenderer != NULL) {
    Vector3D lastCamDir(_cameraDirX, _cameraDirY, _cameraDirZ);

    if (lastCamDir.angleBetween(lightDir)._degrees > 10) {

      FloatBufferBuilderFromCartesian3D* vertices = FloatBufferBuilderFromCartesian3D::builderWithFirstVertexAsCenter();
      vertices->add(cam->getCartesianPosition());
      vertices->add(cam->getCartesianPosition().add(lightDir.times(1000)) );

      DirectMesh* mesh = new DirectMesh(GLPrimitive::lines(),
                                        true,
                                        vertices->getCenter(),
                                        vertices->create(),
                                        (float)3.0,
                                        (float)1.0,
                                        new Color(Color::red()));
      _meshRenderer->addMesh(mesh);
    }
  }

  //SAVING STATE
  _cameraDirX = camDir._x;
  _cameraDirY = camDir._y;
  _cameraDirZ = camDir._z;
  
  _upX = up._x;
  _upY = up._y;
  _upZ = up._z;
  
}