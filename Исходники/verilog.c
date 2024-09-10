static void processFunction (tokenInfo *const token)
{
	int c;
	tokenInfo *classType;

	/* Search for function name
	 * Last identifier found before a '(' or a ';' is the function name */
	c = skipWhite (vGetc ());
	do
	{
		readIdentifier (token, c);
		c = skipWhite (vGetc ());
		/* Identify class type prefixes and create respective context*/
		if (isLanguage (Lang_systemverilog) && c == ':')
		{
			c = vGetc ();
			if (c == ':')
			{
				verbose ("Found function declaration with class type %s\n", vStringValue (token->name));
				classType = newToken ();
				vStringCopy (classType->name, token->name);
				classType->kind = K_CLASS;
				createContext (classType);
				currentContext->classScope = TRUE;
			}
			else
			{
				vUngetc (c);
			}
		}
	} while (c != '(' && c != ';' && c != EOF);

	if ( vStringLength (token->name) > 0 )
	{
		verbose ("Found function: %s\n", vStringValue (token->name));

		/* Create tag */
		createTag (token);

		/* Get port list from function */
		processPortList (c);
	}
}