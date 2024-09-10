int sndintrf_init_sound(int sndnum, sound_type sndtype, int clock, const void *config)
{
	sndintrf_data *info = &sound[sndnum];
	int index;

	/* fill in the type and interface */
	info->intf = sndintrf[sndtype];
	info->sndtype = sndtype;
	info->aliastype = sndtype_get_info_int(sndtype, SNDINFO_INT_ALIAS);
	if (info->aliastype == 0)
		info->aliastype = sndtype;
	info->clock = clock;

	/* find an empty slot in the matrix and add it */
	totalsnd++;
	for (index = 0; index < MAX_SOUND; index++)
		if (sound_matrix[info->aliastype][index] == 0)
		{
			sound_matrix[info->aliastype][index] = totalsnd;
			break;
		}
	info->index = index;

	/* start the chip, tagging all its streams */
	current_sound_start = &sound[sndnum];
	info->token = (*info->intf.start)(index, clock, config);
	current_sound_start = NULL;
	VPRINTF(("  token = %p\n", info->token));

	/* if that failed, die */
	if (!info->token)
		return 1;

	return 0;
}