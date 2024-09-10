// read config from file to the structure
int io_read_config (tIO *conf_data)
{
	FILE *fp = NULL;
	char input[128];
	char token[64];
	int line = 0;

	fp = fopen (conf_file, "r");
	if (fp == NULL) {
//		fprintf(stderr, "can't open %s: %s\n", conf_files[chan], strerror(errno));
		return (-1);
	}

	while (fgets(input, sizeof (input), fp)!=NULL){
		char *ptr = input;
		line ++;

		ptr = get_token (ptr, token, sizeof (token));
		if (token[0] == '#')
			continue;

		if (strcasecmp (token, "ext_inputs") == 0) {

			ptr = get_token (ptr, token, sizeof (token));
			if (strcmp (token, "{") != 0)
				goto err;

			while (fgets(input, sizeof (input), fp)!=NULL){
				char *ptr = input;
				line++;

				ptr = get_token (ptr, token, sizeof (token));
				if (token[0] == '#')
					continue;

				if (strcmp (token, "}") == 0) {
					break;
				}
				else if (strcasecmp (token, "ch_1_current_state") == 0) {
					ptr = get_token (ptr, token, sizeof (token));
					conf_data->ext_inputs[0].current_state = atol (token);
				}
				else if (strcasecmp (token, "ch_2_current_state") == 0) {
					ptr = get_token (ptr, token, sizeof (token));
					conf_data->ext_inputs[1].current_state = atol (token);
				}
			}
		}
		else if (strcasecmp (token, "ext_outputs") == 0) {
			ptr = get_token (ptr, token, sizeof (token));
			if (strcmp (token, "{") != 0)
				goto err;

			while (fgets(input, sizeof (input), fp)!=NULL){
				char *ptr = input;
				line++;

				ptr = get_token (ptr, token, sizeof (token));
				if (token[0] == '#')
					continue;

				if (strcmp (token, "}") == 0) {
					break;
				}
				else if (strcasecmp (token, "ch_1_current_state") == 0) {
					ptr = get_token (ptr, token, sizeof (token));
					conf_data->ext_outputs[0].current_state = atol (token);
				}
				else if (strcasecmp (token, "ch_2_current_state") == 0) {
					ptr = get_token (ptr, token, sizeof (token));
					conf_data->ext_outputs[1].current_state = atol (token);
				}
				else if (strcasecmp (token, "ch_1_default_state") == 0) {
					ptr = get_token (ptr, token, sizeof (token));
					conf_data->ext_outputs[0].default_state = atol (token);
				}
				else if (strcasecmp (token, "ch_2_default_state") == 0) {
					ptr = get_token (ptr, token, sizeof (token));
					conf_data->ext_outputs[1].default_state = atol (token);
				}
			}
		}
	}

	fclose (fp);
	return 0;

err:
//	fprintf(stderr, "Error %s in %d\n", &conf_files[chan], line);
	if (fp)	fclose (fp);
	return -1;
}