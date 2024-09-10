bool rab::WriteRegistry( Options const& options, Config const& config, FolderInfo& rootFolder, PackageOutput_t& package, LogOutput_t& out )
{
	out << "Creating registry file..." << std:: endl;

	_tstringstream stringStream;
	OutputContext outputContext( stringStream, out );

	if( !options.newVersion.empty() )
		outputContext.stream << _T("new_version=") << quote << options.newVersion << quote << endl;
	
	if( !options.oldVersion.empty() )
		outputContext.stream << _T("old_version=") << quote << options.oldVersion << quote << endl;

	Path_t relativePath;
	WriteRegistryFolders( options, config, FolderInfo::FolderInfos_t( 1, &rootFolder ), relativePath, outputContext );

	_tstring fileContent = stringStream.str();
	std::string fileContentUtf8 = loc::conv::utf_to_utf<char>( fileContent );

	if( !package.WriteFile( dung::REGISTRY_FILENAME, fileContentUtf8.c_str(), fileContentUtf8.size() ) )
	{
		out << "Can't write file " << dung::REGISTRY_FILENAME << " to package" << std::endl;
		return false;
	}

	if( options.produceTemp )
	{
		std::ofstream file ( dung::REGISTRY_FILENAME, std::ios::out|std::ios::binary|std::ios::trunc );
		if( !file.is_open() )
		{
			out << "Can't create " << dung::REGISTRY_FILENAME << std::endl;
			return false;
		}

		file.write( fileContentUtf8.c_str(), fileContentUtf8.size() );

		file.close();
	}

	return true;
}