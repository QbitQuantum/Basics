void RenderDoc::BecomeRemoteServer(const char *listenhost, uint16_t port, volatile bool32 &killReplay)
{
  Network::Socket *sock = Network::CreateServerSocket(listenhost, port, 1);

  if(sock == NULL)
    return;

  bool newlyReady = true;

  std::vector<std::pair<uint32_t, uint32_t> > listenRanges;
  bool allowExecution = true;

  FILE *f = FileIO::fopen(FileIO::GetAppFolderFilename("remoteserver.conf").c_str(), "r");

  while(f && !FileIO::feof(f))
  {
    string line = trim(FileIO::getline(f));

    if(line == "")
      continue;

    // skip comments
    if(line[0] == '#')
      continue;

    if(line.substr(0, sizeof("whitelist") - 1) == "whitelist")
    {
      uint32_t ip = 0, mask = 0;

      // CIDR notation
      bool found = Network::ParseIPRangeCIDR(line.c_str() + sizeof("whitelist"), ip, mask);

      if(found)
      {
        listenRanges.push_back(std::make_pair(ip, mask));
        continue;
      }
      else
      {
        RDCLOG("Couldn't parse IP range from: %s", line.c_str() + sizeof("whitelist"));
      }

      continue;
    }
    else if(line.substr(0, sizeof("noexec") - 1) == "noexec")
    {
      allowExecution = false;

      continue;
    }

    RDCLOG("Malformed line '%s'. See documentation for file format.", line.c_str());
  }

  if(f)
    FileIO::fclose(f);

  if(listenRanges.empty())
  {
    RDCLOG("No whitelist IP ranges configured - using default private IP ranges.");
    RDCLOG(
        "Create a config file remoteserver.conf in ~/.renderdoc or %%APPDATA%%/renderdoc to narrow "
        "this down or accept connections from more ranges.");

    listenRanges.push_back(std::make_pair(Network::MakeIP(10, 0, 0, 0), 0xff000000));
    listenRanges.push_back(std::make_pair(Network::MakeIP(172, 16, 0, 0), 0xfff00000));
    listenRanges.push_back(std::make_pair(Network::MakeIP(192, 168, 0, 0), 0xffff0000));
  }

  RDCLOG("Allowing connections from:");

  for(size_t i = 0; i < listenRanges.size(); i++)
  {
    uint32_t ip = listenRanges[i].first;
    uint32_t mask = listenRanges[i].second;

    RDCLOG("%u.%u.%u.%u / %u.%u.%u.%u", Network::GetIPOctet(ip, 0), Network::GetIPOctet(ip, 1),
           Network::GetIPOctet(ip, 2), Network::GetIPOctet(ip, 3), Network::GetIPOctet(mask, 0),
           Network::GetIPOctet(mask, 1), Network::GetIPOctet(mask, 2), Network::GetIPOctet(mask, 3));
  }

  if(allowExecution)
    RDCLOG("Allowing execution commands");
  else
    RDCLOG("Blocking execution commands");

  while(!killReplay)
  {
    if(newlyReady)
    {
      RDCLOG("Replay host ready for requests.");
      newlyReady = false;
    }

    Network::Socket *client = sock->AcceptClient(false);

    if(client == NULL)
    {
      if(!sock->Connected())
      {
        RDCERR("Error in accept - shutting down server");

        SAFE_DELETE(sock);
        return;
      }

      Threading::Sleep(5);

      continue;
    }

    uint32_t ip = client->GetRemoteIP();

    RDCLOG("Connection received from %u.%u.%u.%u.", Network::GetIPOctet(ip, 0),
           Network::GetIPOctet(ip, 1), Network::GetIPOctet(ip, 2), Network::GetIPOctet(ip, 3));

    bool valid = false;

    for(size_t i = 0; i < listenRanges.size(); i++)
    {
      if(Network::MatchIPMask(ip, listenRanges[i].first, listenRanges[i].second))
      {
        valid = true;
        break;
      }
    }

    if(!valid)
    {
      RDCLOG("Doesn't match any listen range, closing connection.");
      SAFE_DELETE(client);
      continue;
    }

    Serialiser ser("", Serialiser::WRITING, false);

    newlyReady = true;

    map<RDCDriver, string> drivers = RenderDoc::Inst().GetRemoteDrivers();

    uint32_t count = (uint32_t)drivers.size();
    ser.Serialise("", count);

    for(auto it = drivers.begin(); it != drivers.end(); ++it)
    {
      RDCDriver driver = it->first;
      ser.Serialise("", driver);
      ser.Serialise("", (*it).second);
    }

    if(!SendPacket(client, ePacket_RemoteDriverList, ser))
    {
      RDCERR("Network error sending supported driver list");
      SAFE_DELETE(client);
      continue;
    }

    Threading::Sleep(4);

    // don't care about the result, just want to check that the socket hasn't been gracefully shut
    // down
    client->IsRecvDataWaiting();
    if(!client->Connected())
    {
      RDCLOG("Connection closed after sending remote driver list");
      SAFE_DELETE(client);
      continue;
    }

    string cap_file;
    string dummy, dummy2;
    FileIO::GetDefaultFiles("remotecopy", cap_file, dummy, dummy2);

    Serialiser *fileRecv = NULL;

    if(!RecvChunkedFile(client, ePacket_CopyCapture, cap_file.c_str(), fileRecv, NULL))
    {
      FileIO::Delete(cap_file.c_str());

      RDCERR("Network error receiving file");

      SAFE_DELETE(fileRecv);
      SAFE_DELETE(client);
      continue;
    }

    RDCLOG("File received.");

    SAFE_DELETE(fileRecv);

    RDCDriver driverType = RDC_Unknown;
    string driverName = "";
    RenderDoc::Inst().FillInitParams(cap_file.c_str(), driverType, driverName, NULL);

    if(RenderDoc::Inst().HasRemoteDriver(driverType))
    {
      ProgressLoopData data;

      data.sock = client;
      data.killsignal = false;
      data.progress = 0.0f;

      RenderDoc::Inst().SetProgressPtr(&data.progress);

      Threading::ThreadHandle ticker = Threading::CreateThread(ProgressTicker, &data);

      IRemoteDriver *driver = NULL;
      auto status = RenderDoc::Inst().CreateRemoteDriver(driverType, cap_file.c_str(), &driver);

      if(status != eReplayCreate_Success || driver == NULL)
      {
        RDCERR("Failed to create remote driver for driver type %d name %s", driverType,
               driverName.c_str());
        SAFE_DELETE(client);
        continue;
      }

      driver->ReadLogInitialisation();

      RenderDoc::Inst().SetProgressPtr(NULL);

      data.killsignal = true;
      Threading::JoinThread(ticker);
      Threading::CloseThread(ticker);

      FileIO::Delete(cap_file.c_str());

      SendPacket(client, ePacket_LogReady);

      ProxySerialiser *proxy = new ProxySerialiser(client, driver);

      while(client)
      {
        if(!proxy->Tick() || killReplay)
        {
          SAFE_DELETE(client);
        }
      }

      driver->Shutdown();

      RDCLOG("Closing replay connection");

      SAFE_DELETE(proxy);
      SAFE_DELETE(client);
    }
    else
    {
      RDCERR("File needs driver for %s which isn't supported!", driverName.c_str());

      FileIO::Delete(cap_file.c_str());
    }

    SAFE_DELETE(client);
  }

  SAFE_DELETE(sock);
}