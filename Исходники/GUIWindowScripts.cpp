bool CGUIWindowScripts::GetDirectory(const CStdString& strDirectory, CFileItemList& items)
{
  if (!CGUIMediaWindow::GetDirectory(strDirectory,items))
    return false;

  // flatten any folders
  for (int i = 0; i < items.Size(); i++)
  {
    CFileItemPtr item = items[i];
    if (item->m_bIsFolder && !item->IsParentFolder() && !item->m_bIsShareOrDrive && !item->GetLabel().Left(1).Equals("."))
    { // folder item - let's check for a default.py file, and flatten if we have one
      CStdString defaultPY;
      CUtil::AddFileToFolder(item->m_strPath, "default.py", defaultPY);
      if (!CFile::Exists(defaultPY)) {
         CUtil::AddFileToFolder(item->m_strPath, "Default.py", defaultPY);
         if (!CFile::Exists(defaultPY)) {
            CUtil::AddFileToFolder(item->m_strPath, "DEFAULT.PY", defaultPY);
         }
      }

      if (CFile::Exists(defaultPY))
      { // yes, format the item up
        item->m_strPath = defaultPY;
        item->m_bIsFolder = false;
        item->FillInDefaultIcon();
        item->SetLabelPreformated(true);
      }
    }
    if (item->GetLabel().Equals("autoexec.py") || (item->GetLabel().Left(1).Equals(".") && !item->IsParentFolder()))
    {
      items.Remove(i);
      i--;
    }
  }

  items.SetProgramThumbs();

  return true;
}