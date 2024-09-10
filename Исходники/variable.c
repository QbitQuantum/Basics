/*---NOTE:- SINCE I HAVE USED STACKS USING LIST IMPLEMENTATION,TO DELETE FIRST ELEMENT,I USE POP &                  LIKEWISWE.---*/
void infix_to_postfix(List infix_l,List postfix_l)
{
	char *p;
	int cnt;
	Stack stack;
	stack = CreateStack();
	char token[MAXNAME],tmp[MAXNAME];
	KindType type;

	do
	{
		/*since i am using stack implementation using linked lists,to get the first value in 
		  list i will be using Top of stack,to delete first element,use pop*/
		if(!IsEmpty(infix_l))
		{
			Gettoken(token,infix_l);
		}
		switch(type = kind(token))
		{
			case OPERAND:
				cnt = Count(postfix_l);
				InsertAfter(token,postfix_l,cnt);
				break;
			case LEFTPAREN:
				Push(token,stack);
				break;
			case RIGHTPAREN:
				while(!IsEmpty(stack))
				{
					TopandPop(stack,tmp);
					
					if(kind(tmp)==LEFTPAREN)
						break;

					cnt = Count(postfix_l);
					InsertAfter(tmp,postfix_l,cnt);
				}
				break;
			case UNARYOP:
			case BINARYOP:
				do
				{

			 	      if(IsEmpty(stack))
				      {
				      		break;
				      }
				      else
				      {
				      	p = Top(stack);
					strcpy(tmp,p);
					if(kind(tmp)==LEFTPAREN)
						break;
					else if(priority(tmp)!=priority(token) &&                                                                                        priority(token)==MAXPRIORITY)
						break;
					else if(priority(token) > priority(tmp))
						break;

					else
					{
						TopandPop(stack,tmp);
						cnt = Count(postfix_l);
						InsertAfter(tmp,postfix_l,cnt);
					}

				       }
				  }while(1);

				  Push(token,stack);
				  break;
			  
		}//switch
		}while(!IsEmpty(infix_l));
		
		while(!IsEmpty(stack))
                {
                         TopandPop(stack,tmp);
                         cnt = Count(postfix_l);
                         InsertAfter(tmp,postfix_l,cnt);
                }

}