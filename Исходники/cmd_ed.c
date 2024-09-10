/*
 * Do the substitute command.
 * The current line is set to the last substitution done.
 */
static void
subCommand(const char * cmd, NUM num1, NUM num2)
{
	int	delim;
	char *	cp;
	char *	oldStr;
	char *	newStr;
	LEN	oldLen;
	LEN	newLen;
	LEN	deltaLen;
	LEN	offset;
	LINE *	lp;
	LINE *	nlp;
	BOOL	globalFlag;
	BOOL	printFlag;
	BOOL	didSub;
	BOOL	needPrint;
	char	buf[USERSIZE];

	if ((num1 < 1) || (num2 > lastNum) || (num1 > num2))
	{
		fprintf(stderr, "Bad line range for substitute\n");

		return;
	}

	globalFlag = FALSE;
	printFlag = FALSE;
	didSub = FALSE;
	needPrint = FALSE;

	/*
	 * Copy the command so we can modify it.
	 */
	strcpy(buf, cmd);
	cp = buf;

	if (isBlank(*cp) || (*cp == '\0'))
	{
		fprintf(stderr, "Bad delimiter for substitute\n");

		return;
	}

	delim = *cp++;
	oldStr = cp;

	cp = strchr(cp, delim);

	if (cp == NULL)
	{
		fprintf(stderr, "Missing 2nd delimiter for substitute\n");

		return;
	}

	*cp++ = '\0';

	newStr = cp;
	cp = strchr(cp, delim);

	if (cp)
		*cp++ = '\0';
	else
		cp = "";

	while (*cp) switch (*cp++)
	{
		case 'g':
			globalFlag = TRUE;
			break;

		case 'p':
			printFlag = TRUE;
			break;

		default:
			fprintf(stderr, "Unknown option for substitute\n");

			return;
	}

	if (*oldStr == '\0')
	{
		if (searchString[0] == '\0')
		{
			fprintf(stderr, "No previous search string\n");

			return;
		}

		oldStr = searchString;
	}

	if (oldStr != searchString)
		strcpy(searchString, oldStr);

	lp = findLine(num1);

	if (lp == NULL)
		return;

	oldLen = strlen(oldStr);
	newLen = strlen(newStr);
	deltaLen = newLen - oldLen;
	offset = 0;
	nlp = NULL;

	while (num1 <= num2)
	{
		offset = findString(lp, oldStr, oldLen, offset);

		if (offset < 0)
		{
			if (needPrint)
			{
				printLines(num1, num1, FALSE);
				needPrint = FALSE;
			}

			offset = 0;
			lp = lp->next;
			num1++;

			continue;
		}

		needPrint = printFlag;
		didSub = TRUE;
		dirty = TRUE;

		/*
		 * If the replacement string is the same size or shorter
		 * than the old string, then the substitution is easy.
		 */
		if (deltaLen <= 0)
		{
			memcpy(&lp->data[offset], newStr, newLen);

			if (deltaLen)
			{
				memcpy(&lp->data[offset + newLen],
					&lp->data[offset + oldLen],
					lp->len - offset - oldLen);

				lp->len += deltaLen;
			}

			offset += newLen;

			if (globalFlag)
				continue;

			if (needPrint)
			{
				printLines(num1, num1, FALSE);
				needPrint = FALSE;
			}

			lp = lp->next;
			num1++;

			continue;
		}

		/*
		 * The new string is larger, so allocate a new line
		 * structure and use that.  Link it in in place of
		 * the old line structure.
		 */
		nlp = (LINE *) malloc(sizeof(LINE) + lp->len + deltaLen);

		if (nlp == NULL)
		{
			fprintf(stderr, "Cannot get memory for line\n");

			return;
		}

		nlp->len = lp->len + deltaLen;

		memcpy(nlp->data, lp->data, offset);

		memcpy(&nlp->data[offset], newStr, newLen);

		memcpy(&nlp->data[offset + newLen],
			&lp->data[offset + oldLen],
			lp->len - offset - oldLen);

		nlp->next = lp->next;
		nlp->prev = lp->prev;
		nlp->prev->next = nlp;
		nlp->next->prev = nlp;

		if (curLine == lp)
			curLine = nlp;

		free(lp);
		lp = nlp;

		offset += newLen;

		if (globalFlag)
			continue;

		if (needPrint)
		{
			printLines(num1, num1, FALSE);
			needPrint = FALSE;
		}

		lp = lp->next;
		num1++;
	}

	if (!didSub)
		fprintf(stderr, "No substitutions found for \"%s\"\n", oldStr);
}