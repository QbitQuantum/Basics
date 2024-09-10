/*
   Parse a string of the form FUNC(arg1,arg2,...)
   Returns the number of parameters or -1 on error.
   */
int parse_string(char *line, char **params, int max_params)
{
	int pos;
	int param_start;
	char *next_param;
	int param_count;

	assert(line != NULL);
	assert(params != NULL);

	pos = 0;

	/* Parse off "function" name */
	while((isalnum(line[pos])) || (line[pos] == '_'))
	{
		pos++;
	}

	/* If we don't have any thing else than this is just the function */
	if(line[pos] == 0)
	{
		return 0;
	}

	if(line[pos] != '(')
	{
		snprintf(g_errstring, MAX_ERROR, "Invalid character %c, expected (", line[pos]);
		return -1;
	}

	/* Terminate */
	line[pos++] = 0;
	param_start = pos;

	/* Scan parameters */
	while((isalnum(line[pos])) || (line[pos] == '_') || (line[pos] == ','))
	{
		pos++;
	}

	if(line[pos] == 0)
	{
		snprintf(g_errstring, MAX_ERROR, "Missing closing brace ')'");
		return -1;
	}

	if(line[pos] != ')')
	{
		snprintf(g_errstring, MAX_ERROR, "Invalid character %c, expected ')'", line[pos]);
		return -1;
	}

	if(line[pos+1] != 0)
	{
		snprintf(g_errstring, MAX_ERROR, "Trailing characters after bracket close %d", line[pos+1]);
		return -1;
	}

	line[pos] = 0;

	param_count = 0;
	next_param = strtok(&line[param_start], ",");
	while(next_param != NULL)
	{
		if(param_count == max_params)
		{
			snprintf(g_errstring, MAX_ERROR, "Run out of space for parameters");
			return -1;
		}

		params[param_count++] = next_param;
		next_param = strtok(NULL, ",");
	}

	return param_count;
}