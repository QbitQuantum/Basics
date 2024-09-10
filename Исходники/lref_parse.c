/* parse an entry reference string into routine, label & offset */
void lref_parse(unsigned char *label_ref, mstr* routine, mstr* label, int* offset)
{
	unsigned char 	ch, *c, *c1;
	int 		i, label_len;
	error_def	(ERR_RUNPARAMERR);

	routine->addr = label->addr = (char *)label_ref;
	*offset = 0;
	label_len = STRLEN((const char *)label_ref);
	for (i = 0, c = label_ref;  i < label_len;  i++)
	{
		ch = *c++;
		if (ch == '^'  ||  ch == '+')
		{
			label->len = i;

			if (ch == '+')
			{
				*offset = (int)STRTOL((const char *)c, (char**)&c1, 10);
				if (c == c1 ||*c1 != '^')
					rts_error(VARLSTCNT(1) ERR_RUNPARAMERR);
				c = c1 + 1;
			}
			routine->addr = (char *)c;
			routine->len = INTCAST(label_ref + label_len - c);
			break;
		}
	}
	if (routine->addr == (char *)label_ref)
	{
		routine->len = label_len;
		routine->addr = (char *)label_ref;
		label->len = 0;
	}
	if (!is_ident(routine))
		rts_error(VARLSTCNT(1) ERR_RUNPARAMERR);
	if (label->len && !is_ident(label))
		rts_error(VARLSTCNT(1) ERR_RUNPARAMERR);

	routine->len = routine->len > MAX_MIDENT_LEN ? MAX_MIDENT_LEN : routine->len;
	label->len = label->len > MAX_MIDENT_LEN ? MAX_MIDENT_LEN : label->len;
}