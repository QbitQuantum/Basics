/*
 * Do format conversion placing the output in buffer
 */
API_EXPORT(int) ap_vformatter(int (*flush_func)(ap_vformatter_buff *),
    ap_vformatter_buff *vbuff, const char *fmt, va_list ap)
{
    register char *sp;
    register char *bep;
    register int cc = 0;
    register int i;

    register char *s = NULL;
    char *q;
    int s_len;

    register int min_width = 0;
    int precision = 0;
    enum {
	LEFT, RIGHT
    } adjust;
    char pad_char;
    char prefix_char;

    double fp_num;
    wide_int i_num = (wide_int) 0;
    u_wide_int ui_num;

    char num_buf[NUM_BUF_SIZE];
    char char_buf[2];		/* for printing %% and %<unknown> */

    /*
     * Flag variables
     */
    boolean_e is_long;
    boolean_e alternate_form;
    boolean_e print_sign;
    boolean_e print_blank;
    boolean_e adjust_precision;
    boolean_e adjust_width;
    bool_int is_negative;

    sp = vbuff->curpos;
    bep = vbuff->endpos;

    while (*fmt) {
	if (*fmt != '%') {
	    INS_CHAR(*fmt, sp, bep, cc);
	}
	else {
	    /*
	     * Default variable settings
	     */
	    adjust = RIGHT;
	    alternate_form = print_sign = print_blank = NO;
	    pad_char = ' ';
	    prefix_char = NUL;

	    fmt++;

	    /*
	     * Try to avoid checking for flags, width or precision
	     */
	    if (isascii(*fmt) && !islower(*fmt)) {
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
		if (isdigit(*fmt)) {
		    STR_TO_DEC(fmt, min_width);
		    adjust_width = YES;
		}
		else if (*fmt == '*') {
		    min_width = va_arg(ap, int);
		    fmt++;
		    adjust_width = YES;
		    if (min_width < 0) {
			adjust = LEFT;
			min_width = -min_width;
		    }
		}
		else
		    adjust_width = NO;

		/*
		 * Check if a precision was specified
		 *
		 * XXX: an unreasonable amount of precision may be specified
		 * resulting in overflow of num_buf. Currently we
		 * ignore this possibility.
		 */
		if (*fmt == '.') {
		    adjust_precision = YES;
		    fmt++;
		    if (isdigit(*fmt)) {
			STR_TO_DEC(fmt, precision);
		    }
		    else if (*fmt == '*') {
			precision = va_arg(ap, int);
			fmt++;
			if (precision < 0)
			    precision = 0;
		    }
		    else