void CameraDoubleTapHandler::onDown(const G3MEventContext *eventContext,
                                    const TouchEvent& touchEvent,
                                    CameraContext *cameraContext) {
  // compute globe point where user tapped
  const Vector2I pixel = touchEvent.getTouch(0)->getPos();
  Camera* camera = cameraContext->getNextCamera();
  const Vector3D initialPoint = camera->pixel2PlanetPoint(pixel);
  if (initialPoint.isNan()) return;
  
  // compute central point of view
  const Vector3D centerPoint = camera->getXYZCenterOfView();
  
  // compute drag parameters
  const Vector3D axis = initialPoint.cross(centerPoint);
  const Angle angle   = Angle::fromRadians(- IMathUtils::instance()->asin(axis.length()/initialPoint.length()/centerPoint.length()));
  
  // compute zoom factor
  const double height   = camera->getGeodeticPosition()._height;
  const double distance = height * 0.6;
  
  // create effect
  Effect* effect = new DoubleTapEffect(TimeInterval::fromSeconds(0.75), axis, angle, distance);
  
  EffectTarget* target = cameraContext->getNextCamera()->getEffectTarget();
  eventContext->getEffectsScheduler()->startEffect(effect, target);
}