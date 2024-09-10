u32t _std mod_searchload(const char *name, u32t flags, qserr *error) {
   char path[QS_MAXPATH+1],
       mname[E32MODNAME+5], *epos;
   strncpy(mname,name,E32MODNAME);
   mname[E32MODNAME] = 0;
   epos = strrchr(mname,'.');
   if (!epos||strlen(epos)>4) {
      epos = mname + strlen(mname);
      strcpy(epos,".DLL");
   } else
      epos = 0;
   strupr(mname);

   if (error) *error = 0;
   *path=0;
   _searchenv(mname,"LIBPATH",path);
   if (!*path) _searchenv(mname,"PATH",path);
   if (!*path) _searchenv(name,"LIBPATH",path);
   if (!*path) _searchenv(name,"PATH",path);
   if (!*path&&epos) {
      strcpy(epos,".EXE");
      _searchenv(mname,"PATH",path);
   }
   if (!*path) return 0;
   return mod_load(path, flags, error, 0);
}