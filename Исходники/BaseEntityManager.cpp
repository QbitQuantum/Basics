bool BaseEntityManager::LoadAllBaseEntitiesFromRootTextFile( const string& strRootTextFile,
															  vector<BaseEntity *>& vecpBaseEntity,
															  std::string& db_filepath )
{
	CTextFileScanner scanner;
	if( !scanner.OpenFile( strRootTextFile ) )
	{
		LOG_PRINT_WARNING( " - Cannot open file: " + strRootTextFile );
		return false;
	}

	// change to the directory of 'strRootTextFile'
	path parent_path = path(strRootTextFile).parent_path();

	vector<string> vecSrcTextFile;
	string filename, relative_db_filepath;
	for( ; !scanner.End(); scanner.NextLine() )
	{
		if( scanner.TryScanLine( "input", filename ) )
			vecSrcTextFile.push_back( path(parent_path / filename).string() );

		scanner.TryScanLine( "output", relative_db_filepath );
	}

	if( vecSrcTextFile.size() == 0 )		 { LOG_PRINT_ERROR( " - no input file is specified." ); return false; }

	if( 0 < relative_db_filepath.length() )
	{
		db_filepath = path( parent_path / relative_db_filepath ).string();
	}

	size_t i, num_input_files = vecSrcTextFile.size();
	for( i=0; i<num_input_files; i++ )
	{
		LoadAllBaseEntitiesFromTextFile( vecSrcTextFile[i], vecpBaseEntity );
	}

	return true;
}