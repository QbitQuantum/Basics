void	util_out_print_vaparm(caddr_t message, int flush, va_list var, int faocnt)
{
	char	fmt_buff[OUT_BUFF_SIZE];
	caddr_t	fmtc;
	int	rc;

	/*
	 * Note: this function checks for EINTR on FPRINTF. This check should not be
	 * converted to an EINTR wrapper macro because of the variable number of args used
	 * by fprintf.
	 */

	if (util_outptr == NULL)
		util_outptr = util_outbuff;

	if (message != NULL)
		util_outptr = util_format(message, var, util_outptr, OUT_BUFF_SIZE - (util_outptr - util_outbuff) - 2, faocnt);

	switch (flush)
	{
		case NOFLUSH:
			break;

		case RESET:
			break;

		case FLUSH:
			*util_outptr++ = '\n';
		case OPER:
		case SPRINT:
			/******************************************************************************************************
			   For all three of these actions we need to do some output buffer translation. In all cases a '%'
			   is translated to the escape version '%%'. For OPER and SPRINT, we also translate '\n' to a ', '
			   since some syslog() implementations (like Tru64) stop processing the passed message on a newline.
			*******************************************************************************************************/
			*util_outptr = '\0';
			for (util_outptr = util_outbuff, fmtc = fmt_buff;  0 != *util_outptr; )
			{
				if ('%' == *util_outptr)
				{
					*fmtc++ = '%';	/* escape for '%' */
					*fmtc++ = '%';
					util_outptr++;
				} else if ('\n' == *util_outptr && (OPER == flush || SPRINT == flush))
				{
					*fmtc++ = ',';
					*fmtc++ = ' ';
					util_outptr++;
				} else
					*fmtc++ = *util_outptr++;
			}
			*fmtc++ = '\0';
			switch (flush)
			{
				case FLUSH:
					do
					{
						rc = FPRINTF(stderr, fmt_buff);
					} while (-1 == rc && EINTR == errno);
					break;
				case OPER:
					util_out_send_oper(STR_AND_LEN(fmt_buff));
					break;
				case SPRINT:
					memcpy(util_outbuff, fmt_buff, fmtc - fmt_buff);
					break;
			}
			break;
		default:
			assert(FALSE);
	}
	switch (flush)
	{
		case NOFLUSH:
			break;

		case FLUSH:
		case RESET:
		case OPER:
		case SPRINT:
			/* Reset buffer information.  */
			util_outptr = util_outbuff;
			break;
	}

}