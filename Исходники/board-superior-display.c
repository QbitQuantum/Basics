static int get_panel_data(char *str, struct panel_s6e8aa0a01_data *panel)
{
	u8 temp_data[(ID_PARAM_SIZE+MTP_PARAM_SIZE)*2];
	unsigned int val;
	int i = 0;

	while (*str) {

		if ('0' <= *str && *str <= '9')
			val = *str - '0';
		else if ('a' <= _tolower(*str) && _tolower(*str) <= 'f')
			val = _tolower(*str) - 'a' + 10;
		else if (*str == '\n' && *(str + 1) == '\0')
			break;
		else
			return -EINVAL;

		temp_data[i++] = val;

		str++;
	}

	for (i = 0; i < ID_PARAM_SIZE; i++) {
		panel->panel_id[i] =
			((temp_data[i*2]<<4)&0xF0)|(temp_data[i*2+1]&0x0F);
		pr_info("panel_id[%d]=0x%02x\n", i, panel->panel_id[i]);
	}
	for (i = 0; i < MTP_PARAM_SIZE; i++) {
		panel->mtp_data[i] =
			((temp_data[(i+ID_PARAM_SIZE)*2]<<4)&0xF0)|
			(temp_data[(i+ID_PARAM_SIZE)*2+1]&0x0F);
		pr_info("mtp_data[%d]=0x%02x\n", i, panel->mtp_data[i]);
	}

}