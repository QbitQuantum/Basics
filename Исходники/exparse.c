Expr *MakeHandleFunc(void (*fn)(Expr *), int handle_token,
	int nparams, int returns_vec)
{
	Expr *expr = NULL;
	void *data = NULL;
	TOKEN *fntoken = cur_token;
	token = GetToken();
	if(token == OP_LPAREN)
	{
		/*
		 * Look for a handle to a declared type that matches
		 * the type specified by handle_token.
		 */
		token = GetToken();
		if(token == handle_token)
		{
			switch(token)
			{
				case DECL_COLOR_MAP:
					data = (void *)ColorMap_Copy((ColorMap *)cur_token->data);
					break;
			}
		}
		else
		{
			switch(handle_token)
			{
				case DECL_COLOR_MAP:
					ErrUnknown(token, "color map handle id", "expression syntax");
					break;
				default:
					ErrUnknown(token, "handle to a declared item",
						"expression syntax");
					break;
			}
		}
		/* Get the first comma if more params follow. */
		if(nparams > 0)
		{
			token = GetToken();
			if(token != OP_COMMA)
				ErrUnknown(token, ",", "expression syntax");
		}
		if(nparams < 2)
		{
			expr = ExprNew();
			expr->fn = fn;
			expr->data = data;
			expr->isvec = returns_vec ? 1 : 0;
			token = GetToken();
			expr->l = Term0();
			if(token == OP_RPAREN)
			{
				CheckParamCount(expr->l, fntoken->name, nparams);
				token = GetToken();
			}
			else
				ErrUnknown(token, ")", "expression syntax");
		}
		else
		{
			token = GetToken();
			expr = Term0();
			if(token == OP_RPAREN)
			{
				CheckParamCount(expr, fntoken->name, nparams);
				token = GetToken();
				if(expr != NULL)
				{
					expr->fn = fn;
					expr->data = data;
					expr->isvec = returns_vec ? 1 : 0;
				}
				else if(data != NULL)
				{
					switch(token)
					{
						case DECL_COLOR_MAP:
							ColorMap_Delete((ColorMap *)data);
							break;
					}
				}
			}
			else
				ErrUnknown(token, ")", "expression syntax");
		}
	}
	else
		ErrUnknown(token, "(", "expression syntax");
	return expr;
}