struct conditionNode* condition()
{
	struct conditionNode* cNode;
	struct varNode* op1;
	struct varNode* op2;
	struct statementNode* tBranch;
	struct statementNode* fBranch;
	int op;

	cNode = make_condition();

	ttype = getToken();
	if ((ttype == ID)|(ttype == NUM))
	{
		ungetToken(); //ungetToken since it still be parsed
		cNode->op1 = primary(); //left operand of a condition is a primary

		ttype = getToken();
		if ((ttype == GREATER)|(ttype == GTEQ)|(ttype == LESS)
			|(ttype == NOTEQUAL)|(ttype == LTEQ))
		{
			cNode->operator = ttype; //relop is set to >, <, etc.
		
			ttype = getToken();
			if ((ttype == ID)|(ttype == NUM))
			{
				ungetToken(); //ungetToken since it still be parsed
				cNode->op2 = primary(); //right operand of a condition is a primary
			
				ttype = getToken();
				if(ttype == RPAREN)
				{
					ttype = getToken();
					if(ttype == THEN)
					{
						cNode->trueBranch = stmt_list();
						return cNode;
					}
					else
					{
						return NULL;
					}
				}
				else
				{
					return NULL;
				}
			}
			else
			{
				return NULL;
			}
		}
		else
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}
}