bool CFileOperationJob::DoProcessFolder(FileAction action, const std::string& strPath, const std::string& strDestFile, FileOperationList &fileOperations, double &totalTime)
{
  // check whether this folder is a filedirectory - if so, we don't process it's contents
  CFileItem item(strPath, false);
  IFileDirectory *file = CFileDirectoryFactory::Create(item.GetURL(), &item);
  if (file)
  {
    delete file;
    return true;
  }

  CFileItemList items;
  CDirectory::GetDirectory(strPath, items, "", DIR_FLAG_NO_FILE_DIRS | DIR_FLAG_GET_HIDDEN);
  for (int i = 0; i < items.Size(); i++)
  {
    CFileItemPtr pItem = items[i];
    pItem->Select(true);
  }

  if (!DoProcess(action, items, strDestFile, fileOperations, totalTime))
  {
    CLog::Log(LOGERROR,"FileManager: error while processing folder: %s", strPath.c_str());
    return false;
  }

  if (action == ActionMove)
  {
    fileOperations.push_back(CFileOperation(ActionDeleteFolder, strPath, "", 1));
    totalTime += 1.0;
  }

  return true;
}