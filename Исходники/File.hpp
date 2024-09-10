 static time_t timestamp(const string &filename, file::time mode = file::time::create) {
   #if !defined(_WIN32)
   struct stat64 data;
   stat64(filename, &data);
   #else
   struct __stat64 data;
   _wstat64(utf16_t(filename), &data);
   #endif
   switch(mode) { default:
     case file::time::create: return data.st_ctime;
     case file::time::modify: return data.st_mtime;
     case file::time::access: return data.st_atime;
   }
 }