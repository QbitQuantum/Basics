void ImageArea::revert(ObjectsContainer* objects, UndoersCollector* redoers)
{
  Image* image = objects->getObjectT<Image>(m_imageId);

  if (image->getPixelFormat() != m_format)
    throw UndoException("Image type does not match");

  // Backup the current image portion
  redoers->pushUndoer(new ImageArea(objects, image, m_x, m_y, m_w, m_h));

  // Restore the old image portion
  for (int v=0; v<m_h; ++v)
    memcpy(image_address(image, m_x, m_y+v), &m_data[m_lineSize*v], m_lineSize);
}