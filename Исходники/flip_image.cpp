void FlipImage::revert(ObjectsContainer* objects, UndoersCollector* redoers)
{
  Image* image = objects->getObjectT<Image>(m_imageId);
  raster::algorithm::FlipType flipType = static_cast<raster::algorithm::FlipType>(m_flipType);
  gfx::Rect bounds(gfx::Point(m_x, m_y), gfx::Size(m_w, m_h));

  if (image->getPixelFormat() != m_format)
    throw UndoException("Image type does not match");

  redoers->pushUndoer(new FlipImage(objects, image, bounds, flipType));

  raster::algorithm::flip_image(image, bounds, flipType);
}