bool SessionInitializer::setUpSSL(qi::SessionPtr session, const std::string &serviceDirectoryUrl)
{
  if(session->connect(serviceDirectoryUrl).wait(1000) != qi::FutureState_FinishedWithValue)
    return false;

  if (_listen == true)
  {
    session->setIdentity("../tests/server.key", "../tests/server.crt");
    session->listen("tcps://0.0.0.0:0");
  }

  return true;
}