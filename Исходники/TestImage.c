static void* read_image(const char* src, size_t* size)
{
	int success = 0;
	void* a = NULL;
	INT64 src_size;
	FILE* fsrc = fopen(src, "rb");

	if (!fsrc)
	{
		fprintf(stderr, "Failed to open file %s\n", src);
		goto cleanup;
	}

	if (_fseeki64(fsrc, 0, SEEK_END))
	{
		fprintf(stderr, "Failed to seek to file end\n");
		goto cleanup;
	}

	src_size = _ftelli64(fsrc);
	if (src_size < 0)
	{
		fprintf(stderr, "Invalid file position %"PRId64"\n", src_size);
		goto cleanup;
	}
	if (_fseeki64(fsrc, 0, SEEK_SET))
	{
		fprintf(stderr, "Failed to seek to SEEK_SET\n");
		goto cleanup;
	}

	a = malloc((size_t)src_size);

	if (!a)
	{
		fprintf(stderr, "Failed malloc %"PRId64" bytes\n", src_size);
		goto cleanup;
	}

	if (fread(a, sizeof(char), (size_t)src_size, fsrc) != (size_t)src_size)
	{
		fprintf(stderr, "Failed read %"PRId64" bytes\n", src_size);
		goto cleanup;
	}

	success = 1;
	*size = src_size;
cleanup:

	if (a && !success)
	{
		free(a);
		a = NULL;
	}

	if (fsrc)
		fclose(fsrc);

	return a;
}