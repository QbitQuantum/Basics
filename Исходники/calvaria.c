static void dump_bytes(FILE *outstream, const void *_buf, size_t size)
{
	const char *buf = _buf;
	size_t i, ascii_cnt = 0;
	char ascii[17] = { 0, };

	for (i = 0; i < size; i++) {
		if (i % 16 == 0) {
			if (i != 0) {
				fprintf(outstream, "  |%s|\n", ascii);
				ascii[0] = 0;
				ascii_cnt = 0;
			}
			fprintf(outstream, "[%04X]: ", (unsigned int)i);
		}
		fprintf(outstream, " %02X", buf[i] & 0xFF);
		ascii[ascii_cnt] = toAscii(buf[i]);
		ascii[ascii_cnt + 1] = 0;
		ascii_cnt++;
	}
	if (ascii[0]) {
		if (size % 16) {
			for (i = 0; i < 16 - (size % 16); i++)
				fprintf(outstream, "   ");
		}
		fprintf(outstream, "  |%s|\n", ascii);
	}
}