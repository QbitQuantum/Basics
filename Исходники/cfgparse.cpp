int config_parser_t::read_config(char ***cv, FILE *f)
{
	*cv = (char **)calloc(MAX_CONFIG_LINES, sizeof(char *));
	if(!*cv)
		return -1;

	if(!f)
	{
		free((*cv));
		(*cv) = NULL;
		return -2;
	}

	fseek(f, 0, SEEK_END);
	int len = ftell(f);
	(*cv)[0] = (char *)malloc(len+1);
	if(!(*cv)[0])
	{
		rewind(f);
		free(*cv);
		*cv = NULL;
		return -3;
	}
	rewind(f);
	if(fread((*cv)[0], len, 1, f) < 0)
	{
		free(*cv[0]);
		free(*cv);
		*cv = NULL;
		return -4;
	}
	(*cv)[0][len] = 0;

	char *v = (*cv)[0];
	scanstate_t state = SS_BLANK;
	int arg = 1;
	int start_arg = 0;
	while(*v)
	{
		switch(state)
		{
		  case SS_BLANK:
			if(*v == '"')
			{
				start_arg = 1;
				state = SS_QUOTE;
			}
			else if(*v == '#')
				state = SS_COMMENT;
			else if(*v > ' ')
			{
				start_arg = 1;
				state = SS_WORD;
			}
			break;
		  case SS_QUOTE:
			if(*v == '"')
			{
				*v = 0;
				state = SS_BLANK;
			}
			break;
		  case SS_WORD:
			if(*v <= ' ')
			{
				*v = 0;
				state = SS_BLANK;
			}
			break;
		  case SS_COMMENT:
			if((*v == 10) || (*v == 13))
				state = SS_BLANK;
			break;
		}
		if(start_arg)
		{
			if(arg < MAX_CONFIG_LINES)
			{
				if(state == SS_QUOTE)
					(*cv)[arg++] = v+1;
				else
					(*cv)[arg++] = v;
			}
			start_arg = 0;
		}
		++v;
	}
	rewind(f);
	return arg;
}