/* Get next line of input from G.input_file_list, flushing append buffer and
 * noting if we ran out of files without a newline on the last line we read.
 */
static char *get_next_line(char *gets_char, char *last_puts_char)
{
	char *temp = NULL;
	int len;
	char gc;

	flush_append(last_puts_char);

	/* will be returned if last line in the file
	 * doesn't end with either '\n' or '\0' */
	gc = NO_EOL_CHAR;
	for (; G.current_input_file <= G.last_input_file; G.current_input_file++) {
		FILE *fp = G.current_fp;
		if (!fp) {
			const char *path = G.input_file_list[G.current_input_file];
			fp = stdin;
			if (path != bb_msg_standard_input) {
				fp = fopen_or_warn(path, "r");
				if (!fp) {
					G.exitcode = EXIT_FAILURE;
					continue;
				}
			}
			G.current_fp = fp;
		}
		/* Read line up to a newline or NUL byte, inclusive,
		 * return malloc'ed char[]. length of the chunk read
		 * is stored in len. NULL if EOF/error */
		temp = bb_get_chunk_from_file(fp, &len);
		if (temp) {
			/* len > 0 here, it's ok to do temp[len-1] */
			char c = temp[len-1];
			if (c == '\n' || c == '\0') {
				temp[len-1] = '\0';
#if ENABLE_PLATFORM_MINGW32
				if (c == '\n' && len > 1 && temp[len-2] == '\r') {
					temp[len-2] = '\0';
				}
#endif
				gc = c;
				if (c == '\0') {
					int ch = fgetc(fp);
					if (ch != EOF)
						ungetc(ch, fp);
					else
						gc = LAST_IS_NUL;
				}
			}
			/* else we put NO_EOL_CHAR into *gets_char */
			break;

		/* NB: I had the idea of peeking next file(s) and returning
		 * NO_EOL_CHAR only if it is the *last* non-empty
		 * input file. But there is a case where this won't work:
		 * file1: "a woo\nb woo"
		 * file2: "c no\nd no"
		 * sed -ne 's/woo/bang/p' input1 input2 => "a bang\nb bang"
		 * (note: *no* newline after "b bang"!) */
		}
		/* Close this file and advance to next one */
		fclose_if_not_stdin(fp);
		G.current_fp = NULL;
	}
	*gets_char = gc;
	return temp;
}