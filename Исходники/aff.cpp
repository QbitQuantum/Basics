void aff::start(std::map<std::string, Variant* > args)
{
  std::list<Variant *> vl; 
  std::list<Variant *>::iterator 		 vpath; 
  AffNode*					 node;

  if (args["parent"])
    this->parent = args["parent"]->value<Node* >();
  else
    this->parent = VFS::Get().GetNode("/");
  if (args["path"])
    vl = args["path"]->value<std::list<Variant* > >();
  else
    throw(envError("aff module requires path argument"));
  if (args["cache size"])
  {
    std::ostringstream cs;
    cs << args["cache size"]->value<uint32_t >();
    this->cache_size = cs.str(); 
  }
  else
    this->cache_size = "2";
#ifndef WIN32
  setenv("AFFLIB_CACHE_PAGES", this->cache_size.c_str(), 1);
#else
  _putenv_s("AFFLIB_CACHE_PAGES", this->cache_size.c_str());
#endif

  for (vpath = vl.begin(); vpath != vl.end(); vpath++)
  {
     std::string path = (*vpath)->value<Path* >()->path;
     AFFILE* affile = af_open(path.c_str(), O_RDONLY, 0);
     if (affile)
     {
	std::string nname = path.substr(path.rfind('/') + 1);
	node = new AffNode(nname, af_get_imagesize(affile), NULL, this, path, affile);
   	this->registerTree(this->parent, node);   
	this->res[path] = new Variant(std::string("added successfully by aff module"));
     }
     else 
        this->res[path] = new Variant(std::string("can't be added by aff module"));
  }

  return ;

}