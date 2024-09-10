objrtn	InputStream_initialize(void)
{
	static  CRITICALSECTION  cs;
	static  int volatile once = 0;

	ENTERCRITICALSECTION(_CI_CS_);
	if (!once) {
		INITIALIZECRITICALSECTION(cs);
		once = 1;
	}
	LEAVECRITICALSECTION(_CI_CS_);

	ENTERCRITICALSECTION(cs);

	if (InputStream_c) {
		LEAVECRITICALSECTION(cs);
		return InputStream_c;
	}
	INHIBIT_THREADER;
	InputStream_c = gNewClass(Class, "InputStream", sizeof(InputStream_iv_t), 0, END);
	cMethodFor(InputStream, gNewWithStr, InputStream_cm_gNewWithStr);
	cMethodFor(InputStream, gNew, InputStream_cm_gNew);
	iMethodFor(InputStream, gDispose, InputStream_im_gDispose);
	iMethodFor(InputStream, gGCDispose, InputStream_im_gGCDispose);
	iMethodFor(InputStream, gLineHasColon, InputStream_im_gLineHasColon);
	iMethodFor(InputStream, gNextToken, InputStream_im_gNextToken);
	iMethodFor(InputStream, gDeepDispose, InputStream_im_gDispose);

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return InputStream_c;
}