static ssize_t
qp_write(Sfio_t* sp, const void* buf, size_t n, Sfdisc_t* disc)
{
	register State_t*	state = (State_t*)CODEX(disc)->data;
	register unsigned char*	s;
	register unsigned char*	e;
	register int		c;
	register int		col;

 again:
	if (state->pp)
	{
		s = state->prv;
		e = state->pp;
		state->col = 0;
	}
	else
	{
		s = (unsigned char*)buf;
		e = s + n;
		col = state->col;
	}
	for (;;)
	{
		if (s >= e)
		{
			if (state->pp)
			{
				state->pp = 0;
				state->col = col;
				goto again;
			}
			break;
		}
		c = *s++;
		if (!col++)
		{
			if (c == 'F')
			{
				if ((e - s) < 4)
				{
					s--;
					col--;
					state->pp = state->prv;
					for (c = 0; c < (e - s); ++c)
						*state->pp++ = s[c];
					break;
				}
				else if (s[0] == 'r' && s[1] == 'o' && s[2] == 'm' && s[3] == ' ')
					goto quote;
			}
			else if (c == '.')
			{
				if ((e - s) < 1)
				{
					s--;
					col--;
					state->pp = state->prv;
					*state->pp++ = c;
					break;
				}
				else if (s[0] == '\r' || s[0] == '\n')
					goto quote;
			}
		}
		if (c == '\n')
		{
			col = 0;
			PUTCHAR(state, c);
			continue;
		}
		else if (col >= (LINE - 4))
		{
			col = 0;
			PUTCHAR(state, '=');
			PUTCHAR(state, '\n');
		}
		if (c == ' ' || c == '\t')
		{
			if ((e - s) < 1)
			{
				s--;
				col--;
				state->pp = state->prv;
				*state->pp++ = c;
				break;
			}
			else if (s[0] == '\r' || s[0] == '\n')
				goto quote;
			else
			{
				if (c == '\t')
					col |= 7;
				PUTCHAR(state, c);
				continue;
			}
		}
#if CC_NATIVE == CC_ASCII
		else if (c >= 0x21 && c <= 0x7e && c != '=')
#else
		else if (isprint(c) && !iscntrl(c) && c != '=')
#endif
		{
			PUTCHAR(state, c);
			continue;
		}
	quote:
		col += 2;
		PUTCHAR(state, '=');
		PUTCHAR(state, hex[(c >> 4) & 0xF]);
		PUTCHAR(state, hex[c & 0xF]);
	}
	state->col = col;
	return n;
}