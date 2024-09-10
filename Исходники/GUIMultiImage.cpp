bool CGUIMultiImage::CMultiImageJob::DoWork()
{
  // check to see if we have a single image or a folder of images
  CFileItem item(m_path, false);
  item.FillInMimeType();
  if (item.IsPicture() || item.GetMimeType().Left(6).Equals("image/"))
  {
    m_files.push_back(m_path);
  }
  else
  {
    // Load in images from the directory specified
    // m_path is relative (as are all skin paths)
    CStdString realPath = g_TextureManager.GetTexturePath(m_path, true);
    if (realPath.IsEmpty())
      return true;

    URIUtils::AddSlashAtEnd(realPath);
    CFileItemList items;
    CDirectory::GetDirectory(realPath, items, g_advancedSettings.m_pictureExtensions + "|.tbn|.dds", DIR_FLAG_NO_FILE_DIRS | DIR_FLAG_NO_FILE_INFO);
    for (int i=0; i < items.Size(); i++)
    {
      CFileItem* pItem = items[i].get();
      if (pItem && (pItem->IsPicture() || pItem->GetMimeType().Left(6).Equals("image/")))
        m_files.push_back(pItem->GetPath());
    }
  }
  return true;
}