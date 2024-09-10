int _getInstance(const int argc, const char **argv)
{
  if (argv[0] == 0)
  {
    _giUsage();
    return 1;
  }
  
  // need to get class definition to find keys
  // first arg is name of class
  CIMClass cldef;
  try
  {
    cldef = _c.getClass( _nameSpace, argv[0] );
  }
  catch(Exception& e)
  {
    cerr << /* "getInstance: " << */ e.getMessage() << endl;
    return 1;
  }

  CIMObjectPath ref;
  CIMInstance inst;

  // If there are no more args, prompt user for keys
  if (argv[1] == 0) ref = CIMObjectPath(String::EMPTY, // hostname left blank
                                       _nameSpace,
                                       argv[0],
                                       _inputInstanceKeys(cldef));
  
  // else if there's another arg and it's "list", enumInstNames and print
  // a list from which user will select (return if none)
  else if (String::equalNoCase("list",argv[1]))
  {
    ref = _selectInstance(argv[0]);
    // An empty ObjectPath means nothing was selected
    if (ref.identical(CIMObjectPath())) return 0;
  }
    
  // else there's another arg but it's invalid
  else
  {
    _giUsage();
    return 1;
  }

  // get the specified instance
  try
  {
    inst = _c.getInstance(_nameSpace,ref);
  }
  catch(Exception& e)
  {
    cerr << /* "getInstance: " << */ e.getMessage() << endl;
    return 1;
  }
  _displayInstance(inst);
  return 0;
}