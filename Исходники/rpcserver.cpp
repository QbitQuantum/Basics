int rpcfslist(void *data, unsigned int datalen, KnownClient *client, void *rbuffer, unsigned int *rlen)
{
  *rlen = 0;

  //Min entry index to start listing at
  unsigned int m = readUnsignedNumber(data, 2);
  data += 2;

  if (strlen((char *)data) == 1)
  {
    //hardcoded response. Note that SD card might not exist.
    //TODO: Properly detect missing SD card
    if (((char *)data)[0] == '/')
    {
      strcpy((char *)rbuffer, "\x02spiffs\x02sd");
      rlen[0] = 10;
      return 0;
    }
  }

  //Skip the first slash if any(Assume mountpoint name is at least 2 chars)
  //Then get the slash after that.
  char *fn = strchr((char *)data + 1, '/');
  if (fn == 0)
  {
    RPC_ERR(3, "Impossible filename does not contain a root directory");
  }

  fs::FS *mountpoint = getFS((char *)data);
  if (mountpoint == 0)
  {
    RPC_ERR(3, "That device does not exist or is disconnected.");
  }

  int count = 0;
#ifdef ESP32
  File d = mountpoint->open(fn);
#else
  if (mountpoint->exists(fn) == false)
  {
    RPC_ERR(3, "Selected dir does not exist");
  }
  Dir d = mountpoint->openDir(fn);
#endif

  //Start from end if string
  int dirnamelen = strlen(fn);

  //Get rid of the trailing slash that seems to mess things up
  //While we're at it
  if (fn[dirnamelen - 1] == '/')
  {
    fn[dirnamelen - 1] = 0;
  }

#ifdef ESP32
  if (!d)
  {
    RPC_ERR(3, ("Selected dir " + String((char *)data + 2) + " does not exist").c_str());
  }

  if (!d.isDirectory())
  {
    RPC_ERR(1, "Selected obj is not a directory");
  }

  File f = d.openNextFile();
#else
  d.next();
  File f = d.openFile("r");
#endif

  String l = "";
  while (f && (rlen[0] < 1024))
  {
    if (l == f.name())
    {
      return 0;
    }
    l = f.name();
    if (count >= m)
    {
      strcpy((char *)rbuffer + 1, ((char *)f.name()) + 1);
//I don't think ESP8266 SPIFFS has true directories
#ifdef ESP32
      if (f.isDirectory())
#else
      if (0)
#endif
      {
        *(char *)rbuffer = 2;
      }
      else
      {
        *(char *)rbuffer = 1;
      }

      //Plus 1 for typecode, plus 1 for null
      rlen[0] += strlen(f.name() + 1) + 2;
      rbuffer += (strlen(f.name() + 1) + 2);
    }

#ifdef ESP32
    f = d.openNextFile();
#else
    d.next();
    f = d.openFile("r");
#endif

    count += 1;
  }
  return 0;
}