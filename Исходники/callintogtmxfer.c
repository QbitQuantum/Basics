void init_callin_functable(void)
{
	unsigned char 	*env_top, *address_top;
	uint4		address_len;

	/* The address of the vector table containing pointers
	 * to gt_timers functions is of type unsigned int which
	 * is o.k in current GT.M implementations, however when
	 * GT.M migrates to a fully 64 port this part of the code
	 * might have be re-visited.
	 */
	assert ( 64 > sizeof(gtmvectortable_address));
	address_top = i2asc(gtmvectortable_address, (uint4 )&callintogtm_vectortable[0]);
	*address_top = '\0';
	address_len = (uint4 )(address_top - &gtmvectortable_address[0]);
	env_top =  &gtmvectortable_env[0];
	memcpy(env_top, GTM_CALLIN_START_ENV, strlen(GTM_CALLIN_START_ENV));
	memcpy((env_top + strlen(GTM_CALLIN_START_ENV)), gtmvectortable_address, address_len);
	*(env_top + strlen(GTM_CALLIN_START_ENV) + address_len) = '\0';
	if (PUTENV((char *)gtmvectortable_env))
	{
		rts_error(VARLSTCNT(1) errno);
	}
}