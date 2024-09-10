UBool findPattern()
{
	UErrorCode status = U_ZERO_ERROR;
	int32_t offset = usearch_next(search, &status);
	if (offset == USEARCH_DONE) {
		fprintf(stdout, "Pattern not found in source\n");
	}
	while (offset != USEARCH_DONE) {
		fprintf(stdout, "Pattern found at offset %d size %d\n", offset,
				usearch_getMatchedLength(search));
		offset = usearch_next(search, &status);
	}
	if (U_FAILURE(status)) {
		fprintf(stderr, "Error in searching for pattern %d\n", status);
		return FALSE;
	}
	fprintf(stdout, "End of search\n");
	return TRUE;
}