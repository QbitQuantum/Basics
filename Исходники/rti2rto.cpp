int main(int argc, char* argv[])
{
	bool debug = false;
	uint32 dropLastNchains = 0;
	uint32 dropHighSPcount = 0;
	int sptl = 0;

	if (argc < 2)
	{
		usage();
		return 0;
	}
	
	std::vector<std::string> pathNames;

	// Parse command line args
	int i;
	for( i = 1; i < argc; i++ )
	{
		if ( strncmp( argv[i], "-v", 2 ) == 0 )
			debug = true;
		else if ( strncmp( argv[i], "-drop_last_n_chains=", 20 ) == 0 )
		{
			uint32 j;

			for ( j = 20; argv[i][j] >= '0' && argv[i][j] <= '9'; j++ )
			{
				dropLastNchains *= 10;
				dropLastNchains += ((int) argv[i][j] ) - 0x30;
			}

			if ( argv[i][j] != '\0' )
			{
				printf("Error: Invalid drop_last_n_chains number.\n\n");
				usage();
				exit( 1 );
			}
		}
		else if ( strncmp( argv[i], "-drop_high_sp_n_chains=", 23 ) == 0 )
		{
			uint32 j;

			for ( j = 23; argv[i][j] >= '0' && argv[i][j] <= '9'; j++ )
			{
				dropHighSPcount *= 10;
				dropHighSPcount += ((int) argv[i][j] ) - 0x30;
			}

			if ( argv[i][j] != '\0' )
			{
				printf("Error: Invalid drop_high_sp_n_chains number.\n\n");
				usage();
				exit( 1 );
			}
		}
		else if ( strncmp( argv[i], "-sptl=", 6 ) == 0 )
		{
			uint32 j;

			for ( j = 6; argv[i][j] >= '0' && argv[i][j] <= '9'; j++ )
			{
				sptl *= 10;
				sptl += ((int) argv[i][j] ) - 0x30;
			}

			if ( argv[i][j] != '\0' )
			{
				printf("Error: Invalid sptl number.\n\n");
				usage();
				exit( 1 );
			}
		}
		else
			GetTableList( argv[i], pathNames );
	}

	if ( debug )
	{
		for( int i = 0; i < argc; i++ )
			printf("%i: %s\n", i, argv[i]);
	}

	if ( pathNames.size() == 0 )
	{
		printf("no rainbow table found\n");
		return 0;
	}

	std::string resultFile, sType;

	for ( uint32 i = 0; i < pathNames.size(); i++ )
	{
		if( pathNames[i].substr( pathNames[i].length() - 4, pathNames[i].length()) == "rti2")
		{
			resultFile = pathNames[i].substr(0, pathNames[i].length() - 2); // Resulting file is .rt, not .rti2
			sType = "RTI2";
		}
		else if( pathNames[i].substr( pathNames[i].length() - 3, pathNames[i].length()) == "rti")
		{
			resultFile = pathNames[i].substr( 0, pathNames[i].length() - 1 ); // Resulting file is .rt, not .rti
			sType = "RTI";
		}
		else 
		{
			printf("File %s is not a RTI or a RTI2 file", pathNames[i].c_str() );
			continue;
		}
		
		// XXX this assumes someone is converting either just the last file
		// *or* doing a whole set which will read the last file first
		if ( dropLastNchains > 0 && i == 0 )
		{
			std::string::size_type lastX = resultFile.find_last_of('x');

			if ( lastX == std::string::npos )
			{
				std::cout << "Could not parse the filename to drop the last chains"
					<< std::endl;
				exit( -1 );
			}
			
			std::string::size_type firstSplit
				= resultFile.find_first_of('_',lastX);

			#if defined(_WIN32) && !defined(__GNUC__)
				uint64 chains = _atoi64( resultFile.substr( lastX + 1, firstSplit - lastX - 1).c_str() );
			#else
				uint64 chains = atoll( resultFile.substr( lastX + 1, firstSplit - lastX - 1 ).c_str() );
			#endif

			chains -= dropLastNchains;

			resultFile.replace( lastX + 1, firstSplit - lastX - 1, uint64tostr( chains ) );
		}

		ConvertRainbowTable( pathNames[i], resultFile, sType, debug, dropLastNchains, dropHighSPcount, sptl );
		dropLastNchains = 0;
		dropHighSPcount = 0;

		printf("\n");
	}
	return 0;
}