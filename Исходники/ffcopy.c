int Fcopy(FILE * const fdst, FILE * const fsrc)
{	byte *buf;
	size_t len, i;
	int err;

	DBG_ENTER("Fcopy", Suppl_supplio)

	assert(fsrc);
	assert(fdst);

	chkHeap
	if(Fmaxbuf(&buf, &len))
		DBG_RETURN_I( 3)				/* out of memory */

	chkHeap
	while((err = Fcopybuf(fdst, fsrc, buf, len, &i)) == 0);

	chkHeap
	free(buf);
		/*	err == 0 --> impossible
			err == 1 --> read error, this is OK, if read had hit EOF
		*/
	chkHeap
	DBG_RETURN_BI(err < 2? Feof(fsrc) == 0: err)
}