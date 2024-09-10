/*
 * Do format conversion placing the output in buffer
 */
static void xbuf_format_converter(smart_str *xbuf, const char *fmt, va_list ap) /* {{{ */
{
	char *s = NULL;
	int s_len, free_zcopy;
	zval *zvp, zcopy;

	int min_width = 0;
	int precision = 0;
	enum {
		LEFT, RIGHT
	} adjust;
	char pad_char;
	char prefix_char;

	double fp_num;
	wide_int i_num = (wide_int) 0;
	u_wide_int ui_num = (u_wide_int) 0;

	char num_buf[NUM_BUF_SIZE];
	char char_buf[2];			/* for printing %% and %<unknown> */

#ifdef HAVE_LOCALE_H
	struct lconv *lconv = NULL;
#endif

	/*
	 * Flag variables
	 */
	length_modifier_e modifier;
	boolean_e alternate_form;
	boolean_e print_sign;
	boolean_e print_blank;
	boolean_e adjust_precision;
	boolean_e adjust_width;
	bool_int is_negative;

	while (*fmt) {
		if (*fmt != '%') {
			INS_CHAR(xbuf, *fmt);
		} else {
			/*
			 * Default variable settings
			 */
			adjust = RIGHT;
			alternate_form = print_sign = print_blank = NO;
			pad_char = ' ';
			prefix_char = NUL;
			free_zcopy = 0;

			fmt++;

			/*
			 * Try to avoid checking for flags, width or precision
			 */
			if (isascii((int)*fmt) && !islower((int)*fmt)) {
				/*
				 * Recognize flags: -, #, BLANK, +
				 */
				for (;; fmt++) {
					if (*fmt == '-')
						adjust = LEFT;
					else if (*fmt == '+')
						print_sign = YES;
					else if (*fmt == '#')
						alternate_form = YES;
					else if (*fmt == ' ')
						print_blank = YES;
					else if (*fmt == '0')
						pad_char = '0';
					else
						break;
				}

				/*
				 * Check if a width was specified
				 */
				if (isdigit((int)*fmt)) {
					STR_TO_DEC(fmt, min_width);
					adjust_width = YES;
				} else if (*fmt == '*') {
					min_width = va_arg(ap, int);
					fmt++;
					adjust_width = YES;
					if (min_width < 0) {
						adjust = LEFT;
						min_width = -min_width;
					}
				} else
					adjust_width = NO;

				/*
				 * Check if a precision was specified
				 */
				if (*fmt == '.') {
					adjust_precision = YES;
					fmt++;
					if (isdigit((int)*fmt)) {
						STR_TO_DEC(fmt, precision);
					} else if (*fmt == '*') {
						precision = va_arg(ap, int);
						fmt++;
						if (precision < 0)
							precision = 0;
					} else