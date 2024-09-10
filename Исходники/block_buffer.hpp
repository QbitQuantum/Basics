	void write(elem_t* dest, size_t dest_size, const elem_t* src, size_t max_count)
	{
		memcpy_s(dest, dest_size, src, max_count);
		write_pos += max_count;
		total_size += max_count;
	}