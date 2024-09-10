// LET command translate function
TokenStatus letTranslate(Translator &translator, Token *commandToken,
	Token *&token)
{
	TokenStatus status;
	int column;
	bool hidden;
	DataType dataType;
	bool done;
	TokenStack letStack;
	bool haveSubStr = false;

	if (commandToken == NULL)
	{
		column = token->column();
		hidden = true;
	}
	else  // delete unneeded command token and get another token
	{
		column = commandToken->column();
		delete commandToken;
		hidden = false;
	}
	dataType = Any_DataType;
	do
	{
		if ((status = translator.getOperand(token, dataType,
			Translator::All_Reference)) != Good_TokenStatus)
		{
			if (token->column() > column)
			{
				return status;
			}
			// next token determines error
			Token *nextToken;
			if ((status = translator.getToken(nextToken)) != Good_TokenStatus)
			{
				status = ExpCmd_TokenStatus;
			}
			if (nextToken->isCode(Comma_Code) || nextToken->isCode(Eq_Code))
			{
				status = ExpAssignItem_TokenStatus;
			}
			else
			{
				status = ExpCmd_TokenStatus;
			}
			delete nextToken;
			return status;
		}

		// get and check next token for comma or equal
		status = translator.getToken(token);
		if (token->isCode(Comma_Code))
		{
			done = false;
		}
		else if (token->isCode(Eq_Code))
		{
			done = true;
		}
		else  // invalid token or parser error
		{
			if (translator.table().hasFlag(translator.doneStackTopToken(),
				SubStr_Flag))
			{
				delete translator.doneStackPop();
			}
			return ExpEqualOrComma_TokenStatus;
		}

		// check if this is a sub-string assignment
		if (translator.table().hasFlag(translator.doneStackTopToken(),
			SubStr_Flag))
		{
			// delete comma/equal token, use sub-string function token
			delete token;

			// get sub-string function token from rpn item on top of stack
			// (delete rpn item since it was not appended to output)
			RpnItem *rpnItem = translator.doneStackPop();
			token = rpnItem->token();
			rpnItem->setToken(NULL);  // prevent delete of token
			delete rpnItem;

			// change to assign sub-string code (first associated code)
			translator.table().setToken(token,
				translator.table().associatedCode(token->code()));

			haveSubStr = true;
		}
		else  // use comma/equal token
		{
			// change token to appropriate assign code
			translator.table().setToken(token, Assign_Code);
			status = translator.processDoneStackTop(token);
			if (status != Good_TokenStatus)
			{
				return status;
			}
		}
		letStack.push(token);  // save token

		// get data type for assignment
		if (dataType == Any_DataType)
		{
			dataType = token->dataType();
		}

		token = NULL;
	}
	while (!done);

	// get expression for value to assign
	if ((status = translator.getExpression(token,
		translator.equivalentDataType(dataType))) != Done_TokenStatus)
	{
		if (status == Parser_TokenStatus && token->isDataType(None_DataType))
		{
			status = ExpOpOrEnd_TokenStatus;
		}
		return status;
	}

	Token *letToken = letStack.pop();
	if (!letStack.isEmpty())
	{
		if (haveSubStr)
		{
			// add each token saved in let stack except the last
			do
			{
				// change to keep code (second associated code)
				translator.table().setToken(letToken,
					translator.table().associatedCode(letToken->code()));

				// append to output and pop next token from let stack
				translator.outputAppend(letToken);
				letToken = letStack.pop();
			}
			while (!letStack.isEmpty());  // continue until last token
		}
		else  // have a multiple assignment, change to list code
		{
			translator.table().setToken(letToken,
				translator.table().secondAssociatedCode(letToken->code()));
		}
	}

	// drop expresion result from done stack, append last assignment token
	translator.doneStackDrop();
	translator.outputAppend(letToken);

	// set hidden LET flag if needed
	if (!hidden)
	{
		letToken->addSubCode(Option_SubCode);
	}

	// check terminating token for end-of-statement
	if (!translator.table().hasFlag(token, EndStmt_Flag))
	{
		return ExpOpOrEnd_TokenStatus;
	}

	return Done_TokenStatus;
}