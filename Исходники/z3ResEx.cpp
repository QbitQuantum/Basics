bool z3ResEx::setFlags( const targs &args )
{
	if( args.Count() > 1 )
	{
		if( args.HasItem("--usage") )
		{
			PrintUsage();

			// Also stop execution here (but successfully)
			return false;
		}

		if( SetCurrentDirectoryA( args.GetItemValue(1) ) == 0 )
		{
			setMessage( "ERROR: Cannot set current path to \"%s\"", args.GetItemValue(1) );
			return false;
		}

		// Allow verbose toggle when not true by default
		if( !( m_verboseMessages ) )
			m_verboseMessages = ( args.HasItem("-v") || args.HasItem("--verbose") );

		// Disable file extraction
		if( args.HasItem("-x") || args.HasItem("--no-extraction") )
			m_doExtraction = false;

		// List the filesystem contents (no extraction)
		if( args.HasItem("-l") || args.HasItem("--list-filesystem") )
		{
			m_listContents = true;
			m_doExtraction = false;
		}

		// Specify which folder to extract
		if( args.HasItem("-c") || args.HasItem("--criteria") )
		{
			bool bHasValue = false;

			const char *strVal1 = args.GetItemValue("-c");
			if( strVal1 )
			{
				m_folderCriteria = strVal1;
				bHasValue = true;
			}
			else
			{
				const char *strVal2 = args.GetItemValue("--criteria");

				if( strVal2 )
				{
					m_folderCriteria = strVal2;
					bHasValue = true;
				}
			}

			if( !bHasValue )
			{
				setMessage( "ERROR: No criteria was specified" );
				return false;
			}
		}
	}
	else
	{
		// No arguments, but inform user of them!
		puts("To see all options, use the --usage flag\n");
	}

	if( m_verboseMessages )
	{
		// Print current flags

		if( m_doExtraction )	puts("LOG: Extracting files");
		if( m_listContents )	puts("LOG: Listing filesystem");
		if( !m_folderCriteria.empty( ) )
		{
			string tmp;
			tmp = "LOG: Search criteria set to '";
			tmp += m_folderCriteria.c_str();
			tmp += "'";
			puts( tmp.c_str() );
		}
	}

	std::transform(m_folderCriteria.begin(), m_folderCriteria.end(), m_folderCriteria.begin(), ::toupper);

	return true;
}