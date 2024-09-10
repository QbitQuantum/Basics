unsigned function (char const * oldname, char const * newname)

{
	unsigned count = 0;
	signed c = getc (stdin);
	while (c != EOF)
	{
		if (isspace (c))
		{
			do 
			{
				putc (c, stdout);
				c = getc (stdin);
			}
			while (isspace (c));
			continue;
		}
		if (isalpha (c) || (c == '_'))
		{
			char string [255];
			char * sp = string;
			do 
			{
				* sp++ = (char) (c);
				c = getc (stdin);
			}
			while (isalnum (c) || (c == '_'));
			* sp = (char) (0);
			if (! strcmp (string, oldname))
			{
				count++;
				fputs (newname, stdout);
				continue;
			}
			fputs (string, stdout);
			continue;
		}
		if (isdigit (c))
		{
			do 
			{
				putc (c, stdout);
				c = getc (stdin);
			}
			while (isdigit (c) || (c == '.'));
			if ((c == 'x') || (c == 'X'))
			{
				do 
				{
					putc (c, stdout);
					c = getc (stdin);
				}
				while (isxdigit (c));
			}
			if ((c == 'e') || (c == 'E'))
			{
				putc (c, stdout);
				c = getc (stdin);
				if ((c == '+') || (c == '-'))
				{
					putc (c, stdout);
					c = getc (stdin);
				}
				while (isdigit (c))
				{
					putc (c, stdout);
					c = getc (stdin);
				}
			}
			continue;
		}
		if (isquote (c))
		{
			signed o;
			putc (c, stdout);
			o = getc (stdin);
			while (nomatch (o, c))
			{
				if ((char) (o) == '\\')
				{
					putc (o, stdout);
					o = getc (stdin);
				}
				putc (o, stdout);
				o = getc (stdin);
			}
			putc (c, stdout);
			c = getc (stdin);
			continue;
		}
		if (c == '/')
		{
			putc (c, stdout);
			c = getc (stdin);
			if (c == '/')
			{
				while (nobreak (c))
				{
					putc (c, stdout);
					c = getc (stdin);
				}
				putc ('\n', stdout);
				c = getc (stdin);
				continue;
			}
			if (c == '*')
			{
				while (nomatch (c, '/'))
				{
					while (nomatch (c, '*'))
					{
						putc (c, stdout);
						c = getc (stdin);
					}
					putc (c, stdout);
					c = getc (stdin);
				}
				putc ('/', stdout);
				c = getc (stdin);
				continue;
			}
			continue;
		}
		putc (c, stdout);
		c = getc (stdin);
	}
	return (count);
}