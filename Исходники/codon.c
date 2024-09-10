/********************************************************************
*
*	print_label_to_buffer_all_ex(buf, label, pos, strand, extra_space)
*
*	print a label (with label_name=label, position=pos, 
*	orientation = strand, extra_space = extra_space for partial start)
*	into the current buffer
*	return the offset of the buffer pointer to the current buffer
*	Has an option to strip/not-strip semicolons for hardline old blast
*	users.
*
*********************************************************************/
NLM_EXTERN Int4 print_label_to_buffer_all_ex(CharPtr buf, CharPtr label, 
		Int4 pos, Uint1 strand, Boolean extra_space, Boolean is_html, 
		Int4 label_space, Int4 num_space, Boolean show_strand, 
		Boolean strip_semicolon)
{
	Int4 len;
	Char symbol;
	Char temp[100];
	Int4 i = 0;
	CharPtr str;
	Int4 max_b_space;

	/*
	*	print the label to the buffer
	*/
	max_b_space = label_space + 1;
	len = 0;
	if(label)
	{
		if (strip_semicolon)
		{
			str= StrTok(label, ":");
			if(str == NULL)
				str = label;
			else
			{
				str = StrTok(NULL, ":");
				if(str == NULL)
					str = label;
			}
		}
		else
		{
			str = label;
		}
		len = MIN(max_b_space-1, (Int4)StringLen(str));
		StringNCpy(buf, str, len);
		i = len;
		if(is_html)
		{
			sprintf(buf+i, "</a>");
			i += 4;
		}
		buf[i++] = ' ';
		++len;
	}
	
	/*add the leftover empty space */
	for(; len<max_b_space; ++len)
		buf[i++] = ' ';

	if(show_strand)
	{
		symbol = ' ';
		if(strand == Seq_strand_plus)
			symbol = '>';
		if(strand == Seq_strand_minus)
			symbol = '<';
		buf[i++] = ' ';
		buf[i++] = symbol;
		buf[i++] = ' ';
	}

	len = 0;
	if(pos != -1)
	{
		sprintf(buf+i, "%ld", (long) pos);
		sprintf(temp, "%ld", (long) pos);
		len = StringLen(temp);
		i += len;
	}

	if(extra_space)	/*for partial codon*/
		++len;
	max_b_space = num_space + 1;
	for(; len <max_b_space; ++len)
		buf[i++] = ' ';
	return i;
}