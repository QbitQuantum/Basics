/*
 * Number scanner
 *
 * state |      ch         | next state
 * ------+-----------------+--------------------------
 *   0   | [0]             | 1
 *   0   | [1-9]           | 4
 *   0   | .               | error (should never occur)
 *   1   | [xX]            | 2
 *   1   | [0-7]           | 3
 *   1   | [89a-wyzA-WYZ_] | error invalid digit
 *   1   | .               | return 0
 *   2   | [0-9a-fA-F]     | 2
 *   2   | [g-zG-Z_]       | error invalid hex digit
 *   2   | .               | return (hex-number) if TOS != [xX] else error
 *   3   | [0-7]           | 3
 *   3   | [89a-zA-Z_]     | error invalid octal digit
 *   3   | .               | return (octal-number)
 *   4   | [0-9]           | 4
 *   4   | [a-zA-Z_]       | error invalid decimal digit
 *   4   | .               | return (decimal-number)
 *
 * All non-identifier characters [^a-zA-Z_0-9] terminate the scan
 * and return the value. This is not entirely correct, but close
 * enough (should check punctuators as trailing context, but the
 * char_table is not adapted to that and it is questionable whether
 * it is worth the trouble).
 * All non-iso-8859-1 characters are an error.
 */
static int scan_number(int ch)
{
	int state = 0;
	int base = 10;
	empty_char_stack();

	while(1)
	{
		if(!isisochar(ch))
			xyyerror("Invalid digit\n");

		switch(state)
		{
		case 0:
			if(isdigit(ch))
			{
				push_char(ch);
				if(ch == '0')
					state = 1;
				else
					state = 4;
			}
			else
				internal_error(__FILE__, __LINE__, "Non-digit in first number-scanner state\n");
			break;
		case 1:
			if(ch == 'x' || ch == 'X')
			{
				push_char(ch);
				state = 2;
			}
			else if(ch >= '0' && ch <= '7')
			{
				push_char(ch);
				state = 3;
			}
			else if(isalpha(ch) || ch == '_')
				xyyerror("Invalid number digit\n");
			else
			{
				unget_unichar(ch);
				mcy_lval.num = 0;
				return tNUMBER;
			}
			break;
		case 2:
			if(isxdigit(ch))
				push_char(ch);
			else if(isalpha(ch) || ch == '_' || !isxdigit(tos_char_stack()))
				xyyerror("Invalid hex digit\n");
			else
			{
				base = 16;
				goto finish;
			}
			break;
		case 3:
			if(ch >= '0' && ch <= '7')
				push_char(ch);
			else if(isalnum(ch) || ch == '_')
				xyyerror("Invalid octal digit\n");
			else
			{
				base = 8;
				goto finish;
			}
			break;
		case 4:
			if(isdigit(ch))
				push_char(ch);
			else if(isalnum(ch) || ch == '_')
				xyyerror("Invalid decimal digit\n");
			else
			{
				base = 10;
				goto finish;
			}
			break;
		default:
			internal_error(__FILE__, __LINE__, "Invalid state in number-scanner\n");
		}
		ch = get_unichar();
	}
finish:
	unget_unichar(ch);
	push_char(0);
	mcy_lval.num = strtoul(get_char_stack(), NULL, base);
	return tNUMBER;
}