DWORD WINAPI RandomThreadProc(LPVOID lpParameter) 
{
	const int buffer_element_count = 30000;
	const int max_float_digits = 8;

	sfmt_t sfmt;
	sfmt_init_gen_rand(&sfmt, GetCurrentThreadId());
	uint32_t* randoms = (uint32_t*) _aligned_malloc(sizeof(uint32_t)*buffer_element_count, 64);

	bool done = false;

	WriteBuffer* write_buffer = new WriteBuffer(buffer_element_count, max_float_digits);
	// std::ofstream output();
	while (!done) 
	{
		// Prepare a block of numbers for writing.
		char* write_ptr = write_buffer->ptr_;

		sfmt_fill_array32(&sfmt, randoms, buffer_element_count);

		*(write_ptr++) = '0';
		*(write_ptr++) = '.';

		// Compute digits
		for (int k = 0; k < buffer_element_count; ++k)
		{
			// Format each float to string and append to buffer.
			// float random = float(rand()) / RAND_MAX;
			// float random = float(randoms[k]) / 4294967296.0f;
			// int fractional_part = random *  1000000000;
			// this turns the fractional part of the float back into usable integer.
#if 1
			float f1 = float(randoms[k]) / 429496.7296f;
			int d1 = int(f1);
			float f2 = (f1 - d1)*10000.0f;
			int d2 = int(f2 + 0.5f);
#else
			double f1 = double(randoms[k]) / 429496.7296;
			int d1 = int(f1);
			double f2 = (f1 - d1)*10000.0;
			int d2 = int(f2 + 0.5);
#endif
			// convert to string form.
			// we use a lookup table for this.
			uint32_t part_1 = *((uint32_t*)(g_x + d1));
			*((uint32_t*)(write_ptr)) = part_1;

			uint32_t part_2 = *((uint32_t*)(g_x + d2));
			*((int*)(write_ptr + 4)) = part_2;

			*((int*)(write_ptr + 8)) = '.0\n\r'; // order of chars reversed.
#ifdef _DEBUG
			printf("%.8lf => %s\n", double(randoms[k]) / 4294967296.0, write_ptr-2);
#endif
			write_ptr+=12;
		}
		// get rid of last 0.
		write_ptr-=2;
		// Compute how many bytes to write.
		write_buffer->useful_data_size_ =  write_ptr - write_buffer->ptr_;

		// Enqueue for writing.
		// while (write_buffer) {
			EnterCriticalSection(&g_write_queue_cs);
			/*if (g_write_queue.size() < kMaxQueue) 
			{
				g_write_queue.push(write_buffer);
				SetEvent(g_write_queue_has_more_data_event);
				write_buffer = NULL;
			} else 
			{
				// ops.
		    }*/
			g_total_bytes_written += write_buffer->useful_data_size_;
			done = g_done;
			if (done) 
			{
				DWORD bytes_written = 0;
				::WriteFile(g_hFile, write_buffer->ptr_, write_buffer->useful_data_size_, 
					&bytes_written, NULL);
			}
			LeaveCriticalSection(&g_write_queue_cs);
			/* if (write_buffer) {
				// slow down writing, queue is full
				// printf("S");
				WaitForSingleObject(g_write_queue_accepts_more_data_event, 10);
			}*/
		// }
	}

	_aligned_free(randoms);

	return 0;
}