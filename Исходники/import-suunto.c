static int dm4_dive(void *param, int columns, char **data, char **column)
{
	UNUSED(columns);
	UNUSED(column);
	int i;
	int interval, retval = 0;
	struct parser_state *state = (struct parser_state *)param;
	sqlite3 *handle = state->sql_handle;
	float *profileBlob;
	unsigned char *tempBlob;
	int *pressureBlob;
	char *err = NULL;
	char get_events_template[] = "select * from Mark where DiveId = %d";
	char get_tags_template[] = "select Text from DiveTag where DiveId = %d";
	char get_events[64];

	dive_start(state);
	state->cur_dive->number = atoi(data[0]);

	state->cur_dive->when = (time_t)(atol(data[1]));
	if (data[2])
		utf8_string(data[2], &state->cur_dive->notes);

	/*
	 * DM4 stores Duration and DiveTime. It looks like DiveTime is
	 * 10 to 60 seconds shorter than Duration. However, I have no
	 * idea what is the difference and which one should be used.
	 * Duration = data[3]
	 * DiveTime = data[15]
	 */
	if (data[3])
		state->cur_dive->duration.seconds = atoi(data[3]);
	if (data[15])
		state->cur_dive->dc.duration.seconds = atoi(data[15]);

	/*
	 * TODO: the deviceid hash should be calculated here.
	 */
	settings_start(state);
	dc_settings_start(state);
	if (data[4])
		utf8_string(data[4], &state->cur_settings.dc.serial_nr);
	if (data[5])
		utf8_string(data[5], &state->cur_settings.dc.model);

	state->cur_settings.dc.deviceid = 0xffffffff;
	dc_settings_end(state);
	settings_end(state);

	if (data[6])
		state->cur_dive->dc.maxdepth.mm = lrint(strtod_flags(data[6], NULL, 0) * 1000);
	if (data[8])
		state->cur_dive->dc.airtemp.mkelvin = C_to_mkelvin(atoi(data[8]));
	if (data[9])
		state->cur_dive->dc.watertemp.mkelvin = C_to_mkelvin(atoi(data[9]));

	/*
	 * TODO: handle multiple cylinders
	 */
	cylinder_start(state);
	if (data[22] && atoi(data[22]) > 0)
		state->cur_dive->cylinder[state->cur_cylinder_index].start.mbar = atoi(data[22]);
	else if (data[10] && atoi(data[10]) > 0)
		state->cur_dive->cylinder[state->cur_cylinder_index].start.mbar = atoi(data[10]);
	if (data[23] && atoi(data[23]) > 0)
		state->cur_dive->cylinder[state->cur_cylinder_index].end.mbar = (atoi(data[23]));
	if (data[11] && atoi(data[11]) > 0)
		state->cur_dive->cylinder[state->cur_cylinder_index].end.mbar = (atoi(data[11]));
	if (data[12])
		state->cur_dive->cylinder[state->cur_cylinder_index].type.size.mliter = lrint((strtod_flags(data[12], NULL, 0)) * 1000);
	if (data[13])
		state->cur_dive->cylinder[state->cur_cylinder_index].type.workingpressure.mbar = (atoi(data[13]));
	if (data[20])
		state->cur_dive->cylinder[state->cur_cylinder_index].gasmix.o2.permille = atoi(data[20]) * 10;
	if (data[21])
		state->cur_dive->cylinder[state->cur_cylinder_index].gasmix.he.permille = atoi(data[21]) * 10;
	cylinder_end(state);

	if (data[14])
		state->cur_dive->dc.surface_pressure.mbar = (atoi(data[14]) * 1000);

	interval = data[16] ? atoi(data[16]) : 0;
	profileBlob = (float *)data[17];
	tempBlob = (unsigned char *)data[18];
	pressureBlob = (int *)data[19];
	for (i = 0; interval && i * interval < state->cur_dive->duration.seconds; i++) {
		sample_start(state);
		state->cur_sample->time.seconds = i * interval;
		if (profileBlob)
			state->cur_sample->depth.mm = lrintf(profileBlob[i] * 1000.0f);
		else
			state->cur_sample->depth.mm = state->cur_dive->dc.maxdepth.mm;

		if (data[18] && data[18][0])
			state->cur_sample->temperature.mkelvin = C_to_mkelvin(tempBlob[i]);
		if (data[19] && data[19][0])
			state->cur_sample->pressure[0].mbar = pressureBlob[i];
		sample_end(state);
	}

	snprintf(get_events, sizeof(get_events) - 1, get_events_template, state->cur_dive->number);
	retval = sqlite3_exec(handle, get_events, &dm4_events, state, &err);
	if (retval != SQLITE_OK) {
		fprintf(stderr, "%s", "Database query dm4_events failed.\n");
		return 1;
	}

	snprintf(get_events, sizeof(get_events) - 1, get_tags_template, state->cur_dive->number);
	retval = sqlite3_exec(handle, get_events, &dm4_tags, state, &err);
	if (retval != SQLITE_OK) {
		fprintf(stderr, "%s", "Database query dm4_tags failed.\n");
		return 1;
	}

	dive_end(state);

	/*
	for (i=0; i<columns;++i) {
		fprintf(stderr, "%s\t", column[i]);
	}
	fprintf(stderr, "\n");
	for (i=0; i<columns;++i) {
		fprintf(stderr, "%s\t", data[i]);
	}
	fprintf(stderr, "\n");
	//exit(0);
	*/
	return SQLITE_OK;
}