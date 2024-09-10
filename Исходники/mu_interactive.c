boolean_t mu_interactive(caddr_t message)
{
	boolean_t	done = FALSE, mur_error_allowed;
	unsigned short	len;
	int		index;
	char		res[8];
	char 		*fgets_res;
	util_out_print(PROCEED_PROMPT, TRUE);

	while (FALSE == done)
	{
		fgets_res = util_input(res, SIZEOF(res), stdin, FALSE);
		if (NULL != fgets_res)
		{
			len = strlen(res);
			if (0 < len)
			{
				for (index = 0; index < len; index++)
					res[index] = TOUPPER(res[index]);
				if (0 == memcmp(res, YES_STRING, len))
				{
					done = TRUE;
					mur_error_allowed = TRUE;
					break;
				} else if (0 == memcmp(res, NO_STRING, len))
				{
					done = TRUE;
					mur_error_allowed = FALSE;
					break;
				}
			}
			util_out_print(CORRECT_PROMPT, TRUE);
		} else
		{
			mur_error_allowed = FALSE;
			break;
		}
	}
	if (FALSE == mur_error_allowed)
		util_out_print(message, TRUE);
	return (mur_error_allowed);
}