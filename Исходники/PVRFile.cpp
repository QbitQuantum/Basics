bool CPVRFile::Rename(const CURL& url, const CURL& urlnew)
{
  CStdString path(url.GetFileName());
  CStdString newname(urlnew.GetFileName());

  size_t found = newname.find_last_of("/");
  if (found != CStdString::npos)
    newname = newname.substr(found+1);

  if (path.Left(11) == "recordings/" && path[path.size()-1] != '/')
  {
    CStdString strURL = url.Get();
    CPVRRecording *tag = CPVRManager::GetRecordings()->GetByPath(strURL);
    if (tag)
      return tag->Rename(newname);
  }
  return false;
}