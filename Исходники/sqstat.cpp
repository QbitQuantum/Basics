vector<SQUID_Connection> sqstat::GetInfo(Options* pOpts) {
   sqconn con;

   string temp_str;

   active_conn = 0;

   long long esize;
   long etime;

   int n=0, delay_pool;

   vector<SQUID_Connection>::iterator Conn_it; // pointer to current peer
   vector<Uri_Stats>::iterator Stat_it; // pointer to current stat
   Uri_Stats newStats;

   try {
      con.open(pOpts->host, pOpts->port);
   }
   catch(sqconnException &e) {
      std::stringstream error;
      error << e.what() << " while connecting to " << pOpts->host << ":" << pOpts->port;
      throw sqstatException(error.str(), FAILED_TO_CONNECT);
   }

   connections.clear();

   time_t timenow = 0;
   time_t timediff = 0;

   try {
      string request = "GET cache_object://localhost/active_requests HTTP/1.0\n";
      if (!pOpts->pass.empty()) {
         string encoded = Base64::Encode("admin:" + pOpts->pass);
         request += "Authorization: Basic " + encoded + "\n";
      }
      con << request;
      Uri_Stats oldStats;
      while ((con >> temp_str) != 0) {
         if (connections.size()==0) {
            if (n==0) {
               if (temp_str != "HTTP/1.0 200 OK" && temp_str != "HTTP/1.1 200 OK") {
                  std::stringstream error;
                  error << "Access to squid statistic denied: " << temp_str;
                  /*string ip;
                  try {
                     ip = get_ip();
                  }
                  catch (string) {
                     ip = "<your_host_ip>";
                  }*/
                  /*error << "You must enable access to squid statistic in squid.conf by adding strings like:" << endl << endl;
                  error << "\tacl adminhost src <admin_host_ip_here>/255.255.255.255" << endl;
                  error << "\thttp_access allow manager adminhost" << endl;
                  error << "\thttp_access deny manager";*/
                  throw sqstatException(error.str(), ACCESS_DENIED);
               } else {
                  n=1;
                  timenow = time(NULL);
                  timediff = timenow - lastruntime;
                  continue;
               }
            }
         }

         vector<string> result;
         if (temp_str.substr(0,8) == "Server: ") {
            result = Utils::SplitString(temp_str, " ");
            if (result.size() == 2) {
               squid_version = result[1];
            } else { FormatChanged(temp_str); }
         } else if (temp_str.substr(0,12) == "Connection: ") {
            result = Utils::SplitString(temp_str, " ");
            if (result.size() == 2) {
               newStats.id = result[1];
               oldStats = FindUriStatsById(oldConnections, result[1]);
               newStats.uri = "";
               newStats.username = "";
               newStats.size = 0;
               newStats.count = 0;
               newStats.oldsize = 0;
               newStats.etime = 0;
               newStats.delay_pool = -1;
            } else { FormatChanged(temp_str); }
         } else if ((temp_str.substr(0,6) == "peer: ") or (temp_str.substr(0,8) == "remote: ")) {
            result = Utils::SplitString(temp_str, " ");
            if (result.size() == 2) {
               std::pair <string, string> peer = Utils::SplitIPPort(result[1]);
               if (!peer.first.empty()) {
                  Conn_it = std::find_if( connections.begin(), connections.end(), std::bind2nd( std::ptr_fun(ConnByPeer) , peer.first) );
                  // if it is new peer, create new SQUID_Connection
                  if (Conn_it == connections.end()) {
                     SQUID_Connection connection;
                     connection.peer = peer.first;
#ifdef WITH_RESOLVER
                     connection.hostname = DoResolve(pOpts, peer.first);
#endif
                     connections.push_back(connection);
                     Conn_it = connections.end() - 1;
                  }
                  Conn_it->stats.push_back(newStats);
                  Stat_it = Conn_it->stats.end() - 1;
               }
            } else { FormatChanged(temp_str); }
         } else if (temp_str.substr(0,4) == "uri ") {
            result = Utils::SplitString(temp_str, " ");
            if (result.size() == 2) {
               Stat_it->uri = result[1];
               Stat_it->count = 1;
               Stat_it->curr_speed = 0;
               Stat_it->av_speed = 0;
            } else { FormatChanged(temp_str); }
         } else if (temp_str.substr(0,11) == "out.offset ") {
            result = Utils::SplitString(temp_str, " ");
            if (result.size() == 4) {
               esize = atoll(result[3].c_str());
               Stat_it->size = esize;
               Stat_it->oldsize = oldStats.size;
               Conn_it->sum_size += esize;
            } else { FormatChanged(temp_str); }
         } else if (temp_str.substr(0,6) == "start ") {
            result = Utils::SplitString(temp_str, " ");
            if (result.size() == 5) {
               string temp = result[2].erase(0,1);
               etime = atoi(temp.c_str());
               Stat_it->etime = etime;
               if (etime > Conn_it->max_etime)
                  Conn_it->max_etime = etime;
            } else { FormatChanged(temp_str); }
         } else if (temp_str.substr(0,11) == "delay_pool ") {
            result = Utils::SplitString(temp_str, " ");
            if (result.size() == 2) {
               string temp = result[1];
               delay_pool = atoi(temp.c_str());
               Stat_it->delay_pool = delay_pool;
            } else { FormatChanged(temp_str); }
         } else if (temp_str.substr(0,9) == "username ") {
            result = Utils::SplitString(temp_str, " ");
            if (result.size() == 1)
               result.push_back("-");
            if (result.size() == 2) {
               string username = result[1];
               if (!(username == "-")) {
                  Utils::ToLower(username);
                  Stat_it->username = username;
                  if (!Utils::MemberOf(Conn_it->usernames, username))
                     Conn_it->usernames.push_back(username);
               }
            } else { FormatChanged(temp_str); }
         }
      }
   }
   catch(sqconnException &e) {
      std::stringstream error;
      error << e.what();
      throw sqstatException(error.str(), UNKNOWN_ERROR);
   }

   av_speed = 0;
   curr_speed = 0;
   for (vector<SQUID_Connection>::iterator Conn = connections.begin(); Conn != connections.end(); ++Conn) {

      sort(Conn->stats.begin(), Conn->stats.end(), CompareURLs);

      active_conn += Conn->stats.size();

      for (vector<Uri_Stats>::iterator Stats = Conn->stats.begin(); Stats != Conn->stats.end(); ++Stats) {
         long stat_av_speed = 0;
         if ((Stats->size != 0) && (Stats->etime != 0))
            stat_av_speed = Stats->size/Stats->etime;
         Stats->av_speed = stat_av_speed;
         Conn->av_speed += stat_av_speed;
         av_speed += stat_av_speed;
         long stat_curr_speed = 0;
         if ((Stats->size != 0) && (Stats->oldsize != 0) && (lastruntime != 0) && (Stats->size > Stats->oldsize)) {
            if (timediff < 1) timediff = 1;
            stat_curr_speed = (Stats->size - Stats->oldsize) / timediff;
            /*if ((stat_curr_speed > 10000000) || (stat_curr_speed < 0)) {
               cout << Stats->size << " " <<  Stats->oldsize << " " << timenow << " " << lastruntime << endl;
               throw;
            }*/
            Stats->curr_speed = stat_curr_speed;
            Conn->curr_speed += stat_curr_speed;
            curr_speed += stat_curr_speed;
         } /*else {
            Conn->curr_speed += stat_av_speed;
            curr_speed += stat_av_speed;
         }*/
      }
   }

   sort(connections.begin(), connections.end(), sqstat::CompareSIZE);

   oldConnections = connections;
   lastruntime = timenow;

   return connections;
}