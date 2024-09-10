objrtn	UnsignedShortInteger_initialize(void)
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

	if (UnsignedShortInteger_c) {
		LEAVECRITICALSECTION(cs);
		return UnsignedShortInteger_c;
	}
	INHIBIT_THREADER;
	Number_initialize();
	if (UnsignedShortInteger_c)  {
		ENABLE_THREADER;
		LEAVECRITICALSECTION(cs);
		return UnsignedShortInteger_c;
	}
	UnsignedShortInteger_c = gNewClass(Class, "UnsignedShortInteger", sizeof(UnsignedShortInteger_iv_t), 0, Number, END);
	cMethodFor(UnsignedShortInteger, gNewWithUnsigned, UnsignedShortInteger_cm_gNewWithUnsigned);
	iMethodFor(UnsignedShortInteger, gUnsignedShortValue, UnsignedShortInteger_im_gUnsignedShortValue);
	iMethodFor(UnsignedShortInteger, gChangeDoubleValue, UnsignedShortInteger_im_gChangeDoubleValue);
	iMethodFor(UnsignedShortInteger, gDoubleValue, UnsignedShortInteger_im_gDoubleValue);
	iMethodFor(UnsignedShortInteger, gCompare, UnsignedShortInteger_im_gCompare);
	iMethodFor(UnsignedShortInteger, gChangeLongValue, UnsignedShortInteger_im_gChangeLongValue);
	iMethodFor(UnsignedShortInteger, gChangeShortValue, UnsignedShortInteger_im_gChangeShortValue);
	iMethodFor(UnsignedShortInteger, gShortValue, UnsignedShortInteger_im_gShortValue);
	iMethodFor(UnsignedShortInteger, gPointerValue, UnsignedShortInteger_im_gPointerValue);
	iMethodFor(UnsignedShortInteger, gCharValue, UnsignedShortInteger_im_gCharValue);
	iMethodFor(UnsignedShortInteger, gStringRepValue, UnsignedShortInteger_im_gStringRepValue);
	iMethodFor(UnsignedShortInteger, gChangeUShortValue, UnsignedShortInteger_im_gChangeUShortValue);
	iMethodFor(UnsignedShortInteger, gHash, UnsignedShortInteger_im_gHash);
	iMethodFor(UnsignedShortInteger, gChangeValue, UnsignedShortInteger_im_gChangeValue);
	iMethodFor(UnsignedShortInteger, gLongValue, UnsignedShortInteger_im_gLongValue);
	iMethodFor(UnsignedShortInteger, gChangeCharValue, UnsignedShortInteger_im_gChangeCharValue);

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return UnsignedShortInteger_c;
}