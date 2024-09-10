// ReadResults
//------------------------------------------------------------------------------
/*static*/ bool JobQueueRemote::ReadResults( Job * job )
{
	const ObjectNode * node = job->GetNode()->CastTo< ObjectNode >();
	const bool includePDB = (  node->IsUsingPDB() && ( job->IsLocal() == false ) );

	// main object
	FileStream fs;
	if ( fs.Open( node->GetName().Get() ) == false )
	{
		FLOG_ERROR( "File missing despite success: '%s'", node->GetName().Get() );
		return false;
	}
	uint32_t size = (uint32_t)fs.GetFileSize();
	uint32_t size2 = 0;

	// pdb file if present
	FileStream fs2;
	if ( includePDB )
	{
		AStackString<> pdbName;
		node->GetPDBName( pdbName );
		if ( fs2.Open( pdbName.Get() ) == false )
		{
			FLOG_ERROR( "File missing despite success: '%s'", pdbName.Get() );
			return false;
		}
		size2 = (uint32_t)fs2.GetFileSize();
	}

	// calc memory required
	size_t memSize = sizeof( uint32_t ); // write size of first file
	memSize += size;
	if ( includePDB )
	{
		memSize += sizeof( uint32_t ); // write size of second file
		memSize += size2;
	}

	// allocate entire buffer
	AutoPtr< char > mem( (char *)ALLOC( memSize ) );

	// write first file size
	*( (uint32_t *)mem.Get() ) = size;

	// read first file
	if ( fs.Read( mem.Get() + sizeof( uint32_t ), size ) != size )
	{
		FLOG_ERROR( "File read error for '%s'", node->GetName().Get() );
		return false;
	}

	if ( includePDB )
	{
		// write second file size
		*( (uint32_t *)( mem.Get() + sizeof( uint32_t ) + size ) ) = size2;

		// read second file
		if ( fs2.Read( mem.Get() + sizeof( uint32_t ) + size + sizeof( uint32_t ), size2 ) != size2 )
		{
			FLOG_ERROR( "File read error for '%s'", node->GetName().Get() );
			return false;
		}
	}

	// transfer data to job
	job->OwnData( mem.Release(), memSize );

	return true;
}