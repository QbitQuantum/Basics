void MovingPixelsState::setTransparentColor(const app::Color& color)
{
  ASSERT(m_pixelsMovement != NULL);

  Sprite* sprite = m_currentEditor->getSprite();
  ASSERT(sprite != NULL);

  PixelFormat format = sprite->getPixelFormat();
  m_pixelsMovement->setMaskColor(color_utils::color_for_image(color, format));
}