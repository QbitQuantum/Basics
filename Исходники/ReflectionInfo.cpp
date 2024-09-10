	/*static*/ bool ReflectionInfo::WriteDefinitions()
	{
		uint32_t numProblems = 0;

		const ReflectionInfo * ri = s_FirstReflectionInfo;
		for ( ; ri != nullptr; ri = ri->m_Next )
		{
			// ignore abstract classes
			if ( ri->IsAbstract() )
			{
				continue;
			}

			// Serialize a default instance to a MemoryStream 
			MemoryStream ms;
			{
				// Create and serialize default instance
				if ( ri->IsObject() )
				{
					RefObject * object = ri->CreateObject();
					{
						TextWriter tw( ms );
						tw.Write( object );
					}
					FDELETE( object );
				}
				else
				{
					ASSERT( ri->IsStruct() )
					Struct * str = ri->CreateStruct();
					{
						TextWriter tw( ms );
						tw.Write( str, ri );
					}
					FDELETE( str );
				}
			}

			AStackString<> fileName; 
			fileName.Format( "..\\Data\\Reflection\\.Definitions\\%s.definition", ri->GetTypeName() );

			// avoid writing file if not changed

			// Try to open existing file
			FileStream f;
			if ( f.Open( fileName.Get(), FileStream::READ_ONLY ) )
			{
				// read content
				const uint64_t fileSize = f.GetFileSize();
				if ( fileSize == ms.GetSize() )
				{
					AutoPtr< char > mem( (char *)Alloc( (size_t)fileSize ) );
					if ( f.Read( mem.Get(), (size_t)fileSize ) == fileSize )
					{
						if ( memcmp( mem.Get(), ms.GetData(), (size_t)fileSize ) == 0 )
						{
							continue; // definition has not changed
						}
					}
				}
				f.Close();
			}

			// Definition changed - try to save it

			int result = 0;
			AutoPtr< char > memOut;
			AutoPtr< char > memErr;
			uint32_t memOutSize;
			uint32_t memErrSize;

			// existing definition?
			if ( FileIO::FileExists( fileName.Get() ) )
			{
				// existing - need to open for edit?
				if ( FileIO::GetReadOnly( fileName ) )
				{
					AStackString<> args( "edit " );
					args += fileName;
					Process p;
					if ( p.Spawn( "p4", args.Get(), nullptr, nullptr ) )
					{
						p.ReadAllData( memOut, &memOutSize, memErr, &memErrSize );
						result = p.WaitForExit();
					}
				}
			}
			else
			{
				// new - open for add
				AStackString<> args( "add " );
				args += fileName;
				Process p;
				if ( p.Spawn( "p4", args.Get(), nullptr, nullptr ) )
				{
					p.ReadAllData( memOut, &memOutSize, memErr, &memErrSize );
					result = p.WaitForExit();
				}
			}

			if ( result == 0 )
			{ 
				if ( f.Open( fileName.Get(), FileStream::WRITE_ONLY ) )
				{
					if ( f.Write( ms.GetData(), ms.GetSize() ) == ms.GetSize() )
					{
						continue; // all ok!
					}
				}
			}

			// PROBLEM!
			OUTPUT( "Error writing definition '%s'\n", fileName.Get() );
			if ( result != 0 )
			{
				OUTPUT( "Perforce error: %s\n", memErr.Get() );
			}
			++numProblems;
		}
		if ( numProblems > 0 )
		{
			FATALERROR( "Problem writing %u definition(s).\n", numProblems );
		}
		return ( numProblems == 0 );
	}