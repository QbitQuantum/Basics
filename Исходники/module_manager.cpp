	CError CModuleManager::load_from_integra_file( const string &integra_file, guid_set &new_embedded_modules )
	{
		unzFile unzip_file;
		unz_file_info file_info;
		char file_name[ CStringHelper::string_buffer_length ];
		char *temporary_file_name;
		FILE *temporary_file;
        string::size_type implementation_directory_length;
		unsigned char *copy_buffer;
		int bytes_read;
		int total_bytes_read;
		int bytes_remaining;
		GUID loaded_module_id;
		CError CError = CError::SUCCESS;

		new_embedded_modules.clear();

		unzip_file = unzOpen( integra_file.c_str() );
		if( !unzip_file )
		{
			INTEGRA_TRACE_ERROR << "Couldn't open zip file: " << integra_file;
			return CError::FAILED;
		}

		implementation_directory_length = CFileIO::implementation_directory_name.length();

		if( unzGoToFirstFile( unzip_file ) != UNZ_OK )
		{
			INTEGRA_TRACE_ERROR << "Couldn't iterate contents: " << integra_file;
			unzClose( unzip_file );
			return CError::FAILED;
		}

		copy_buffer = new unsigned char[ CFileIO::data_copy_buffer_size ];

		do
		{
			temporary_file_name = NULL;
			temporary_file = NULL;

			if( unzGetCurrentFileInfo( unzip_file, &file_info, file_name, CStringHelper::string_buffer_length, NULL, 0, NULL, 0 ) != UNZ_OK )
			{
				INTEGRA_TRACE_ERROR << "Couldn't extract file info: " << integra_file;
				continue;
			}

			if( strlen( file_name ) <= implementation_directory_length || string( file_name ).substr( 0, implementation_directory_length ) != CFileIO::implementation_directory_name )
			{
				/* skip file not in node directory */
				continue;
			}

			temporary_file_name = tempnam( m_server.get_scratch_directory().c_str(), "embedded_module" );
			if( !temporary_file_name )
			{
				INTEGRA_TRACE_ERROR << "couldn't generate temporary filename";
				CError = CError::FAILED;
				continue;
			}

			temporary_file = fopen( temporary_file_name, "wb" );
			if( !temporary_file )
			{
				INTEGRA_TRACE_ERROR << "couldn't open temporary file: " << temporary_file_name;
				CError = CError::FAILED;
				goto CLEANUP;
			}

			if( unzOpenCurrentFile( unzip_file ) != UNZ_OK )
			{
				INTEGRA_TRACE_ERROR << "couldn't open zip contents: " << file_name;
				CError = CError::FAILED;
				goto CLEANUP;
			}

			total_bytes_read = 0;
			while( total_bytes_read < file_info.uncompressed_size )
			{
				bytes_remaining = file_info.uncompressed_size - total_bytes_read;
				assert( bytes_remaining > 0 );

				bytes_read = unzReadCurrentFile( unzip_file, copy_buffer, MIN( CFileIO::data_copy_buffer_size, bytes_remaining ) );
				if( bytes_read <= 0 )
				{
					INTEGRA_TRACE_ERROR << "Error decompressing file";
					CError = CError::FAILED;
					goto CLEANUP;
				}

				fwrite( copy_buffer, 1, bytes_read, temporary_file );

				total_bytes_read += bytes_read;
			}

			fclose( temporary_file );
			temporary_file = NULL;

			if( load_module( temporary_file_name, CInterfaceDefinition::MODULE_EMBEDDED, loaded_module_id ) )
			{
				new_embedded_modules.insert( loaded_module_id );

				store_module( loaded_module_id );
			}

			CLEANUP:

			if( temporary_file )
			{
				fclose( temporary_file );
			}

			if( temporary_file_name )
			{
				CFileHelper::delete_file( temporary_file_name );
				delete[] temporary_file_name;
			}

			unzCloseCurrentFile( unzip_file );
		}
		while( unzGoToNextFile( unzip_file ) != UNZ_END_OF_LIST_OF_FILE );

		unzClose( unzip_file );

		delete[] copy_buffer;

		return CError;
	}