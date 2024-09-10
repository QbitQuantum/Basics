int main(int argc, const char** argv){
  ndb_init();

  const char* _tabname = NULL;
  int _help = 0;
  
  struct getargs args[] = {
    { "usage", '?', arg_flag, &_help, "Print help", "" }
  };
  int num_args = sizeof(args) / sizeof(args[0]);
  int optind = 0;
  char desc[] = 
    "tabname\n"\
    "This program will bulk copy data from a file to a table in Ndb.\n";
  
  if(getarg(args, num_args, argc, argv, &optind) ||
     argv[optind] == NULL || _help) {
    arg_printusage(args, num_args, argv[0], desc);
    return NDBT_ProgramExit(NDBT_WRONGARGS);
  }
  _tabname = argv[optind];
  ndbout << "Tablename: " << _tabname << endl;

  // Connect to Ndb
  Ndb MyNdb( "TEST_DB" );

  if(MyNdb.init() != 0){
    ERR(MyNdb.getNdbError());
    return NDBT_ProgramExit(NDBT_FAILED);
  }

  // Connect to Ndb and wait for it to become ready
  while(MyNdb.waitUntilReady() != 0)
    ndbout << "Waiting for ndb to become ready..." << endl;
   
  // Check if table exists in db
  const NdbDictionary::Table* pTab = MyNdb.getDictionary()->getTable(_tabname);
  if(pTab == NULL){
    ndbout << " Table " << _tabname << " does not exist!" << endl;
    return NDBT_ProgramExit(NDBT_WRONGARGS);
  }
  
  char buf[255];
  BaseString::snprintf(buf, sizeof(buf), "%s.data", (const char*)_tabname);
  if (insertFile(&MyNdb, pTab, buf) != 0){
    return NDBT_ProgramExit(NDBT_FAILED);
  }

  return NDBT_ProgramExit(NDBT_OK);

}