///////////////////////////////////
// and here the fun begins...
int
main (int argc, char *argv[])
{
  // option processing variables
  int  opt;
  int  option_index = 0;

  // should the action be forced
  bool forceAction = false;

  // should help be displayed
  bool displayHelp = false;

  // should version info be displayed
  bool displayVer = false;

  // the action the user has chosen to perform
  int  action = 0;

  // the argument to the action
  const char* action_arg = NULL;

  // should existing records be updated (default: No)
  bool updateRecords = false;

  // selected itemNr, 0 = no specific item selected
  uint16_t itemNr = 0;

  // enabled DBTypes (default to all)
  int dbTypes = (EQItemDB::LORE_DB | EQItemDB::NAME_DB | 
		 EQItemDB::DATA_DB | EQItemDB::RAW_DATA_DB);

  // search string
  QString search;

  // note program name for later use.
  progname = argv[0];

  // Get an instance of the EQItemDB
  EQItemDB* itemDB = new EQItemDB;
  
  // begin processing options
  while ((opt = getopt_long( argc,
			     argv,
			     OPTION_LIST,
			     option_list,
			     &option_index)) != -1)
    {
      switch(opt)
	{
	case 'd': // display an item
	case 'l': // list items
	case 'f': // import from a flat file db
	case 'r': // import from a itemrawdata.dbm file
	case 'o': // import from an old GDBM file
	case 'e': // export a raw data record
	case 'x': // export database as a CSV file
	case 'D': // delete a record
	case 'R': // reorganize database
	case 'u': // upgrade ItemDB to current format
	  // these actions are mutually exclusive, if two chosen, display help
	  if (action != 0)
	    displayHelp = true;
	  else
	  {
	    // save action and it's argument
	    action = opt;
	    action_arg = optarg;
	  }
	  break;
	case 'i':
	  itemNr = (uint16_t)atoi(optarg);
	  break;
	case 'U':
	  updateRecords = true;
	  break;
	case 'v':
	case 'V':
	  displayVer = true;
	  break;
	case ITEMDB_LORE_FILENAME_OPTION:
	  itemDB->SetDBFile(EQItemDB::LORE_DB, optarg);
	  break;
	case ITEMDB_NAME_FILENAME_OPTION:
	  itemDB->SetDBFile(EQItemDB::NAME_DB, optarg);
	  break;
	case ITEMDB_DATA_FILENAME_OPTION:
	  itemDB->SetDBFile(EQItemDB::DATA_DB, optarg);
	  break;
	case ITEMDB_RAW_FILENAME_OPTION:
	  itemDB->SetDBFile(EQItemDB::RAW_DATA_DB, optarg);
	  break;
	case ITEMDB_DATABASES_ENABLED:
	  dbTypes = atoi(optarg);
	  break;
	case FORCE_ACTION:
	  forceAction = true;
	  break;
	case 'h': // display usage info
	default:
	  displayHelp = true;
	  break;
	}
    }

  // if no action selected, display help
  if ((action == 0) && !displayHelp && !displayVer)
  {
    fprintf(stderr, "No action specified\n");
    displayHelp = true;
  }

  // are there extra arguments
  if (optind < argc)
  {
    //yes, there are

    // is the action list with no search argument
    if ((action == 'l') && (action_arg == 0))
    {
      // yes, so use them for the search argument
      while (optind < argc)
	{
	  if (!search.isEmpty())
	    search += " ";
	  
	  // append extra arguments to search string
	  search += argv[optind++];
	}
    }
    else // otherwise display help
    {
      fprintf(stderr, "Extra arguments!\n");
      displayHelp = true;
    }
  }

  // if either the display or delete actions were specified and no 
  // item was specified display help.
  if (((action == 'd') || (action == 'D')) && 
      (itemNr == 0))
    displayHelp = true;

  // result to return from the program (the exit code).
  int result = 0;

  // display the help/usage information if required and exit
  if (displayHelp)
  {
    // display the usage information
    displayUsage(); 

    // return non-zero result
    result = 1;
  }
  else
  {
    // enable the set of dbtypes
    itemDB->SetEnabledDBTypes(dbTypes);
    
    // display the version information
    if (displayVer)
      displayVersion(itemDB);

    // perform the requested action
    switch(action)
    {
    case 'd': // display an item
      result = displayRecord(itemDB, itemNr);
      break;
    case 'l': // list items
    {
      if (action_arg)
	search = action_arg;
      result = listRecords(itemDB, itemNr, search);
      break;
    }
    case 'f': // import from a flat file db
      result = importFlatFile(itemDB, action_arg, itemNr, 
			      forceAction, updateRecords);
      break;
    case 'r': // import from a itemrawdata.dbm file
    case 'o': // import from an old GDBM file
      // the above two options are really the same
      result = importGDBM(itemDB, action_arg, itemNr, 
			  forceAction, updateRecords);
      break;
    case 'e': // export a raw data record
      result = exportRawRecord(itemDB, action_arg, itemNr);
      break;
    case 'x': // export database as a CSV file
      result = exportRecordCSV(itemDB, action_arg, itemNr);
      break;
    case 'D': // delete a record
      result = deleteRecord(itemDB, itemNr, forceAction);
      break;
    case 'R': // reorganize database
      result = reorganize(itemDB);
      break;
    case 'u': // upgrade ItemDB to current format
      result = upgradeItemDB(itemDB);

    }
  }

  // shutdown the ItemDB
  itemDB->Shutdown();

  // delete this instance of ItemDB
  delete itemDB;

  return result;
}