DLL_EXPIMP bwt_size_t CALL_CONV bwt(void* const void_data, const bwt_size_t n)
{
	if(!void_data || n < 2) return 0;

	unsigned char* __restrict data = void_data;
	bwt_size_t i, index = n;
	struct bwt_info_t data_info;
	data_info.rotations = malloc(n * 2 - 1);
	bwt_size_t* __restrict positions = malloc(sizeof(bwt_size_t) * n);

	memcpy(data_info.rotations, data, n);
	memcpy(data_info.rotations + n, data, n - 1);
	data_info.len = n;

	positions += n;
	while((*(--positions) = --index));

#ifdef __linux__
	qsort_r(positions, n, sizeof(bwt_size_t), bwt_cmp, &data_info);
#elif defined(__APPLE__)
	qsort_r(positions, n, sizeof(bwt_size_t), &data_info, bwt_cmp);
#elif defined(_WIN32)
	qsort_s(positions, n, sizeof(bwt_size_t), bwt_cmp, &data_info);
#endif

	for(i = 0; i < n; i++)
	{
		*data++ = data_info.rotations[(*positions + n - 1) % n];
		if(!*positions++) index = i;
	}

	free(positions - n);
	free(data_info.rotations);

	return index;
}