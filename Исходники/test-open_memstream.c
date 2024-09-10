static void
simple_tests(void)
{
	static const char zerobuf[] =
	    { 'f', 'o', 'o', 0, 0, 0, 0, 'b', 'a', 'r', 0 };
	char c;
	FILE *fp;

	fp = open_memstream(&buf, NULL);
	if (fp != NULL)
		errx(1, "did not fail to open stream");
	else if (errno != EINVAL)
		err(1, "incorrect error for bad length pointer");
	fp = open_memstream(NULL, &len);
	if (fp != NULL)
		errx(1, "did not fail to open stream");
	else if (errno != EINVAL)
		err(1, "incorrect error for bad buffer pointer");
	fp = open_memstream(&buf, &len);
	if (fp == NULL)
		err(1, "failed to open stream");
	fflush(fp);
	assert_stream("");
	if (fwide(fp, 0) >= 0)
		printf("stream is not byte-oriented\n");

	fprintf(fp, "fo");
	fflush(fp);
	assert_stream("fo");
	fputc('o', fp);
	fflush(fp);
	assert_stream("foo");
	rewind(fp);
	fflush(fp);
	assert_stream("");
	fseek(fp, 0, SEEK_END);
	fflush(fp);
	assert_stream("foo");

	/*
	 * Test seeking out past the current end.  Should zero-fill the
	 * intermediate area.
	 */
	fseek(fp, 4, SEEK_END);
	fprintf(fp, "bar");
	fflush(fp);

	/*
	 * Can't use assert_stream() here since this should contain
	 * embedded null characters.
	 */
	if (len != 10)
		printf("bad length %zd for zero-fill test\n", len);
	else if (memcmp(buf, zerobuf, sizeof(zerobuf)) != 0)
		printf("bad buffer for zero-fill test\n");

	fseek(fp, 3, SEEK_SET);
	fprintf(fp, " in ");
	fflush(fp);
	assert_stream("foo in ");
	fseek(fp, 0, SEEK_END);
	fflush(fp);
	assert_stream("foo in bar");

	rewind(fp);
	if (fread(&c, sizeof(c), 1, fp) != 0)
		printf("fread did not fail\n");
	else if (!ferror(fp))
		printf("error indicator not set after fread\n");
	else
		clearerr(fp);

	fseek(fp, 4, SEEK_SET);
	fprintf(fp, "bar baz");
	fclose(fp);
	assert_stream("foo bar baz");
	free(buf);
}