struct assignNode* expr(struct assignNode* assign)
{
	struct varNode* op;
	struct varNode* oper2;
	int oper;

	ttype = getToken();
	if (ttype == NUM)
	{	
		//printf("NUM: %d\n",ttype);
		op = make_var();
		
		if(symSearch(token) == NULL)
		{
			symAdd(op);
		}
		
		assign->op1 = symSearch(token);
		
		/*assign->op1 = primary(assign->op1);

		ttype = getToken();
		if ((ttype == PLUS) | (ttype == MINUS) | (ttype == MULT) | (ttype == DIV))
		{	
			assign->oper = ttype; //op is set + - * /
			assign->op2 = primary(assign->op2);
		}
		
		ungetToken();
		return assign;*/
	} 
	else if (ttype == ID)
	{
		
		assign->op1 = symSearch(token);
		
		/*printf("ID: %d\n",ttype);

		assign->op1 = primary(assign->op1);
		printf("ASSIGN ID %s\n", assign->op1->id);
			
		ttype = getToken();
		printf("PLUS: %d\n",ttype);
		if ((ttype == PLUS) | (ttype == MINUS) | (ttype == MULT) | (ttype == DIV))
		{
			assign->oper = ttype;
				
			ttype = getToken();
			if(ttype == ID) 
				
			{
	printf("ID: %d\n",ttype);				

				assign->op2 = primary(assign->op2);
				return assign;									
			} 
				
			else
				
			{
					
				ungetToken();
				
			}
		
		} 
			
		else 
			
		{
				
			return NULL;
			
		}
*/		
	
	 }
	 
	 ttype = getToken();
	 if ((ttype == PLUS) | (ttype == MINUS) | (ttype == MULT) | (ttype == DIV))
	 {
		assign->oper = ttype;
	 }
		
	ttype = getToken();
	if (ttype == NUM)
	{	
		//printf("NUM: %d\n",ttype);
		op = make_var();
		
		if(symSearch(token) == NULL)
		{
			symAdd(op);
		}
		
		assign->op1 = symSearch(token);
		
		/*assign->op1 = primary(assign->op1);

		ttype = getToken();
		if ((ttype == PLUS) | (ttype == MINUS) | (ttype == MULT) | (ttype == DIV))
		{	
			assign->oper = ttype; //op is set + - * /
			assign->op2 = primary(assign->op2);
		}
		
		ungetToken();
		return assign;*/
	} 
	else if (ttype == ID)
	{
		
		assign->op2 = symSearch(token);
		
		/*printf("ID: %d\n",ttype);

		assign->op1 = primary(assign->op1);
		printf("ASSIGN ID %s\n", assign->op1->id);
			
		ttype = getToken();
		printf("PLUS: %d\n",ttype);
		if ((ttype == PLUS) | (ttype == MINUS) | (ttype == MULT) | (ttype == DIV))
		{
			assign->oper = ttype;
				
			ttype = getToken();
			if(ttype == ID) 
				
			{
	printf("ID: %d\n",ttype);				

				assign->op2 = primary(assign->op2);
				return assign;									
			} 
				
			else
				
			{
					
				ungetToken();
				
			}
		
		} 
			
		else 
			
		{
				
			return NULL;
			
		}
*/		
	
	 }
	 return assign;
}