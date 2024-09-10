void BlockDataManagerConfig::parseArgs(int argc, char* argv[])
{
   /***
   --testnet: run db against testnet bitcoin network

   --regtest: run db against regression test network

   --rescan: delete all processed history data and rescan blockchain from the
   first block

   --rebuild: delete all DB data and build and scan from scratch

   --rescanSSH: delete balance and txcount data and rescan it. Much faster than
   rescan or rebuild.

   --datadir: path to the operation folder

   --dbdir: path to folder containing the database files. If empty, a new db
   will be created there

   --satoshi-datadir: path to blockchain data folder (blkXXXXX.dat files)

   --ram_usage: defines the ram use during scan operations. 1 level averages
   128MB of ram (without accounting the base amount, ~400MB). Defaults at 4.
   Can't be lower than 1. Can be changed in between processes

   --thread-count: defines how many processing threads can be used during db
   builds and scans. Defaults to maximum available CPU threads. Can't be
   lower than 1. Can be changed in between processes

   --zcthread-count: defines the maximum number on threads the zc parser can
   create for processing incoming transcations from the network node

   --db-type: sets the db type:
   DB_BARE: tracks wallet history only. Smallest DB.
   DB_FULL: tracks wallet history and resolves all relevant tx hashes.
   ~750MB DB at the time of 0.95 release. Default DB type.
   DB_SUPER: tracks all blockchain history. XXL DB (100GB+).
   Not implemented yet

   db type cannot be changed in between processes. Once a db has been built
   with a certain type, it will always function according to that type.
   Specifying another type will do nothing. Build a new db to change type.

   --cookie: create a cookie file holding a random authentication key to allow
   local clients to make use of elevated commands, like shutdown.

   --fcgi-port: sets the DB listening port.

   --clear-mempool: delete all zero confirmation transactions from the DB.

   ***/

   try
   {
      //parse cli args
      map<string, string> args;
      for (int i = 1; i < argc; i++)
      {
         //check prefix
         if (strlen(argv[i]) < 2)
            throw DbErrorMsg("invalid CLI arg");

         string prefix(argv[i], 2);
         if (prefix != "--")
            throw DbErrorMsg("invalid CLI arg");

         //string prefix and tokenize
         string line(argv[i] + 2);
         auto&& argkeyval = getKeyValFromLine(line, '=');
         args.insert(make_pair(
            argkeyval.first, stripQuotes(argkeyval.second)));
      }

      processArgs(args, true);

      //figure out datadir
      auto argIter = args.find("datadir");
      if (argIter != args.end())
      {
         dataDir_ = argIter->second;
         args.erase(argIter);
      }
      else
      {
         if (!testnet_ && !regtest_)
            dataDir_ = defaultDataDir_;
         else if (!regtest_)
            dataDir_ = defaultTestnetDataDir_;
         else
            dataDir_ = defaultRegtestDataDir_;
      }

      expandPath(dataDir_);

      //get datadir
      auto configPath = dataDir_;
      appendPath(configPath, "armorydb.conf");

      if (DBUtils::fileExists(configPath, 2))
      {
         ConfigFile cf(configPath);
         auto mapIter = cf.keyvalMap_.find("datadir");
         if (mapIter != cf.keyvalMap_.end())
            throw DbErrorMsg("datadir is illegal in .conf file");

         processArgs(cf.keyvalMap_, false);
      }

      processArgs(args, false);

      //figure out defaults
      bool autoDbDir = false;
      if (dbDir_.size() == 0)
      {
         dbDir_ = dataDir_;
         appendPath(dbDir_, dbDirExtention_);
         autoDbDir = true;
      }

      if (blkFileLocation_.size() == 0)
      {
         if (!testnet_)
            blkFileLocation_ = defaultBlkFileLocation_;
         else
            blkFileLocation_ = defaultTestnetBlkFileLocation_;
      }

      //expand paths if necessary
      expandPath(dbDir_);
      expandPath(blkFileLocation_);

      if (blkFileLocation_.size() < 6 ||
         blkFileLocation_.substr(blkFileLocation_.length() - 6, 6) != "blocks")
      {
         appendPath(blkFileLocation_, "blocks");
      }

      logFilePath_ = dataDir_;
      appendPath(logFilePath_, "dbLog.txt");

      //test all paths
      auto testPath = [](const string& path, int mode)
      {
         if (!DBUtils::fileExists(path, mode))
         {
            stringstream ss;
            ss << path << " is not a valid path";

            cout << ss.str() << endl;
            throw DbErrorMsg(ss.str());
         }
      };

      testPath(dataDir_, 6);

      //create dbdir if was set automatically
      if (autoDbDir)
      {
         try
         {
            testPath(dbDir_, 0);
         }
         catch (DbErrorMsg&)
         {
#ifdef _WIN32
            CreateDirectory(dbDir_.c_str(), NULL);
#else
            mkdir(dbDir_.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
#endif
         }
      }

      //now for the regular test, let it throw if it fails
      testPath(dbDir_, 6);

      testPath(blkFileLocation_, 2);

      //fcgi port
      if (useCookie_ && !customFcgiPort_)
      {
         //no custom fcgi port was provided and the db was spawned with a 
         //cookie file, fcgi port will be randomized
         srand(time(0));
         while (1)
         {
            auto port = rand() % 15000 + 49150;
            stringstream portss;
            portss << port;

            if (!testConnection("127.0.0.1", portss.str()))
            {
               fcgiPort_ = portss.str();
               break;
            }
         }
      }
   }
   catch (...)
   {
      exceptionPtr_ = current_exception();
   }
}