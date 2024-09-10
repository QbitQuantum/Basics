/*
 * MPP-220077: real_act_prefix_size should not go beyond ps_buffer_size
 */
void
test__set_ps_display__real_act_prefix_size(void **state)
{
	int		len;

	ps_buffer = (char *) malloc(127 * sizeof(char));
	ps_buffer_fixed_size = 79;
	memset(ps_buffer, 'x', ps_buffer_fixed_size * sizeof(char));
	ps_buffer_size = 127;
	IsUnderPostmaster = true;

	StrNCpy(ps_host_info, "msa4000125.europe.corp.microsoft.com(57193)",
			sizeof(ps_host_info));
	ps_host_info_size = 0;
	gp_session_id = 26351;
	Gp_role = GP_ROLE_DISPATCH;
	Gp_segment = -1;
	gp_command_count = 964;
	currentSliceId = -1;

	set_ps_display("testing activity", true);
	assert_true(real_act_prefix_size <= ps_buffer_size);

	get_real_act_ps_display(&len);
	assert_true(len >= 0);
}