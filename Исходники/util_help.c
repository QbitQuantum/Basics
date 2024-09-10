void util_help(void)
{
	int  rc;
	char *help_option;
	char help_cmd_string[HELP_CMD_STRING_SIZE];
	DCL_THREADGBL_ACCESS;

	SETUP_THREADGBL_ACCESS;
	assert(1 >= TREF(parms_cnt));
	assert(GTM_IMAGE < image_type && UTIL_HELP_IMAGES > image_type);
	if (0 == TREF(parms_cnt))
		help_option = utilImageGLDs[INVALID_IMAGE];
	else
	{
		assert(TAREF1(parm_ary, TREF(parms_cnt) - 1));
		assert((char *)-1L != (TAREF1(parm_ary, TREF(parms_cnt) - 1)));
		help_option = (TAREF1(parm_ary, TREF(parms_cnt) - 1));
	}
	SNPRINTF(help_cmd_string, SIZEOF(help_cmd_string),
			"$gtm_dist/mumps -run %%XCMD 'do ^GTMHELP(\"%s\",\"$gtm_dist/%shelp.gld\")'",
			help_option, utilImageGLDs[image_type]);
	rc = SYSTEM(help_cmd_string);
	if (0 != rc)
		rts_error_csa(NULL, VARLSTCNT(5) ERR_TEXT, 2, RTS_ERROR_TEXT("HELP command error"), rc);
}