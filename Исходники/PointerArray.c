objrtn	PointerArray_initialize(void)
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

	if (PointerArray_c) {
		LEAVECRITICALSECTION(cs);
		return PointerArray_c;
	}
	INHIBIT_THREADER;
	Array_initialize();
	if (PointerArray_c)  {
		ENABLE_THREADER;
		LEAVECRITICALSECTION(cs);
		return PointerArray_c;
	}
	PointerArray_c = gNewClass(Class, "PointerArray", 0, 0, Array, END);
	cvMethodFor(PointerArray, vNew, PointerArray_cvm_vNew, PointerArray_cfm_vNew);
	ivMethodFor(PointerArray, vChangeValue, PointerArray_ivm_vChangeValue, PointerArray_ifm_vChangeValue);
	ivMethodFor(PointerArray, vPointerValue, PointerArray_ivm_vPointerValue, PointerArray_ifm_vPointerValue);

	init_class();

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return PointerArray_c;
}