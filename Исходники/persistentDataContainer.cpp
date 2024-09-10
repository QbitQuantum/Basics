void CPersistentDataContainer::_readFromFile(std::vector<std::string>& dataNames,std::vector<std::string>& dataValues)
{
	dataNames.clear();
	dataValues.clear();
	std::string filenameAndPath(VVarious::splitPath_path(VVarious::getModulePathAndFile())+VREP_SLASH+V_REP_SYSTEM_DIRECTORY_NAME+VREP_SLASH+_filename.c_str());
	if (VFile::doesFileExist(filenameAndPath))
	{
		try
		{
			VFile file(filenameAndPath,VFile::READ|VFile::SHARE_DENY_NONE);
			VArchive archive(&file,VArchive::LOAD);
			_serialize(archive,dataNames,dataValues);
			archive.close();
			file.close();
		}
		catch(VFILE_EXCEPTION_TYPE e)
		{
			// silent error since 3/2/2012: when the system folder dowesn't exist, we don't want an error!!    VFile::reportAndHandleFileExceptionError(e);
		}
	}
}