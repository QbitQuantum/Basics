int dc_read_switch_config(CmdData *cmd_data)
{
	u32 i;
	int src_number;
	char start_time[4096], end_time[4096];

	time_t now_t = time(NULL);
	struct tm start_tm = *localtime(&now_t);
	struct tm end_tm = *localtime(&now_t);

	GF_Config *conf = cmd_data->switch_conf;
	u32 sec_count = gf_cfg_get_section_count(conf);

	dc_task_init(&cmd_data->task_list);

	if (sec_count == 0) {
		return 0;
	}

	for (i = 0; i < sec_count; i++) {
		const char *section_name = gf_cfg_get_section_name(conf, i);
		const char *section_type = gf_cfg_get_key(conf, section_name, "type");

		if (strcmp(section_type, "video") == 0) {
			VideoDataConf *video_data_conf = gf_malloc(sizeof(VideoDataConf));

			strcpy(video_data_conf->source_id, section_name);
			strcpy(video_data_conf->filename, gf_cfg_get_key(conf, section_name, "source"));

			strcpy(start_time, gf_cfg_get_key(conf, section_name, "start"));
			parse_time(start_time, &start_tm);
			video_data_conf->start_time = mktime(&start_tm);
			strcpy(end_time, gf_cfg_get_key(conf, section_name, "end"));
			parse_time(end_time, &end_tm);
			video_data_conf->end_time = mktime(&end_tm);

			gf_list_add(cmd_data->vsrc, (void *) video_data_conf);

			src_number = gf_list_count(cmd_data->vsrc);

			dc_task_add(&cmd_data->task_list, src_number, video_data_conf->source_id, video_data_conf->start_time, video_data_conf->end_time);
		}
		else if (strcmp(section_type, "audio") == 0)
		{
			AudioDataConf *audio_data_conf = gf_malloc(sizeof(AudioDataConf));
			strcpy(audio_data_conf->source_id, section_name);
			strcpy(audio_data_conf->filename, gf_cfg_get_key(conf, section_name, "source"));

			strcpy(start_time, gf_cfg_get_key(conf, section_name, "start"));
			parse_time(start_time, &start_tm);
			audio_data_conf->start_time = mktime(&start_tm);

			strcpy(end_time, gf_cfg_get_key(conf, section_name, "end"));
			parse_time(end_time, &end_tm);
			audio_data_conf->end_time = mktime(&end_tm);

			gf_list_add(cmd_data->asrc, (void *) audio_data_conf);
		} else {
			fprintf(stdout, "Switch source configuration file: type %s is not supported.\n", section_type);
		}
	}

	fprintf(stdout, "\33[34m\33[1m");
	fprintf(stdout, "Sources:\n");
	for (i=0; i<gf_list_count(cmd_data->vsrc); i++) {
		VideoDataConf *video_data_conf = gf_list_get(cmd_data->vsrc, i);
		strftime(start_time, 20, "%Y-%m-%d %H:%M:%S", localtime(&video_data_conf->start_time));
		strftime(end_time, 20, "%Y-%m-%d %H:%M:%S", localtime(&video_data_conf->end_time));
		fprintf(stdout, "    id:%s\tsource:%s\tstart:%s\tend:%s\n", video_data_conf->source_id, video_data_conf->filename, start_time, end_time);
	}

	for (i=0; i<gf_list_count(cmd_data->asrc); i++) {
		AudioDataConf *audio_data_conf = gf_list_get(cmd_data->asrc, i);
		strftime(start_time, 20, "%Y-%m-%d %H:%M:%S", localtime(&audio_data_conf->start_time));
		strftime(end_time, 20, "%Y-%m-%d %H:%M:%S", localtime(&audio_data_conf->end_time));
		fprintf(stdout, "    id:%s\tsource:%s\tstart:%s\tend:%s\n", audio_data_conf->source_id, audio_data_conf->filename, start_time, end_time);
	}
	fprintf(stdout, "\33[0m");
	fflush(stdout);

	return 0;
}