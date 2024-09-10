int main(int argc, char** argv)
{
   if (argc < 2)
   {
      help();
      return -1;
   }

   unsigned int thresh = 65536;
   int timeout = 3600 * 24; // default wait for one day

   CmdLineParser clp;
   if (clp.parse(argc, argv) < 0)
   {
      help();
      return -1;
   }

   for (map<string, string>::const_iterator i = clp.m_mDFlags.begin(); i != clp.m_mDFlags.end(); ++ i)
   {
      if (i->first == "w")
         thresh = atoi(i->second.c_str());
      else if (i->first == "t")
      {
         timeout = atoi(i->second.c_str());
         if (timeout < 0)
            timeout = INT_MAX;
      }
      else
      {
         help();
         return -1;
      }
   }

   Sector client;
   if (Utility::login(client) < 0)
      return -1;   

   list<string> filelist;

   for (vector<string>::iterator i = clp.m_vParams.begin(); i < clp.m_vParams.end(); ++ i)
   {
      vector<string> fl;
      fl.clear();

      bool wc = WildCard::isWildCard(*i);
      if (!wc)
      {
         SNode attr;
         if (client.stat(*i, attr) < 0)
         {
            cerr << "ERROR: source file does not exist.\n";
            return -1;
         }
         getFileList(*i, fl, client, thresh);
      }
      else
      {
         string path = *i;
         string orig = path;
         size_t p = path.rfind('/');
         if (p == string::npos)
            path = "/";
         else
         {
            path = path.substr(0, p);
            orig = orig.substr(p + 1, orig.length() - p);
         }

         vector<SNode> filelist;
         int r = client.list(path, filelist);
         if (r < 0)
            cerr << "ERROR: " << r << " " << SectorError::getErrorMsg(r) << endl;

         for (vector<SNode>::iterator i = filelist.begin(); i != filelist.end(); ++ i)
         {
            if (WildCard::match(orig, i->m_strName))
               getFileList(path + "/" + i->m_strName, fl, client, thresh);
         }
      }

      filelist.insert(filelist.end(), fl.begin(), fl.end());
   }

   int result = -1;

   timeval t;
   gettimeofday(&t, NULL);
   int exp_time = t.tv_sec + timeout;

   int interval = 1;
   int total = -1;
   int new_total = 0;

   while (!filelist.empty())
   {
      new_total = 0;

      for (list<string>::iterator i = filelist.begin(); i != filelist.end();)
      {
         SNode sn;
         if (client.stat(*i, sn) < 0)
         {
            cout << "file " << sn.m_strName << " is lost.\n";
            break;
         }

         int diff = (sn.m_iReplicaNum > int(thresh)) ? (thresh - sn.m_sLocation.size()) : (sn.m_iReplicaNum - int(sn.m_sLocation.size()));

         if (diff <= 0)
         {
            list<string>::iterator j = i;
            ++ i;
            filelist.erase(j);
         }
         else
         {
            if ((result = client.copy(*i, *i)) < 0)
            {
               Utility::print_error(result);

               list<string>::iterator j = i;
               ++ i;
               filelist.erase(j);

               break;
            }

            ++ i;
            new_total += diff;
         }
      }

      timeval curr_time;
      gettimeofday(&curr_time, NULL);
      if (curr_time.tv_sec > exp_time)
      {
         cout << "timeout.\n";
         break;
      }

      //TODO: sleep diff for the last time
      if (interval < exp_time - curr_time.tv_sec)
         sleep(interval);
      else
         sleep(exp_time - curr_time.tv_sec);

      // wait longer if no progress, otherwise continue to wait for 1 sec
      if ((total > 0) && (new_total < total))
      {
         total = new_total;
         interval = 1;
      }
      else if (interval < 16)
      {
         interval <<= 1;
      }
   }

   if (filelist.empty())
   {
      cout << "all files have enough replicas.\n";
      result = 0;
   }

   Utility::logout(client);

   return result;
}