static vumatptr load(const char* n){
  typedef std::vector<VUMATPtrHandler> VUMATPtrContainer;
  static LibrariesHandler libraries;
  static VUMATPtrContainer fcts;
#ifdef HAVE_STD_MUTEX
   static std::mutex m;
   std::lock_guard<std::mutex> lock(m);
#else /* HAVE_STD_MUTEX */
   lock l;
#endif  /* HAVE_STD_MUTEX */
  try{
    VUMATPtrContainer::const_iterator p;
    p = std::find_if(fcts.begin(),fcts.end(),VUMATNameCompare(n));
    if(p==fcts.end()){
      const std::pair<std::string,std::string> lf = decompose(n);
      const std::string& lib = lf.first;
      const std::string& fct = lf.second;
      if(lib.empty()){
	report("","","",n);
	return NULLPTR(vumatptr);
      }
#if (defined _WIN32 || defined _WIN64) && (!defined __CYGWIN__)
      libptr l = ::LoadLibrary(TEXT (lib.c_str()));
#else
      libptr l = ::dlopen(lib.c_str(),RTLD_NOW);
#endif
      if(l==NULLPTR(libptr)){
#if (defined _WIN32 || defined _WIN64) && (!defined __CYGWIN__)
	report(lib,"",getLastWin32Error(),n);
#else
	report(lib,"",::dlerror(),n);
#endif	
	return NULLPTR(vumatptr);
      }
      libraries.insert(std::make_pair(lib,l));
      union {
	void *ptr;
	vumatptr f;
      } r;
#if (defined _WIN32 || defined _WIN64) && (!defined __CYGWIN__)
      r.f = reinterpret_cast<vumatptr>(::GetProcAddress(l,fct.c_str()));
#else
      r.ptr = ::dlsym(l,fct.c_str());
#endif
      if(r.ptr==NULLPTR(void *)){
#if (defined _WIN32 || defined _WIN64) && (!defined __CYGWIN__)
	report(lib,fct,getLastWin32Error(),n);
#else
	report(lib,fct,::dlerror(),n);
#endif	
	return NULLPTR(vumatptr);
      }
      VUMATPtrHandler h;
      h.name = std::string(n,n+80);
      h.ptr  = r.f;
      fcts.push_back(h);
      return r.f;
    }
    return p->ptr;
  }