 inline bool directory::remove(const string &pathname) {
   lstring list = directory::contents(pathname);
   for(auto &name : list) {
     if(name.endswith("/")) directory::remove({pathname, name});
     else file::remove({pathname, name});
   }
   return _wrmdir(utf16_t(pathname)) == 0;
 }