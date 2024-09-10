/**
 * FIXME Verbose mode missing yet.
 */
static int do_list_contents(FILE *fp, char *out_f, int list_contents)
{
	int rc;
	struct stat st;
	uint32_t d, crc32, size, compressed_size;
	float ratio = 0.0;
	z_stream strm;
	uint8_t in[4096];
	uint8_t out[4096];
	gz_header head;
	uint8_t extra[64 * 1024];
	uint8_t comment[1024];
	uint8_t name[1024];
	int window_bits = 31;	/* GZIP */
	const char *mon[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
			      "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };

	rc = fstat(fileno(fp), &st);
	if (rc != 0)
		return rc;

	memset(&strm, 0, sizeof(strm));
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	rc = inflateInit2(&strm, window_bits);
	if (Z_OK != rc)
		return rc;

	strm.next_out = out;
	strm.avail_out = sizeof(out);
	strm.next_in = in;
	strm.avail_in = fread(in, 1, sizeof(in), fp);
	if (ferror(fp))
		return Z_ERRNO;

	head.extra = extra;
	head.extra_len = 0;
	head.extra_max = sizeof(extra);

	head.comment = comment;
	head.comm_max = sizeof(comment);

	head.name = name;
	head.name_max = sizeof(name);

	rc = inflateGetHeader(&strm, &head);
	if (Z_OK != rc) {
		fprintf(stderr, "err: Cannot read gz header! rc=%d\n", rc);
		return rc;
	}

	rc = inflate(&strm, Z_BLOCK);
	if (Z_OK != rc) {
		fprintf(stderr, "err: inflate(Z_BLOCK) failed rc=%d\n", rc);
		return rc;
	}

	if (head.done == 0) {
		fprintf(stderr, "err: gzip header not entirely decoded! "
			"total_in=%ld total_out=%ld head.done=%d\n",
			strm.total_in, strm.total_out, head.done);
		return Z_DATA_ERROR;
	}

	rc = fseek(fp, st.st_size - 2 * sizeof(uint32_t), SEEK_SET);
	if (rc != 0)
		return rc;

	rc = fread(&d, sizeof(d), 1, fp);
	if (rc != 1)
		return -1;
	crc32 = __le32_to_cpu(d);

	rc = fread(&d, sizeof(d), 1, fp);
	if (rc != 1)
		return -1;
	size = __le32_to_cpu(d);

	/* Compressed size is total file size reduced by gzip header
	   size and 8 bytes for the gzip trailer. */
	compressed_size = st.st_size - strm.total_in - 8;
	if (size)
		ratio = 100 - (float)compressed_size * 100 / size;

	if (!verbose) {
		fprintf(stderr,
			"         compressed        uncompressed  ratio "
			"uncompressed_name\n"
			"%19lld %19d  %2.2f%% %s\n",
			(long long)st.st_size, size, ratio,
			out_f);
	} else {
		time_t t = time(NULL);
		struct tm *tm = localtime(&t);
		/* (const time_t *)&head.time */

		fprintf(stderr, "method  crc     date  time           "
			"compressed        uncompressed  ratio "
			"uncompressed_name\n"
			"%s %x %s %2d %d:%d %19lld %19d  %2.2f%% %s\n",
			"defla", crc32,
			mon[tm->tm_mon], tm->tm_mday, tm->tm_hour, tm->tm_min,
			(long long)st.st_size, size, ratio,
			out_f);
	}

	if (list_contents > 1)
		do_print_gzip_hdr(&head, stderr);

	return 0;
}