int Slave::connect()
{
   // join the server
   SSLTransport::init();

   string cert = m_strBase + "/conf/master_node.cert";

   // calculate total available disk size
   struct statfs slavefs;
   // <slr>
   statfs(m_SysConfig.m_strHomeDir.c_str(), &slavefs);
   int64_t availdisk = (int64_t)slavefs.f_bfree * slavefs.f_bsize;

   m_iSlaveID = -1;

   m_pLocalFile->serialize("/", m_strHomeDir + ".tmp/metadata.dat");

   set<Address, AddrComp> masters;
   Address m;
   m.m_strIP = m_strMasterIP;
   m.m_iPort = m_iMasterPort;
   masters.insert(m);
   bool first = true;

   while (!masters.empty())
   {
      string mip = masters.begin()->m_strIP;
      int mport = masters.begin()->m_iPort;
      masters.erase(masters.begin());

      SSLTransport secconn;
      secconn.initClientCTX(cert.c_str());
      secconn.open(NULL, 0);
      if (secconn.connect(mip.c_str(), mport) < 0)
      {
         cerr << "unable to set up secure channel to the master.\n";
         return -1;
      }

      if (first)
      {
         secconn.getLocalIP(m_strLocalHost);

         // init data exchange channel
         m_iDataPort = 0;
         if (m_DataChn.init(m_strLocalHost, m_iDataPort) < 0)
         {
            cerr << "unable to create data channel.\n";
            secconn.close();
            return -1;
         }
      }

      int32_t cmd = 1;
      secconn.send((char*)&cmd, 4);

      int32_t size = m_strHomeDir.length() + 1;
      secconn.send((char*)&size, 4);
      secconn.send(m_strHomeDir.c_str(), size);

      int32_t res = -1;
      secconn.recv((char*)&res, 4);
      if (res < 0)
      {
         cerr << "slave join rejected. code: " << res << endl;
         return res;
      }

      secconn.send((char*)&m_iLocalPort, 4);
      secconn.send((char*)&m_iDataPort, 4);
      secconn.send((char*)&(availdisk), 8);
      secconn.send((char*)&(m_iSlaveID), 4);

      if (first)
         m_iSlaveID = res;

      struct stat s;
      stat((m_strHomeDir + ".tmp/metadata.dat").c_str(), &s);
      size = s.st_size;
      secconn.send((char*)&size, 4);
      secconn.sendfile((m_strHomeDir + ".tmp/metadata.dat").c_str(), 0, size);

      if (!first)
      {
         secconn.close();
         continue;
      }

      // move out-of-date files to the ".attic" directory
      size = 0;
      secconn.recv((char*)&size, 4);

      if (size > 0)
      {
         secconn.recvfile((m_strHomeDir + ".tmp/metadata.left.dat").c_str(), 0, size);

         Metadata* attic = NULL;
         if (m_SysConfig.m_MetaType == DISK)
            attic = new Index2;
         else
            attic = new Index;
         attic->init(m_strHomeDir + ".tmp/metadata.left");
         attic->deserialize("/", m_strHomeDir + ".tmp/metadata.left.dat", NULL);
         unlink((m_strHomeDir + ".tmp/metadata.left.dat").c_str());

         vector<string> fl;
         attic->list_r("/", fl);
         for (vector<string>::iterator i = fl.begin(); i != fl.end(); ++ i)
            move(*i, ".attic", "");

         attic->clear();
         delete attic;

         m_SectorLog.insert("WARNING: certain files have been moved to ./attic due to conflicts.");
      }

      int id = 0;
      secconn.recv((char*)&id, 4);
      Address addr;
      addr.m_strIP = mip;
      addr.m_iPort = mport;
      m_Routing.insert(id, addr);

      int num;
      secconn.recv((char*)&num, 4);
      for (int i = 0; i < num; ++ i)
      {
         char ip[64];
         size = 0;
         secconn.recv((char*)&id, 4);
         secconn.recv((char*)&size, 4);
         secconn.recv(ip, size);
         addr.m_strIP = ip;
         secconn.recv((char*)&addr.m_iPort, 4);

         m_Routing.insert(id, addr);

         masters.insert(addr);
      }

      first = false;
      secconn.close();
   }

   SSLTransport::destroy();

   unlink((m_strHomeDir + ".tmp/metadata.dat").c_str());

   // initialize slave statistics
   m_SlaveStat.init();

   cout << "This Sector slave is successfully initialized and running now.\n";

   return 1;
}