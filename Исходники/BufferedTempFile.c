objrtn	BufferedTempFile_initialize(void)
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

	if (BufferedTempFile_c) {
		LEAVECRITICALSECTION(cs);
		return BufferedTempFile_c;
	}
	INHIBIT_THREADER;
	BufferedTempFile_c = gNewClass(Class, "BufferedTempFile", sizeof(BufferedTempFile_iv_t), 0, END);
	cMethodFor(BufferedTempFile, gOpenTempFile, BufferedTempFile_cm_gOpenTempFile);
	iMethodFor(BufferedTempFile, gFlush, BufferedTempFile_im_gFlush);
	iMethodFor(BufferedTempFile, gRetreat, BufferedTempFile_im_gRetreat);
	iMethodFor(BufferedTempFile, gPosition, BufferedTempFile_im_gPosition);
	iMethodFor(BufferedTempFile, gLength, BufferedTempFile_im_gLength);
	iMethodFor(BufferedTempFile, gWrite, BufferedTempFile_im_gWrite);
	iMethodFor(BufferedTempFile, gEndOfStream, BufferedTempFile_im_gEndOfStream);
	iMethodFor(BufferedTempFile, gSeek, BufferedTempFile_im_gSeek);
	iMethodFor(BufferedTempFile, gPointerValue, BufferedTempFile_im_gPointerValue);
	iMethodFor(BufferedTempFile, gAdvance, BufferedTempFile_im_gAdvance);
	iMethodFor(BufferedTempFile, gDispose, BufferedTempFile_im_gDispose);
	iMethodFor(BufferedTempFile, gName, BufferedTempFile_im_gName);
	iMethodFor(BufferedTempFile, gGets, BufferedTempFile_im_gGets);
	iMethodFor(BufferedTempFile, gGCDispose, BufferedTempFile_im_gGCDispose);
	iMethodFor(BufferedTempFile, gDeepDispose, BufferedTempFile_im_gDispose);
	iMethodFor(BufferedTempFile, gRead, BufferedTempFile_im_gRead);

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return BufferedTempFile_c;
}