void f_local_fwriter::set_file_size (uint64_t filsize)
{
	open_file ();
#ifdef _WIN32
	uint64_t offset = this->seek_file (filsize, FILE_BEGIN);
	if (offset != filsize) {
		std::string errmsg = fmt_string ("Can't seek file %s(%s)."
			, f_name_.c_str (), error_msg ().c_str ());
		THROW_XDELTA_EXCEPTION (errmsg);
	}
	BOOL success = SetEndOfFile (f_handle_);
#else
	int success = ftruncate (f_fd_, filsize);
	success = success == 0 ? 1 : 0;
#endif
	if (!success) {
		std::string errmsg = fmt_string ("Can't set file  %s's size.", f_name_.c_str ());
		THROW_XDELTA_EXCEPTION (errmsg);
	}	
}