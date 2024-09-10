static int
narc_read(void *buf, FILE *fp)
{
	struct NARC *self = buf;
	assert(self != NULL);

	/* For efficiency, we stash the file pointer so we can lazily load
	 * the contained files - although i'm not sure this is the best
	 * solution */
	self->fp = fp;

	FREAD(fp, &self->header, 1);

	assert(self->header.chunk_count == 3);

	/* read the FATB chunk */
	FREAD(fp, &self->fatb.header, 1);
	assert(self->fatb.header.magic == (magic_t)'FATB');
	if (ferror(fp) || feof(fp)) {
		return FAIL;
	}

	CALLOC(self->fatb.records, self->fatb.header.file_count);

	if (self->fatb.records == NULL) {
		return NOMEM;
	}

	FREAD(fp, self->fatb.records, self->fatb.header.file_count);
	if (ferror(fp) || feof(fp)) {
		return FAIL;
	}


	/* skip the FNTB chunk */
	FREAD(fp, &self->fntb.header, 1);
	assert(self->fntb.header.magic == (magic_t)'FNTB');
	if (ferror(fp) || feof(fp)) {
		return FAIL;
	}
	fseeko(self->fp, (off_t)(self->fntb.header.size - sizeof(self->fntb.header)), SEEK_CUR);

	/* set the data offset */
	struct { magic_t magic; u32 size; } fimg_header;

	FREAD(fp, &fimg_header, 1);
	assert(fimg_header.magic == (magic_t)'FIMG');
	if (ferror(fp) || feof(fp)) {
		return FAIL;
	}

	self->data_offset = ftello(fp);
	if (self->data_offset == -1) {
		return FAIL;
	}

	return OKAY;
}