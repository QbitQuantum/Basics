	File::File(std::string filePath){
		m_hasExtension = GetFileNameAndExtension(filePath, m_name, m_extension);
		m_size = GetFileSize(filePath);
	}