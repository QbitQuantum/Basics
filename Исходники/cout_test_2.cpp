int _tmain(int argc, _TCHAR* argv[])
{
	const size_t max_num = 100000000;
	const int buffer_element_count = 10000;
	const int max_float_digits = 10;
	
	// Init critical section;
	InitializeCriticalSection(&g_write_queue_cs);

	HANDLE hFile = ::CreateFile(L"output.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) 
	{
		printf("Oppps");
		exit(-1);
	}

	// Launch a writer thread.
	HANDLE hThread = CreateThread(NULL, 0, &WriteThreadProc, hFile,0, 0);

	// std::ofstream output();
	for (size_t i=0; i < max_num / buffer_element_count; ++i) 
	{
		// Prepare a block of numbers for writing.
		WriteBuffer* write_buffer = new WriteBuffer(buffer_element_count, max_float_digits);
		char* write_ptr = write_buffer->ptr_;
		for (int k = 0; k < buffer_element_count; ++k)
		{
			// Format each float to string and append to buffer.
			char number_micro_buffer[32];
			int pos = 0;
			int dec;
			int sign;
			float random = float(rand()) / RAND_MAX;
			_ecvt_s(number_micro_buffer, random, max_float_digits, &dec, &sign);

			if (sign)
			{
				*(write_ptr++) = '-';
			}
			if (dec <=0) {
				*(write_ptr++) = '0';
			}
			while(pos<dec) 
			{ 
				*(write_ptr++) = number_micro_buffer[pos++]; 
			}
			*(write_ptr++) = '.';
			while (number_micro_buffer[pos])
			{
				*(write_ptr++) = number_micro_buffer[pos++];
			}
			*(write_ptr++) = '\r';
			*(write_ptr++) = '\n';
		}
		// Compute how many bytes to write.
		write_buffer->useful_data_size_ = write_ptr - write_buffer->ptr_;

		// Enqueue for writing.
		EnterCriticalSection(&g_write_queue_cs);
		g_write_queue.push(write_buffer);
		LeaveCriticalSection(&g_write_queue_cs);
	}

	g_done = true;
	WaitForSingleObject(hThread, INFINITE);

	::CloseHandle(hFile);
	return 0;
}