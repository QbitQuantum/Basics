void get_commandline_options(
	commandline_options&	cmdopt,
	int						argc,
	char**					argv )
{
	cmdopt.language = "C++";
	cmdopt.algorithm = "lalr1";
		
	int state = 0;
	for( int index = 1 ; index < argc ; index++ ) {
		if( argv[index][0] == '-' ) {
			if( strcmp( argv[index], "-java" ) == 0 ||
				strcmp( argv[index], "-Java" ) == 0 ) {
				cmdopt.language = "Java";
				continue;
			}
			if( strcmp( argv[index], "-cs" ) == 0 || strcmp( argv[index], "-CS" ) == 0 ||
				strcmp( argv[index], "-Cs" ) == 0 || strcmp( argv[index], "-C#" ) == 0 ||
				strcmp( argv[index], "-CSharp" ) == 0 || strcmp( argv[index], "-csharp#" ) == 0 ||
				strcmp( argv[index], "-c#" ) == 0 ) {
				cmdopt.language = "C#";
				continue;
			}
			if( strcmp( argv[index], "-d" ) == 0 || strcmp( argv[index], "-D" ) == 0 ) {
				cmdopt.language = "D";
				continue;
			}
			if( strcmp( argv[index], "-c++" ) == 0 || strcmp( argv[index], "-C++" ) == 0 ||
				strcmp( argv[index], "-cpp" ) == 0 || strcmp( argv[index], "-CPP" ) == 0 ) {
				cmdopt.language = "C++";
				continue;
			}
			if( strcmp( argv[index], "-js" ) == 0 || strcmp( argv[index], "-JS" ) == 0 ||
				strcmp( argv[index], "-javascript" ) == 0 ||
				strcmp( argv[index], "-JavaScript" ) == 0 ||
				strcmp( argv[index], "-JAVASCRIPT" ) == 0 ) {
				cmdopt.language = "JavaScript";
				continue;
			}
			if( strcmp( argv[index], "-lalr1" ) == 0 ) {
				cmdopt.algorithm = "lalr1";
				continue;
			}
			if( strcmp( argv[index], "-lr1" ) == 0 ) {
				cmdopt.algorithm = "lr1";
				continue;
			}

			std::cerr << "caper: unknown option: " << argv[index] << std::endl;
			exit(1);
		}

		switch( state ) {
		case 0: cmdopt.infile  = argv[index]; state++; break;
		case 1: cmdopt.outfile = argv[index]; state++; break;
		default:
			std::cerr << "caper: too many arguments" << std::endl;
			exit(1);
		}
	}

	if( state < 2 ) {
		std::cerr << "caper: usage: caper [ -c++ | -js | -cs | -java ] input_filename output_filename" << std::endl;
		exit(1);
	}
		
}