int xpfurandom_get_random_data(void** data, uint32_t size, void* win_alg_handle, xpfurandom_settings* s){
	NTSTATUS st;
	st = BCryptGenRandom(win_alg_handle, *data, size, 0);
	switch (st){
		case STATUS_SUCCESS:break;
		case STATUS_INVALID_HANDLE: {
			fprintf(stderr, "XPFUrandom: BCryptGenRandom failed: invalid algorithm handle(STATUS_INVALID_HANDLE)\n");
			return FAIL;
		}break;
		case STATUS_INVALID_PARAMETER: {
			fprintf(stderr, "XPFUrandom: BCryptGenRandom failed: invalid parameter(STATUS_INVALID_PARAMETER)\n");
			return FAIL;
		}break;
	}
	if (s->file_out) {
		st = fwrite(*data, 1, size, s->file_out);
		if (st != size) {
			fprintf(stderr, "XPFUrandom: fwrite failed\n");
			return FAIL;
		}
		st = fflush(s->file_out);
		if (st) {
			fprintf(stderr, "XPFUrandom: fflush failed: %s\n",strerror(errno));
			return FAIL;
		}
	}
	return OK;
}