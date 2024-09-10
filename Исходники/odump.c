static void function (file const * file, off_t extent, flag_t flags)

{
	unsigned object = 0;
	unsigned lineno = 0;
	unsigned offset = 0;
	unsigned length = 0;
	char memory [_ADDRSIZE +  1];
	char symbol [_NAMESIZE];
	char string [_LINESIZE];
	char * sp;
	signed c;
	while ((c = getc (stdin)) != EOF)
	{
		if ((c == '#') || (c == ';'))
		{
			do 
			{
				c = getc (stdin);
			}
			while (nobreak (c));
			lineno++;
			continue;
		}
		if (isspace (c))
		{
			if (c == '\n')
			{
				lineno++;
			}
			continue;
		}
		length = 0;
		while (isdigit (c))
		{
			length *= 10;
			length += c - '0';
			c = getc (stdin);
		}
		while (isblank (c))
		{
			c = getc (stdin);
		}
		sp = symbol;
		if (isalpha (c) || (c == '_'))
		{
			do 
			{
				* sp++ = (char) (c);
				c = getc (stdin);
			}
			while (isident (c));
		}
		while (isblank (c))
		{
			c = getc (stdin);
		}
		if (c == '[')
		{
			* sp++ = (char) (c);
			c = getc (stdin);
			while (isblank (c))
			{
				c = getc (stdin);
			}
			while (isdigit (c))
			{
				* sp++ = (char) (c);
				c = getc (stdin);
			}
			while (isblank (c))
			{
				c = getc (stdin);
			}
			* sp = (char) (0);
			if (c != ']')
			{
				error (1, EINVAL, "Have '%s' without ']' on line %d", symbol, lineno);
			}
			* sp++ = (char) (c);
			c = getc (stdin);
		}
		* sp = (char) (0);
		while (isblank (c))
		{
			c = getc (stdin);
		}
		sp = string;
		while (nobreak (c))
		{
			* sp++ = (char) (c);
			c = getc (stdin);
		}
		* sp = (char) (0);
		if (length)
		{
			byte buffer [length];
			if (read (file->file, buffer, length) == (signed) (length))
			{
				if (! object++)
				{
					for (c = 0; c < _ADDRSIZE +  65; c++)
					{
						putc ('-', stdout);
					}
					putc ('\n', stdout);
				}
				printf ("%s %u %s\n", hexoffset (memory, sizeof (memory), offset), length, symbol);
				hexview (buffer, offset, length, stdout);
				for (c = 0; c < _ADDRSIZE +  65; c++)
				{
					putc ('-', stdout);
				}
				putc ('\n', stdout);
			}
		}
		offset += length;
		lineno++;
	}
	if (_allclr (flags, ODD_SILENCE))
	{
		if (offset != (unsigned) (extent))
		{
			error (0, 0, "%s has %u bytes, not " OFF_T_SPEC " bytes.", file->name, offset, extent);
		}
	}
	return;
}