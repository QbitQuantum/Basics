string GetHomeFolderFilename()
{
  PWSTR docsPath;
  SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_SIMPLE_IDLIST | KF_FLAG_DONT_UNEXPAND, NULL,
                       &docsPath);
  wstring documents = docsPath;
  CoTaskMemFree(docsPath);

  if(documents[documents.size() - 1] == '/' || documents[documents.size() - 1] == '\\')
    documents.pop_back();

  return StringFormat::Wide2UTF8(documents);
}