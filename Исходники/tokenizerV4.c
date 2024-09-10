char *TKGetNextToken( TokenizerT * tk )
{	// Begin TKGetNextToken

	/**
	 * Check that the string is not empty.
	 */

	if(tk->str == '\0')
	{	// Begin if-statement
		return '\0';
	}	// End if-statement

	/*
	 * calloc(tk->strSize-tk->curChar, sizeof(char));
	 * This will assign for the first token the amount of space
	 * required to contain the entire string in the case that the first token
	 * the whole input is one token. The next time the function is used it will
	 * allocate the size of the string minus the amount of characters already
	 * surpassed.
	 */
	char *arr = calloc(tk->strSize-tk->curChar, sizeof(char));

	int i = 0; // Current index in arr[i]

	while ((char)tk->str[tk->curChar] != '\0')
	{	// Begin while-loop

		/**
		 * This if-statement will check if tk->str[tk->curChar] is
		 * a whitespace character. If a whitespace character is found
		 * the current character which contains the whitespace
		 * will be incremented over (e.g. tk->curChar++) so that the
		 * next time the method is called it will start after the
		 * whitespace character.
		 */
		if((char)tk->str[tk->curChar] == ' ')
		{	// Begin if-statement
			tk->curChar++;
			if((char)tk->str[tk->curChar] == '\0')
			{
				arr[i] = ' ';
				break;
			}
		}	// End if-statement
		else if(isalpha(tk->str[tk->curChar]))
		{	// Begin if-statement
			arr[i] = tk->str[tk->curChar];	// Store current str[index] in arr[i]
			i++;
			tk->curChar++;

			/**
			 * Continue tokenizing word while next character is an alphanumeric
			 * character.
			 */
			while(isalnum(tk->str[tk->curChar]) && (char)tk->str[tk->curChar] != '\0')
			{	// Begin while loop
				arr[i] = tk->str[tk->curChar];
				i++;
				tk->curChar++;
			}	//
			tk->tokenDesc[tk->manyTokens] = "word";
			break;
		}
		else if(isdigit(tk->str[tk->curChar]))
		{
			arr[i] = tk->str[tk->curChar];
			i++;
			tk->curChar++;
			while(isdigit(tk->str[tk->curChar]) && (char)tk->str[tk->curChar] != '\0')
			{
				arr[i] = tk->str[tk->curChar];
				i++;
				tk->curChar++;
			}
			if((char)tk->str[tk->curChar] == 'L')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "long decimal number";
				tk->curChar++;
				break;
			}
			else if((char)tk->str[tk->curChar] == '.')
			{
				tk->tokenDesc[tk->manyTokens] = "float";
				arr[i] = tk->str[tk->curChar];
				i++;
				tk->curChar++;
				while(isdigit(tk->str[tk->curChar]))
				{
					arr[i] = tk->str[tk->curChar];
					i++;
					tk->curChar++;
					if((char)tk->str[tk->curChar] == 'e')
					{
						arr[i] = tk->str[tk->curChar];
						i++;
						tk->curChar++;
						if((char)tk->str[tk->curChar] == '-' || (char)tk->str[tk->curChar] == '+')
						{
							arr[i] = tk->str[tk->curChar];
							i++;
							tk->curChar++;
							if(!isdigit(tk->str[tk->curChar]))
							{
								tk->tokenDesc[tk->manyTokens] = "improper float";
								break;
							}
							while(isdigit(tk->str[tk->curChar]))
							{
								arr[i] = tk->str[tk->curChar];
								i++;
								tk->curChar++;
							}
							tk->tokenDesc[tk->manyTokens] = "scientific float";
							break;
						}
						else
						{
							tk->tokenDesc[tk->manyTokens] = "improper float";
							break;
						}
					}
				}
				break;
			}
			tk->tokenDesc[tk->manyTokens] = "decimal number";
			tk->curChar++;
			break;
		}
		else if((char)tk->str[tk->curChar] == '[')
		{
			arr[i] = tk->str[tk->curChar];
			tk->tokenDesc[tk->manyTokens] = "left brace";
			tk->curChar++;
			break;
		}
		else if((char)tk->str[tk->curChar] == ']')
		{
			arr[i] = tk->str[tk->curChar];
			tk->tokenDesc[tk->manyTokens] = "right brace";
			tk->curChar++;
			break;
		}
		else if((char)tk->str[tk->curChar] == '(')
		{
			arr[i] = tk->str[tk->curChar];
			tk->tokenDesc[tk->manyTokens] = "left parentheses";
			tk->curChar++;
			break;
		}
		else if((char)tk->str[tk->curChar] == ')')
		{
			arr[i] = tk->str[tk->curChar];
			tk->tokenDesc[tk->manyTokens] = "right parentheses";
			tk->curChar++;
			break;
		}
		else if((char)tk->str[tk->curChar] == '+')
		{
			arr[i] = tk->str[tk->curChar];
			i++;
			tk->tokenDesc[tk->manyTokens] = "plus";
			tk->curChar++;
			if((char)tk->str[tk->curChar] == '=')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "plusequals";
				tk->curChar++;
			}
			else if((char)tk->str[tk->curChar] == '+')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "increment";
				tk->curChar++;
			}
			break;
		}
		else if((char)tk->str[tk->curChar] == '-')
		{
			arr[i] = tk->str[tk->curChar];
			i++;
			tk->tokenDesc[tk->manyTokens] = "minus";
			tk->curChar++;
			if((char)tk->str[tk->curChar] == '=')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "minusequals";
				tk->curChar++;
			}
			else if((char)tk->str[tk->curChar] == '-')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "decrement";
				tk->curChar++;
			}
			break;
		}
		else if((char)tk->str[tk->curChar] == '\%')
		{
			arr[i] = tk->str[tk->curChar];
			i++;
			tk->curChar++;

			if((char)tk->str[tk->curChar] == 'd')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "signed decimal integer conversion character";
			}
			else if((char)tk->str[tk->curChar] == 'u')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "unsigned decimal integer conversion character (used in printf only)";
			}
			else if((char)tk->str[tk->curChar] == 'x')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "unsigned hexidecimal integer conversion character";
			}
			else if((char)tk->str[tk->curChar] == 'h')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "unsigned short integer conversion character (used in scanf only)";
			}
			else if((char)tk->str[tk->curChar] == 'o')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "unsigned octal integer conversion character";
			}
			else if((char)tk->str[tk->curChar] == 'c')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "single character conversion character";
			}
			else if((char)tk->str[tk->curChar] == 's')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "null terminated string conversion character";
			}
			else if((char)tk->str[tk->curChar] == 'f')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "fixed point notation for float or double conversion character";
			}
			else if((char)tk->str[tk->curChar] == 'e')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "scientific notation for float or double conversion character (printf only)";
			}
			else if((char)tk->str[tk->curChar] == 'g')
			{
				arr[i] = tk->str[tk->curChar];
				tk->tokenDesc[tk->manyTokens] = "use %e or %f, whichever is shorter conversion character (printf only)";
			}
			tk->curChar++;
			break;
		}
	}	// End while-loop
	return arr;
}	// End TKGetNextToken