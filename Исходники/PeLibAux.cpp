	/**
	* Opens a PE file. The return type is either PeFile32 or PeFile64 object. If an error occurs the return
	* value is 0.
	* @param strFilename Name of a file.
	* @return Either a PeFile32 object, a PeFil64 object or 0.
	**/
	PeFile* openPeFile(const std::string& strFilename)
	{
		unsigned int type = getFileType(strFilename);
		
		if (type == PEFILE32)
		{
			return new PeFile32(strFilename);
		}
		else if (type == PEFILE64)
		{
			return new PeFile64(strFilename);
		}
		else
		{
			return 0;
		}
	}