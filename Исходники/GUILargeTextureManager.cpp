// if available, increment reference count, and return the image.
// else, add to the queue list if appropriate.
bool CGUILargeTextureManager::GetImage(const CStdString &path, CTextureArray &texture, bool firstRequest)
{
  // note: max size to load images: 2048x1024? (8MB)
  CSingleLock lock(m_listSection);
  for (listIterator it = m_allocated.begin(); it != m_allocated.end(); ++it)
  {
    CLargeTexture *image = *it;
    if (image->GetPath() == path)
    {
      if (firstRequest)
        image->AddRef();
      texture = image->GetTexture();
      return texture.size() > 0;
    }
  }

  if (firstRequest)
    QueueImage(path);

  return true;
}