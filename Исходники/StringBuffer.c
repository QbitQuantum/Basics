void StringBuffer_free(T *S) {
        assert(S && *S);
	FREE((*S)->buffer);
        FREE(*S);
}