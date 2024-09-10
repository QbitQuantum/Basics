// This processes options of the form:
//   <hyphen><single option char><zero or more blanks><required argument string>
// e.g.  "-ifilename"  "-i filename".
// An (English) error message is emitted for "-i" without an argument,
// "-" without an option letter, and "x" without a hyphen, but
// all other options pass thru with no error, as they may be an X option
// processed later in the InitializeX call.
//
// If the "-u name" option is specified, a copy of the name is
// returned in the user_name output parameter.
// The name is always uppercased regardless of whether it is enclosed
// in double quotes.
void processOption(Int32 argc, char *argv[], Int32 &i, 
		   const char *& in_filename,
		   const char *& input_string,
		   const char *& out_filename,
		   char *& sock_port,
                   NAString &user_name
		   )
{
  Int32 iorig = i;
  char op = '\0';
// const char *argAfterOp = NULL;
  char *argAfterOp = NULL;
  Int32 status;
  if (argv[i][0] == '-')
  {
    op = argv[i][1];
    if (op)
      if (argv[i][2])
	argAfterOp = &argv[i][2];
    else if (i < argc-1)
      argAfterOp = argv[++i];
  }

  if (argAfterOp)
  {
    switch (op)
    {
      case 's':	sock_port = argAfterOp;				// socket port number
			break;
      case 'i':	in_filename = argAfterOp;			// input file
			break;
      case 'o':	out_filename = argAfterOp;			// output file
		break;
      case 'q':	input_string = argAfterOp;			// input qry
		break;
//    case 'p':	sqlci->getUtil()->setProgramName(argAfterOp);	// utility name
//    		break;
//    case 't':	sqlci->getUtil()->setTerminalName(argAfterOp);	// utility debug
//		sqlci->getUtil()->setDebug(11);			// inspect flag
//		break;

      case 'u':
      {
        // The user_name output parameter will contain a copy of the
        // name
        user_name = argAfterOp;
        user_name.toUpper();

      } // case 'u'
      break;

      default:
	; // ok -- may be an X option, processed later in InitializeX

    } // switch (op)
  } // if (argAfterOp)

  else
  {
    // No argument appears after the option
    switch (op)
    {
      case 'v': printf("sqlci version: %s\n", SCMBuildStr);
        exit(0);
        break;

      case 'i':
      case 'p':
      case 't':
        cerr << argv[0] << ": " << argv[iorig]
             << " option requires an argument -- ignored" << endl;
        break;
        
      case '\0':
        cerr << argv[0] << ": " << argv[iorig]
             << " option is unknown -- ignored" << endl;
        break;
        
      default:
	; // ok -- may be an X option, processed later in InitializeX
        
    } // switch (op)
  } // if (argAfterOp) else ...
}