ExtraRfbServers::~ExtraRfbServers()
{
  try {
    shutDown();
  } catch (...) { }
}