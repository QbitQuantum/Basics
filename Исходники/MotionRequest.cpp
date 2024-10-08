void MotionRequest::draw() const
{
  DECLARE_DEBUG_DRAWING("representation:MotionRequest", "drawingOnField"); // drawing of a request walk vector
  if(motion == walk)
  {
    switch(walkRequest.mode)
    {
    case WalkRequest::targetMode:
    {
      LINE("representation:MotionRequest", 0, 0, walkRequest.target.translation.x, walkRequest.target.translation.y, 0, Drawings::ps_solid, ColorRGBA(0xcd, 0, 0));
      CROSS("representation:MotionRequest", walkRequest.target.translation.x, walkRequest.target.translation.y, 50, 0, Drawings::ps_solid, ColorRGBA(0xcd, 0, 0));
      Vector2<> rotation(500.f, 0.f);
      rotation.rotate(walkRequest.target.rotation);
      ARROW("representation:MotionRequest", walkRequest.target.translation.x, walkRequest.target.translation.y, walkRequest.target.translation.x + rotation.x, walkRequest.target.translation.y + rotation.y, 0, Drawings::ps_solid, ColorRGBA(0xcd, 0, 0, 127));
    }
    break;
    case WalkRequest::speedMode:
    case WalkRequest::percentageSpeedMode:
    {
      Vector2<> translation = walkRequest.mode == WalkRequest::speedMode ? walkRequest.speed.translation * 10.f : walkRequest.speed.translation * 1000.f;
      ARROW("representation:MotionRequest", 0, 0, translation.x, translation.y, 0, Drawings::ps_solid, ColorRGBA(0xcd, 0, 0));
      if(walkRequest.target.rotation != 0.0f)
      {
        translation.x = translation.abs();
        translation.y = 0;
        translation.rotate(walkRequest.speed.rotation);
        ARROW("representation:MotionRequest", 0, 0,  translation.x, translation.y, 0, Drawings::ps_solid, ColorRGBA(0xcd, 0, 0, 127));
      }
    }
    break;
    default:
      break;
    }
  }
}