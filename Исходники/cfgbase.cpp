char  * ConfigBase::GetValue(const char * const val)
{
	static char opBuf[256];
	
	char    *ptr=NULL;
	char    buf[128];
	int     buflen=128;
	int     stat=0;
	
	if (NULL == val)
	{   // Exception
		xcpPtr->error(E_NULL_POINTER, SF_CFGBASE, g_Errstr[E_NULL_POINTER]);
		return NULL;
	}
	
	if (ReOpenFile( ) != E_SUCC)
	{
		return NULL;
	}
	
	while (GetLine(buf, buflen) != NULL)
	{    
		ptr=buf;

		if (! strcmp(m_sField, ""))
			stat=1;
		else if (strstr(buf, m_sField))
		{
			stat=1;
			continue;
		}

		if (stat == 0)
			continue;
		 
		while (*ptr == '\t'  ||  *ptr == ' ')
			ptr++;

		if (*ptr == '[')
			break;
		
		if ((*ptr == '\0')  ||
			(*ptr == '\n')  ||
			(*ptr == '\r')  ||
			(*ptr == ';')  ||
			(*ptr == '#'))
			continue;

		if (strncmp(ptr, val, strlen(val)) != 0)
			continue;

		ptr = strchr(ptr, '=');
		if (ptr!=NULL)
		{
			while (*ptr == '\t'  ||  *ptr == ' ')
				++ptr;
			
			++ptr;

			if ((*ptr == '\0')  ||
				(*ptr == '\n')  ||
				(*ptr == '\r')  ||
				(*ptr == ';')  ||
				(*ptr == '#'))
			{   // Exception handle
				// printf("[%s] Missing value\n",val);
				xcpPtr->error(E_CONFIG_MISS, SF_CFGBASE, g_Errstr[E_CONFIG_MISS]);
				return NULL;
			}

			if ((*ptr == '\"')  ||
				(*ptr == '\''))
			{
				char ch = *ptr;
				int len = 0;

				++ptr;  // Ignore the start delimitation char
				do
				{
					if ((*ptr == '\0')  ||  (len >= MAX_LENGTH_CFG))
					{   // Exception handle
						// opBuf[0] = '\0';
						// break;
						xcpPtr->error(E_CONFIG_ERROR, SF_CFGBASE, "Missing delimitation char \' or \".");
						return NULL;
					}
					
					opBuf[len] = *ptr;
					++len;
					++ptr;
				} while (*ptr != ch);
				opBuf[len] = '\0';
			}
			else
			{
				int len = 0;

				do
				{
					opBuf[len] = *ptr;
					++len;
					++ptr;
				} while ((*ptr != ' ')  &&
						(*ptr != '\0')  &&
						(*ptr != '\n')  &&
						(*ptr != '\r')  &&
						(*ptr != '\t')  &&
						(*ptr != ';')  &&
						(*ptr != '#'));
				opBuf[len] = '\0';
			}
			return opBuf;
		}
		// Exception handle
		// printf("[%s] Missing value\n",val);
		xcpPtr->error(E_CONFIG_MISS, SF_CFGBASE, "The option missing value.");
		return NULL;
	}
	return NULL;
}