void PdmsFileSession::skipComment()
{
	switch (currentToken)
	{
	case PDMS_COMMENT_LINE:
		//skip line only if the end of line has not been read in current buffer
		if (!m_eol)
		{
			int n = 0;
			int car = 0;
			do {
				car = getc(m_file);
				if (car == '\t') car = ' ';
				tokenBuffer[n] = car;
				if (((n + 1) < c_max_buff_size) && ((car != ' ') || (n > 0 && tokenBuffer[n - 1] != ' '))) n++;
			} while (car != EOF && car != '\n');
			if (car == '\n')
				m_currentLine++;
			tokenBuffer[n - 1] = '\0';
		}
		m_eol = false;
		break;
	case PDMS_COMMENT_BLOCK:
	{
		//comment block opening symbol has been met. Search for comment block ending symbol
		//don't forget that some other comments could be embedded in this comment
		bool commentSymb = false;
		int commentBlockLevel = 1;
		int n = 0;
		int car = 0;
		do {
			car = getc(m_file);
			if (car == '\n') m_currentLine++;
			if (car == '\n' || car == '\t') car = ' ';
			if (car == '$') commentSymb = true;
			else if (car == '(' && commentSymb) commentBlockLevel++;
			else if (car == ')' && commentSymb) commentBlockLevel--;
			else
			{
				commentSymb = false;
				tokenBuffer[n] = car;
				if (((n + 1) < c_max_buff_size) && ((car != ' ') || (n > 0 && tokenBuffer[n - 1] != ' '))) n++;
			}
		} while (car != EOF && commentBlockLevel > 0);
		tokenBuffer[n - 1] = '\0';
		m_eol = false;
	}
	break;
	default:
		break;
	}

	upperStr(tokenBuffer);
	if (strncmp(tokenBuffer, "ENTERING IN GROUP:", 18) == 0)
	{
		currentToken = PDMS_ENTER_METAGROUP;
		//The meta group name starts after the "entering in group:" statement, after the last slash
		//But we still store the whole path
		char* ptr2 = &(tokenBuffer[18]);
		while ((*ptr2) == ' ') { ptr2++; }
		//Copy the meta group name at the beginning of tokenbuffer
		tokenBuffer[0] = '/';
		char* ptr1 = &(tokenBuffer[1]);
		while ((*ptr2) && (*ptr2) != ' ')
		{
			*ptr1 = *ptr2;
			ptr1++;
			ptr2++;
		}
		*ptr1 = '\0';
		metaGroupMask = 0;
	}
	else if (strncmp(tokenBuffer, "LEAVING GROUP", 13) == 0)
	{
		currentToken = PDMS_LEAVE_METAGROUP;
		metaGroupMask = 0;
	}
}