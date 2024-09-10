String FindHaxelib(String inLib)
{
   bool loadDebug = getenv("HXCPP_LOAD_DEBUG");

   // printf("FindHaxelib %S\n", inLib.__s);

   String haxepath;

   #if !defined(HX_WINRT) && !defined(EPPC)
      struct stat s;
      if ( (stat(".haxelib",&s)==0 && (s.st_mode & S_IFDIR) ) )
         haxepath = HX_CSTRING(".haxelib");
      if (loadDebug)
          printf( haxepath.length ? "Found local .haxelib\n" : "No local .haxelib\n");
   #endif

   if (haxepath.length==0)
   {
      haxepath = GetEnv("HAXELIB_PATH");
      if (loadDebug)
         printf("HAXELIB_PATH env:%s\n", haxepath.__s);
   }

   if (haxepath.length==0)
   {
       #ifdef _WIN32
       String home = GetEnv("HOMEDRIVE") + GetEnv("HOMEPATH") + HX_CSTRING("/.haxelib");
       #else
       String home = GetEnv("HOME") + HX_CSTRING("/.haxelib");
       #endif
       haxepath = GetFileContents(home);
       if (loadDebug)
          printf("HAXEPATH home:%s\n", haxepath.__s);
   }

   if (haxepath.length==0)
   {
      haxepath = GetEnv("HAXEPATH");
      if (loadDebug)
         printf("HAXEPATH env:%s\n", haxepath.__s);
      if (haxepath.length>0)
      {
         haxepath += HX_CSTRING("/lib");
      }
   }

   if (loadDebug)
      printf("HAXEPATH dir:%s\n", haxepath.__s);

   if (haxepath.length==0)
   {
       haxepath = GetFileContents(HX_CSTRING("/etc/.haxepath"));
       if (loadDebug) printf("HAXEPATH etc:%s\n", haxepath.__s);
   }

   if (haxepath.length==0)
   {
      #ifdef _WIN32
      haxepath = HX_CSTRING("C:\\HaxeToolkit\\haxe\\lib");
      #else
      haxepath = HX_CSTRING("/usr/lib/haxe/lib");
      #endif
       if (loadDebug) printf("HAXEPATH default:%s\n", haxepath.__s);
   }

   String dir = haxepath + HX_CSTRING("/") + inLib + HX_CSTRING("/");


   String dev = dir + HX_CSTRING(".dev");
   String path = GetFileContents(dev);
   if (loadDebug) printf("Read dev location from file :%s, got %s\n", dev.__s, path.__s);
   if (path.length==0)
   {
      path = GetFileContents(dir + HX_CSTRING(".current"));
      if (path.length==0)
         return null();
      // Replace "." with "," ...
      String with_commas;
      for(int i=0;i<path.length;i++)
         if (path.getChar(i)=='.')
            with_commas += HX_CSTRING(",");
         else
            with_commas += path.substr(i,1);

      path = dir + with_commas + HX_CSTRING("/");
   }

   return path;
}