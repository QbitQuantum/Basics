int _tmain(int argc, _TCHAR* argv[])
{
	const size_t max_num = 100000000;
	const int buffer_element_count = 10000;
	const int max_float_digits = 8;
	
	// Init critical section;
	InitializeCriticalSection(&g_write_queue_cs);
	g_write_queue_has_more_data_event = CreateEvent(NULL, FALSE, FALSE, NULL);
	g_write_queue_accepts_more_data_event = CreateEvent(NULL, FALSE, TRUE, NULL);

	HANDLE hFile = ::CreateFile(L"output.txt", GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE) 
	{
		printf("Oppps");
		exit(-1);
	}

	// Launch a writer thread.
	HANDLE hThread = CreateThread(NULL, 0, &WriteThreadProc, hFile,0, 0);

	sfmt_t sfmt;
	sfmt_init_gen_rand(&sfmt, 1234);
	uint32_t* randoms = (uint32_t*) _aligned_malloc(sizeof(uint32_t)*buffer_element_count, 32);

	g_begin_ticks = GetTickCount64();

	// std::ofstream output();
	int finish = max_num / buffer_element_count;
	for (size_t i=0; i < finish; ++i) 
	{
		// Prepare a block of numbers for writing.
		WriteBuffer* write_buffer = new WriteBuffer(buffer_element_count, max_float_digits);
		char* write_ptr = write_buffer->ptr_;

		sfmt_fill_array32(&sfmt, randoms, buffer_element_count);

		for (int k = 0; k < buffer_element_count; ++k)
		{
			// Format each float to string and append to buffer.
			// float random = float(rand()) / RAND_MAX;
			float random = float(randoms[k]) / 4294967296.0f;
			write_ptr += modp_dtoa(random, write_ptr, max_float_digits);
			*(write_ptr++) = '\r';
			*(write_ptr++) = '\n';
		}
		// Compute how many bytes to write.
		write_buffer->useful_data_size_ =  write_ptr - write_buffer->ptr_;

		// Enqueue for writing.
		while (write_buffer) {
			EnterCriticalSection(&g_write_queue_cs);
			if (g_write_queue.size() < kMaxQueue) 
			{
				// ops.
				g_write_queue.push(write_buffer);
				SetEvent(g_write_queue_has_more_data_event);
				write_buffer = NULL;
			}
			LeaveCriticalSection(&g_write_queue_cs);
			if (write_buffer) {
				// slow down writing, queue is full
				printf("S");
				WaitForSingleObject(g_write_queue_accepts_more_data_event, 200);
			}
		}
	}

	g_end_ticks = GetTickCount64();

	// Let the writing thread know we are done.
	EnterCriticalSection(&g_write_queue_cs);
	g_done = true;
	LeaveCriticalSection(&g_write_queue_cs);
	SetEvent(g_write_queue_has_more_data_event);
	// Wait for writing thread to finish.
	WaitForSingleObject(hThread, INFINITE);

	_aligned_free(randoms);

	__int64 delta = g_end_ticks - g_begin_ticks;

	printf("Speed %f Mb per sec\n", (g_total_bytes_written * 1000.0) / (1024.0 * 1024 * delta));

	char c;
	scanf("%c", &c);
	::CloseHandle(hFile);
	return 0;
}