//evaluates and * and / expression
void CStateParser::Term(CTokenizer &tok,CStateManager &StateManager)
{
         
     Primary(tok,StateManager);
     
     //search for operators 
     while( tok.CheckToken("*",false) || tok.CheckToken("/",false)  || 
            tok.CheckToken("=",false) || tok.CheckToken("!=",false) ||
            tok.CheckToken("<",false) || tok.CheckToken("<=",false) ||
            tok.CheckToken(">",false) || tok.CheckToken(">=",false) ||
            tok.CheckToken(":",false) || /*tok.CheckToken("&&",false) || 
            tok.CheckToken("||",false)||*/ tok.CheckToken("^^",false) ||
            tok.CheckToken("&",false) || tok.CheckToken("~",false)  ||
            tok.CheckToken("|",false) || tok.CheckToken("^",false)  || 
            tok.CheckToken("%",false) || tok.CheckToken("(", false) 	
			&& !tok.AtEndOfLine() )  
     {  
      
            if( tok.CheckToken("*") )
            {
                //Have we a ** operator?
                if( tok.CheckToken("*") )
                {
                    Primary(tok,StateManager);
                    StateManager.AddInstruction(OP_SQUARE,0,"#");
                    
                }else
                {
                    Primary(tok,StateManager);
                    StateManager.AddInstruction(OP_MUL,0,"#");
                }
            }
         
           if( tok.CheckToken("/") )
           {
               Primary(tok,StateManager);
               StateManager.AddInstruction(OP_DIV,0,"#");
           }
           
           if( tok.CheckToken("=") )
           {    
                //check for intervall operator
                if( tok.CheckToken("(") )
                {
                    //evaluate first expression                   
                    EvaluateExpression(tok,StateManager);
                    if( !tok.CheckToken(",") )
                        Error("Expectetd a , in intervall operator",tok);

                    //evaluate second expression 
                    EvaluateExpression(tok,StateManager);
                    
                    //intervall op =(,)
                    if( tok.CheckToken(")") )
                    {
                        StateManager.AddInstruction(OP_INTERVALOP4,0,"#");
                    }else if( tok.CheckToken("]") )
                    {
                         StateManager.AddInstruction(OP_INTERVALOP3,0,"#");
                    }
                    
                }else if (tok.CheckToken("[") )
                {
                    //evaluate first expression                   
                    EvaluateExpression(tok,StateManager);
                    if( !tok.CheckToken(",") )
                        Error("Expectetd a , in intervall operator",tok);

                    //evaluate second expression 
                    EvaluateExpression(tok,StateManager);
                    
                    //intervall op =[,)
                    if( tok.CheckToken(")") )
                    {
                       StateManager.AddInstruction(OP_INTERVALOP2,0,"#");
                    }else if( tok.CheckToken("]") )
                    {
                         StateManager.AddInstruction(OP_INTERVALOP1,0,"#");
                    }
                      
                }
                else // is the = op
                {                
					//evalute the right side of the operator
					Primary(tok,StateManager);
					StateManager.AddInstruction(OP_EQUAL,0,"#");
                }
           }
           
           if( tok.CheckToken(":") )
           {    //evalute the right side of the operator
                if(tok.CheckToken("="))
                {
                 EvaluateExpression(tok,StateManager);
                 PrintMessage("TODO:Handel assign operator :=");
                }
           }
           
           if( tok.CheckToken("!=") )
           {    //evalute the right side of the operator
                //check for intervall operator
                if( tok.CheckToken("(") )
                {
                    //evaluate first expression                   
                    EvaluateExpression(tok,StateManager);
                    if( !tok.CheckToken(",") )
                        Error("Expectetd a , in intervall operator",tok);

                    //evaluate second expression 
                    EvaluateExpression(tok,StateManager);
                    
                    //intervall op !=(,)
                    if( tok.CheckToken(")") )
                    {
                        StateManager.AddInstruction(OP_INTERVALOP8,0,"#");
                    }else if( tok.CheckToken("]") )
                    {
                         StateManager.AddInstruction(OP_INTERVALOP7,0,"#");
                    }
                    
                }else if (tok.CheckToken("[") )
                {
                    //evaluate first expression                   
                    EvaluateExpression(tok,StateManager);
                    if( !tok.CheckToken(",") )
                        Error("Expectetd a , in intervall operator",tok);

                    //evaluate second expression 
                    EvaluateExpression(tok,StateManager);
                    
                    //intervall op !=[,)
                    if( tok.CheckToken(")") )
                    {
                       StateManager.AddInstruction(OP_INTERVALOP6,0,"#");
                    }else if( tok.CheckToken("]") )
                    {
                         StateManager.AddInstruction(OP_INTERVALOP5,0,"#");
                    }
                      
                }
                else // is the != op
                {                
					//evalute the right side of the operator
					//EvaluateExpression(tok,StateManager);
					Primary(tok,StateManager);
					StateManager.AddInstruction(OP_NOTEQUAL,0,"#");
					continue;
                }
                //EvaluateExpression(tok,StateManager);
                //StateManager.AddInstruction(OP_NOTEQUAL,0,"#");
           }
           
           if( tok.CheckToken("<") )
           {    //evalute the right side of the operator
                EvaluateExpression(tok,StateManager);
                StateManager.AddInstruction(OP_LESS,0,"#");
           }
           
           if( tok.CheckToken("<=") )
           {    //evalute the right side of the operator
                EvaluateExpression(tok,StateManager);
                StateManager.AddInstruction(OP_LESSEQUAL,0,"#");
           }
           
           if( tok.CheckToken(">") )
           {    //evalute the right side of the operator
                EvaluateExpression(tok,StateManager);
                StateManager.AddInstruction(OP_GREATER,0,"#");
           }
           
           if( tok.CheckToken(">=") )
           {    //evalute the right side of the operator
                EvaluateExpression(tok,StateManager);
                StateManager.AddInstruction(OP_GRAETEREQUAL,0,"#");
           }
           
//            if( tok.CheckToken("&&") )
//            {    //evalute the right side of the operator
//                 EvaluateExpression(tok,StateManager);
//                 StateManager.AddInstruction(OP_LOGAND,0,"#");
//            }
           
//            if( tok.CheckToken("||") )
//            {    //evalute the right side of the operator
//                 EvaluateExpression(tok,StateManager);
//                 StateManager.AddInstruction(OP_LOGOR,0,"#");
//            }
           
           if( tok.CheckToken("^^") ) // is this realy needed?
                                      //FIXME:Cant read ^^
           {    //evalute the right side of the operator
                EvaluateExpression(tok,StateManager);
                StateManager.AddInstruction(OP_LOGXOR,0,"#");
           }
           
           if( tok.CheckToken("&") ) 
           {    //evalute the right side of the operator
                Primary(tok,StateManager);
                StateManager.AddInstruction(OP_AND,0,"#");
           }
           
           if( tok.CheckToken("~") ) 
           {    //evalute the right side of the operator
                Primary(tok,StateManager);
                StateManager.AddInstruction(OP_NOT,0,"#");
           }
           
           if( tok.CheckToken("|") ) 
           {    //evalute the right side of the operator
                Primary(tok,StateManager);
                StateManager.AddInstruction(OP_OR,0,"#");
           }
           
           if( tok.CheckToken("^") ) 
           {    //evalute the right side of the operator
                Primary(tok,StateManager);
                StateManager.AddInstruction(OP_XOR,0,"#");
           }
           
           if( tok.CheckToken("%") ) 
           {    //evalute the right side of the operator
                Primary(tok,StateManager);
                StateManager.AddInstruction(OP_MOD,0,"#");
           }

		   if (tok.CheckToken("("))
		   {
			   EvaluateExpression(tok,StateManager);

			   if( !tok.CheckToken(")") )
				   Error("Missing )",tok);
		   }
           
      }
     
}