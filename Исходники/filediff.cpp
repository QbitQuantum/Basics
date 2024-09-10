bool rab::CreateDiffFile( Options const& options, DiffEncoders const &diffEncoders, FileInfo& fileInfo, 
	Path_t const& fullNew, Path_t const& fullOld, Path_t const& relativeTemp, 
	dung::MemoryBlock const& newFile, dung::MemoryBlock const& oldFile, PackageOutput_t &package, LogOutput_t& out )
{
	Path_t fullTemp = relativeTemp.filename();

	if( options.produceTemp )
	{
		fullTemp = options.pathToTemp / relativeTemp;
		fs::create_directories( fullTemp.parent_path() );
	}

	dung::DiffEncoder_i* pEncoder = diffEncoders.FindEncoder( fileInfo.name, fileInfo.diffMethod );
	if( pEncoder != NULL )
	{		
		out << "Encoding " << fileInfo.diffMethod << " diff file " << GenericString( relativeTemp ) << std::endl;
		
		dung::MemoryBlock deltaFile;
		if( !pEncoder->EncodeDiffMemoryBlock( newFile.pBlock, newFile.size, oldFile.pBlock, oldFile.size, deltaFile.pBlock, deltaFile.size ) )
		{
			_tstring errorMessage;
			pEncoder->GetErrorMessage( errorMessage );
			out << "Encoding error: " << errorMessage << std::endl;
			return false;
		}

		if( options.produceTemp )
		{
			if( !WriteWholeFile( fullTemp.wstring(), deltaFile ) )
			{
				out << "Can't write file " << GenericString( fullTemp ) << std::endl;
				return false;
			}
		}

		if( !package.WriteFile( GenericString( relativeTemp ), deltaFile.pBlock, deltaFile.size ) )
		{
			out << "Can't write file " << GenericString( relativeTemp ) << " to package. Size=" << deltaFile.size << std::endl;
			return false;
		}
	}
	else
	{
		dung::DiffEncoderExternal_i* pExternalEncoder = diffEncoders.FindExternalEncoder( fileInfo.name, fileInfo.diffMethod );
		if( pExternalEncoder != NULL )
		{
			out << "Encoding " << fileInfo.diffMethod << " diff file " << GenericString( relativeTemp ) << std::endl;
			if( !pExternalEncoder->EncodeDiffFile( GenericString(fullNew).c_str(), GenericString(fullOld).c_str(), GenericString(fullTemp).c_str() ) )
			{
				_tstring errorMessage;
				pExternalEncoder->GetErrorMessage( errorMessage );
				out << "Encoding error: " << errorMessage << std::endl;
				return false;
			}

			dung::MemoryBlock deltaFile;
			if( !ReadWholeFile( fullTemp.generic_string(), deltaFile ) )
			{
				out << "Can't read file " << GenericString(fullTemp) << std::endl;
				return false;
			}

			if( !options.produceTemp )
				fs::remove( fullTemp );

			if( !package.WriteFile( GenericString(relativeTemp), deltaFile.pBlock, deltaFile.size ) )
			{
				out << "Can't write file " << GenericString(relativeTemp) << " to package. Size=" << deltaFile.size << std::endl;
				return false;
			}
		}
		else
		{
			out << "Can't file encoder for file " << fileInfo.name << std::endl;
			return false;
		}				
	}

	return true;
}