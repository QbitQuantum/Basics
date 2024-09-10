bool CHDDirectory::GetSmartFolder(const CStdString& strPath, CFileItemList &items)
{
#ifdef __APPLE__
  CStdString strTruePath = strPath;

  // If there's a trailing /, remove it.
  if (CUtil::HasSlashAtEnd(strTruePath))
    strTruePath = strTruePath.Left(strTruePath.length()-1);

  // Execute the query.
  Cocoa_GetSmartFolderResults(strTruePath, HandleSearchResult, this, &items);
#endif

  return true;
}