struct IntInstr* GenIntCode (struct TreeNode* tree) {
    struct TreeNode *root = tree;
    IntInstr *b1,*b2,*cond,*jump2else,*thenpart,*jump2end,*elsepart,*endif;

    switch (root->type) {
    case STMT_LIST:
	b1 = GenIntCode(root->child[0]);	
	b2 = GenIntCode(root->child[1]);	
        Concatenate(b1,b2);
        return b1;
    case EMPTY_STMT:
        return newIntInstr(OP_NOP,NULL,NULL);
    case EXPR_STMT : 
        b1 = GenIntCode(root->child[0]);
        b2 = newIntInstr(OP_DISCARD,NULL,NULL);
        return Concatenate(b1,b2);
    case PRINT_STMT :
        b1 = GenIntCode(root->child[0]);
        b2 = newIntInstr(OP_PRINT,NULL,NULL);
        return Concatenate(b1,b2);
    case INPUT_STMT :
        return newIntInstr(OP_INPUT,root->symbol,NULL);
    case IFTHEN_STMT :
        cond = GenIntCode(root->child[0]);
        jump2end = newIntInstr(OP_JMPF,NULL,NULL); 
        thenpart = GenIntCode(root->child[1]);
        endif = newIntInstr(JUMPTARGET,NULL,jump2end);
	jump2end->target = endif;	

        Concatenate (cond, jump2end);
	Concatenate (jump2end, thenpart);
	Concatenate (thenpart, endif);
	return cond; 
   case IFTHENELSE_STMT :
	cond = GenIntCode(root->child[0]);
        jump2else = newIntInstr(OP_JMPF,NULL,NULL);     
    	thenpart = GenIntCode(root->child[1]);
        elsepart = PrefixJT(GenIntCode(root->child[2]),jump2else);
 	
	jump2else->target =  elsepart;
        jump2end = newIntInstr(OP_JMP,NULL,NULL);
	endif = newIntInstr(JUMPTARGET,NULL,jump2end);	
	jump2end->target = endif;

	Concatenate (cond, jump2else);
	Concatenate (jump2else, thenpart);
	Concatenate (thenpart, jump2end);
	Concatenate (jump2end, elsepart);
	Concatenate (elsepart, endif);
	return cond; 
   case ERROR_STMT:
	return newIntInstr (OP_NOP,NULL,NULL);
   case EQUAL_EXPR:
	b1 = GenIntCode (root->child[0]);
	b2 = GenIntCode (root->child[1]);
	Concatenate (b1, b2);
	if (root->child[0]->rettype == T_STRING)
		return Concatenate (b1, newIntInstr (OP_STR_EQUAL,NULL,NULL));
	else
		return Concatenate (b1, newIntInstr (OP_BOOL_EQUAL,NULL,NULL));
   case ASSIGN_EXPR:
	b1 = GenIntCode (root->child[0]);
	b2 = newIntInstr (OP_GETTOP, root->symbol,NULL);
	return Concatenate (b1, b2);
   case CONCAT_EXPR:
	b1 = GenIntCode (root->child[0]);
	b2 = GenIntCode (root->child[1]);
	Concatenate (b1, b2);
	return Concatenate (b1, newIntInstr (OP_CONCAT,NULL,NULL));
   case IDENT_EXPR:
   case STR_EXPR:
	return newIntInstr (OP_PUSH, root->symbol,NULL);
   case COERCE_TO_STR:
	b1 = GenIntCode (root->child[0]);
	b2 = newIntInstr (OP_BOOL2STR,NULL,NULL);
	return Concatenate (b1, b2);
    }
    return newIntInstr (OP_NOP,NULL,NULL); // shouldn't happen 
}