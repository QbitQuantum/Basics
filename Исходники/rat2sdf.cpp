static void dumpOptions(IMG_DeepShadow &fp) {
	const UT_Options * opt;
	UT_WorkBuffer wbuf;
	if (opt = fp.getTBFOptions()) {
		wbuf.strcpy("DSM Options: ");
		opt->appendPyDictionary(wbuf);
		printf("%s\n", wbuf.buffer());
	}
}