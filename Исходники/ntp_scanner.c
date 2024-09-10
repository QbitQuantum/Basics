static int
get_next_char(
	struct FILE_INFO *ip_file
	)
{
	char ch;

	if (input_from_file)
		return FGETC(ip_file);
	else {
		if (remote_config.buffer[remote_config.pos] == '\0') 
			return EOF;
		else {
			ip_file->col_no++;
			ch = remote_config.buffer[remote_config.pos++];
			if (ch == '\n') {
				ip_file->prev_line_col_no = ip_file->col_no;
				++ip_file->line_no;
				ip_file->col_no = 1;
			}
			return ch;
		}
	}
}