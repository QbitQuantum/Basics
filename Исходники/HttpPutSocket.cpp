void HttpPutSocket::SetFile(const std::string& file)
{
	//struct stat st;
	
	// Added by Amir Krifa
	std::ifstream f;
	f.open(file.c_str(), std::ios_base::binary | std::ios_base::in);
	//if (!f.good() || f.eof() || !f.is_open()) { return 0; }
	
	if (!f.good() || f.eof() || !f.is_open()) 
	{ 
		Handler().LogError(this, "SetFile", Errno, StrError(Errno), LOG_LEVEL_FATAL);
		SetCloseAndDelete();
	}else
	{
		f.seekg(0, std::ios_base::beg);
		std::ifstream::pos_type begin_pos = f.tellg();
		f.seekg(0, std::ios_base::end);
		m_filename = file;
		m_content_length = static_cast<off_t>(f.tellg() - begin_pos);
	}
	
	//if (!stat(file.c_str(), &st))
	//{
	//	m_filename = file;
	//	m_content_length = st.st_size;
	//}
	//else
	//{
	//	Handler().LogError(this, "SetFile", Errno, StrError(Errno), LOG_LEVEL_FATAL);
	//	SetCloseAndDelete();
	//}
}