//*********************************************************************************************
CStdString CWINFileSMB::GetLocal(const CURI &url)
{
  CStdString path( url.GetFileName() );

  if( url.GetProtocol().Equals("smb", false) )
  {
    CStdString host( url.GetHostName() );

    if(host.size() > 0)
    {
      path = "//" + host + "/" + path;
    }
  }

  path.Replace('/', '\\');

  return path;
}