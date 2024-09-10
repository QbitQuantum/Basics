void put_check_for_nan(const CppAD::vector<Base>& vec, std::string& file_name)
{
	size_t char_size       = sizeof(Base) * vec.size();
	const char* char_ptr   = reinterpret_cast<const char*>( vec.data() );
# if CPPAD_HAS_MKSTEMP
	char pattern[] = "/tmp/fileXXXXXX";
	int fd = mkstemp(pattern);
	file_name = pattern;
	write(fd, char_ptr, char_size);
	close(fd);
# else
# if CPPAD_HAS_TMPNAM_S
		std::vector<char> name(L_tmpnam_s);
		if( tmpnam_s( name.data(), L_tmpnam_s ) != 0 )
		{	CPPAD_ASSERT_KNOWN(
				false,
				"Cannot create a temporary file name"
			);
		}
		file_name = name.data();
# else
		file_name = tmpnam( CPPAD_NULL );
# endif
	std::fstream file_out(file_name.c_str(), std::ios::out|std::ios::binary );
	file_out.write(char_ptr, char_size);
	file_out.close();
# endif
	return;
}