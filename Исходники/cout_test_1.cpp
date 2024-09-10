int _tmain(int argc, _TCHAR* argv[])
{
	size_t max_num = 100000000;
	const int max_char_per_float = 10;
	const size_t buffer_element_count = 100000;
	size_t buffer_byte_size = buffer_element_count * (max_char_per_float + 5);
	char* write_buffer = new char[buffer_byte_size];
	HANDLE hFile = ::CreateFile(L"output.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, NULL);
	// std::ofstream output();
	for (size_t i=0; i < max_num / buffer_element_count; ++i) 
	{
		int buffer_position = 0;
		for (int k = 0; k < buffer_element_count; ++k)
		{
			char number_buffer[32];
			int pos = 0;
			int dec;
			int sign;
			float random = float(rand()) / RAND_MAX;
			_ecvt_s(number_buffer, random, max_char_per_float, &dec, &sign);
			if (sign)
			{
				write_buffer[buffer_position++] = '-';
			}
			while(pos<dec) 
			{ 
				write_buffer[buffer_position++] = number_buffer[pos++]; 
			}
			write_buffer[buffer_position++] = '.';
			while (number_buffer[pos])
			{
				write_buffer[buffer_position++] = number_buffer[pos++];
			}
			write_buffer[buffer_position++] = '\r';
			write_buffer[buffer_position++] = '\n';
		}
		DWORD bytes_written = 0;
		::WriteFile(hFile, write_buffer, buffer_position, &bytes_written, NULL);
	}

	::CloseHandle(hFile);
	return 0;
}