objrtn	SeriousCondition_initialize(void)
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

	if (SeriousCondition_c) {
		LEAVECRITICALSECTION(cs);
		return SeriousCondition_c;
	}
	INHIBIT_THREADER;
	Condition_initialize();
	if (SeriousCondition_c)  {
		ENABLE_THREADER;
		LEAVECRITICALSECTION(cs);
		return SeriousCondition_c;
	}
	SeriousCondition_c = gNewClass(Class, "SeriousCondition", 0, 0, Condition, END);
	iMethodFor(SeriousCondition, gDefaultRestart, SeriousCondition_im_gDefaultRestart);

	ENABLE_THREADER;

	LEAVECRITICALSECTION(cs);

	return SeriousCondition_c;
}