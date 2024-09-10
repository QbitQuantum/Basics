/*
============
Cbuf_Execute
============
*/
void Cbuf_ExecuteEx (cbuf_t *cbuf)
{
	int		i, j, cursize;
	char	*text;
	char	line[1024], *src, *dest;
	qbool	comment, quotes;

	cbuf_current = cbuf;

	while (cbuf->text_end > cbuf->text_start)
	{
		// find a \n or ; line break
		text = (char *)cbuf->text_buf + cbuf->text_start;

		cursize = cbuf->text_end - cbuf->text_start;
		comment = quotes = false;
		for (i = 0; i < cursize; i++)
		{
			if (text[i] == '\n')
				break;
			if (text[i] == '"')
				quotes = !quotes;
			if (comment || quotes)
				continue;

			if (text[i] == '/' && (i + 1) < cursize && text[i + 1] == '/')
				comment = true;
			else if (text[i] == ';')
				break;
		}

// don't execute lines without ending \n; this fixes problems with
// partially stuffed aliases not being executed properly
#ifndef SERVERONLY
		if (cbuf_current == &cbuf_svc && i == cursize)
			break;
#endif

		// Copy text to line, skipping carriage return chars
		src = text;
		dest = line;
		j = min (i, sizeof(line)-1);
		for ( ; j ; j--, src++) {
			if (*src != 13)
				*dest++ = *src;
		}
		*dest = 0;

// delete the text from the command buffer and move remaining commands down
// this is necessary because commands (exec, alias) can insert data at the
// beginning of the text buffer

		if (i == cursize)
		{
			cbuf->text_start = cbuf->text_end = cbuf->maxsize/2;
		}
		else
		{
			i++;
			cbuf->text_start += i;
		}

// execute the command line
		Cmd_ExecuteString (line);
		
		if (cbuf->wait)
		{	// skip out while text still remains in buffer, leaving it
			// for next frame
			cbuf->wait = false;
			break;
		}
	}

	cbuf_current = NULL;
}