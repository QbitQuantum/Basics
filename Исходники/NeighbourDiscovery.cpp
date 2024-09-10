void NeighbourDiscovery::receiveBeacons() {
  // Get node configuration
  Logger::getInstance()->setThreadName(std::this_thread::get_id(),
                                       "Beacon Receiver");
  LOG(15) << "Starting receiver beacon thread";
  std::string nodeId = m_config.getNodeId();
  std::string nodeAddress = m_config.getNodeAddress();
  uint16_t discoveryPort = m_config.getDiscoveryPort();
  std::string discoveryAddress = m_config.getDiscoveryAddress();
  bool testMode = m_config.getNeighbourTestMode();
#ifndef LEPTON
  // Generate this node address information.
  LOG(65) << "Starting socket into " << discoveryAddress << ":"
                                                         << discoveryPort;
  // Create the socket.
  Socket s = Socket(false);
  if (!s) {
    // Stop the application
    LOG(1) << "Cannot create socket into receiveBeacons thread reason: "
        << s.getLastError();
    g_stop = true;
  } else {
    if (!s.setReuseAddress()) {
      // Stop the application
      LOG(1) << "Cannot set flag REUSEADDR to socket, reason: "
          << s.getLastError();
      g_stop = true;
    } else {
      // Bind the socket.
      if (!s.bind(discoveryAddress, discoveryPort)) {
        // Stop the application
        LOG(1) << "Cannot bind the socket to " << discoveryAddress << ":"
            << discoveryPort << " reason: " << s.getLastError();
        g_stop = true;
      } else {
        // Join the multicast group.
        if (!s.joinMulticastGroup(nodeAddress)) {
          // Stop the application
          LOG(1) << "Cannot join the multicast group, reason: "
              << s.getLastError();
          g_stop = true;
        } else {
          // Add a timeout to the recv socket
          s.setRcvTimeOut(m_config.getSocketTimeout());
#endif
          g_startedThread++;
          while (!g_stop.load()) {
            uint32_t beaconLength = 65507;
            std::string buffer;
            StringWithSize sws = StringWithSize(buffer, beaconLength);
            if (s.canRead(m_config.getSocketTimeout())) {
              s >> sws;
              // Create a thread to add the new neighbour and let this
              // receiving more beacons
              Beacon b = Beacon(buffer);
              if (b.getNodeId() != nodeId || testMode) {
                LOG(21) << "Received beacon from " << b.getNodeId()
                    << " " << b.getNodeAddress() << ":" << b.getNodePort();
                std::thread([b, this]() {
                  m_neighbourTable->update(std::make_shared<Neighbour>(
                          b.getNodeId(),
                          b.getNodeAddress(),
                          b.getNodePort(),
                          b.getEndpoints()));
                }).detach();
              }
            }
          }

          // Leave from the multicast group
          if (false /*!s.leaveMulticastGroup()*/) {
            LOG(4) << "Cannot leave the multicast group, reason: "
                << s.getLastError();
          }
#ifndef LEPTON
        }
      }
    }
#endif
    s.close();
#ifndef LEPTON
  }