// ParseIncludeDirective
//------------------------------------------------------------------------------
bool BFFParser::ParseIncludeDirective( BFFIterator & iter )
{
	// Sanity check include depth to detect cyclic includes
	if ( s_Depth >= 128 )
	{
		Error::Error_1035_ExcessiveDepthComplexity( iter );
		return false;
	}

	// we expect a " quoted string
	if ( *iter != '"' )
	{
		Error::Error_1031_UnexpectedCharFollowingDirectiveName( iter, AStackString<>( "include" ), '"' ); 
		return false;
	}

	BFFIterator stringStart( iter );
	stringStart++; // first actual character

	// find end of string
	if ( iter.ParseToNext( '"' ) == false )
	{
		Error::Error_1012_UnexpectedEndOfFile( iter );
		return false;
	}

	// unescape and substitute variables
	AStackString<> include;
	if ( PerformVariableSubstitutions( stringStart, iter, include ) == false )
	{
		return false;
	}

	iter++; // skip closing quote before returning

	FLOG_INFO( "Including: %s\n", include.Get() );

	// open include

	// 1) Try current directory
	AStackString<> includeToUse;
	if (PathUtils::IsFullPath(include) == false)
	{
		const char * lastSlash = iter.GetFileName().FindLast( NATIVE_SLASH );
		lastSlash = lastSlash ? lastSlash : iter.GetFileName().FindLast( OTHER_SLASH );
		lastSlash = lastSlash ? ( lastSlash + 1 ): iter.GetFileName().Get(); // file only, truncate to empty
		includeToUse.Assign( iter.GetFileName().Get(), lastSlash );
	}
	includeToUse += include;
	AStackString<> includeToUseClean;
	NodeGraph::CleanPath( includeToUse, includeToUseClean );
	FileStream f;
	if ( f.Open( includeToUseClean.Get(), FileStream::READ_ONLY ) == false )
	{
		Error::Error_1032_UnableToOpenInclude( stringStart, includeToUseClean );
		return false;
	}

	// check if include uses "once" pragma
	if ( FBuild::Get().GetDependencyGraph().IsOneUseFile( includeToUseClean ) )
	{
		// already seen, and uses #once : don't include again
		return true;
	}

	uint64_t includeTimeStamp = FileIO::GetFileLastWriteTime( includeToUseClean );

	// read content of include
	const uint32_t fileSize = (uint32_t)f.GetFileSize();
	AutoPtr< char > mem( (char *)ALLOC( fileSize + 1 ) );
	if ( f.Read( mem.Get(), fileSize ) != fileSize )
	{
		Error::Error_1033_ErrorReadingInclude( stringStart, include, Env::GetLastErr() );
		return false;
	}
	mem.Get()[ fileSize ] = '\000'; // sentinel
	BFFParser parser;
	const bool pushStackFrame = false; // include is treated as if injected at this point
	return parser.Parse( mem.Get(), fileSize, includeToUseClean.Get(), includeTimeStamp, pushStackFrame ); 
}