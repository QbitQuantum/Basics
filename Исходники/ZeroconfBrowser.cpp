CZeroconfBrowser::ZeroconfService CZeroconfBrowser::ZeroconfService::fromPath(const CStdString& fcr_path)
{
  if( fcr_path.empty() )
    throw std::runtime_error("CZeroconfBrowser::ZeroconfService::fromPath input string empty!");

  int pos1 = fcr_path.Find('@'); //first @
  int pos2 = fcr_path.Find('@', pos1+1); //second

  if( pos1 == -1 || pos2 == -1 )
    throw std::runtime_error("CZeroconfBrowser::ZeroconfService::fromPath invalid input path");

  return ZeroconfService(
    fcr_path.substr(pos2 + 1, fcr_path.length()), //name
    fcr_path.substr(0, pos1), //type
    fcr_path.substr(pos1 + 1, pos2-(pos1+1)) //domain
    );
}