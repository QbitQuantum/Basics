void PenaltyMarkPercept::draw() const
{
  DECLARE_DEBUG_DRAWING("representation:PenaltyMarkPercept:image", "drawingOnImage");
  DECLARE_DEBUG_DRAWING("representation:PenaltyMarkPercept:field", "drawingOnField");

  if(Blackboard::getInstance().exists("FrameInfo"))
  {
    const FrameInfo& frameInfo = static_cast<const FrameInfo&>(Blackboard::getInstance()["FrameInfo"]);
    if(timeLastSeen == frameInfo.time)
    {
      CROSS("representation:PenaltyMarkPercept:image", position.x(), position.y(), 5, 5, Drawings::solidPen, ColorRGBA::blue);
      CROSS("representation:PenaltyMarkPercept:field", positionOnField.x(), positionOnField.y(), 40, 40, Drawings::solidPen, ColorRGBA::blue);
    }
  }
}