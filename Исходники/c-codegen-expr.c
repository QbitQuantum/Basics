int moduloExprCodegen(c_tree tree, int *registerNo, int topLevel,
		int getAddress, const char *breakLabel, const char *continueLabel)
{
	c_tree op2 = TREE_EXPR_OPERAND(tree,1);

	c_tree op1 = TREE_EXPR_OPERAND(tree,0);

	if (!topLevel)
	{
		int op1Register = c_codegen_recurse(op1,
				registerNo, topLevel, getAddress, breakLabel, continueLabel);

		if (TREE_CODE(op2) == TREE_INTEGER_CST)
		{
			int divReg = (*registerNo)++;
			int mulReg = (*registerNo)++;
			int resReg = (*registerNo)++;

			int immiValue = INTEGER_CST(op2)->val;
			DIVi(divReg, op1Register, immiValue, "modulo", NULL);
			MULi(mulReg, divReg, immiValue, "modulo", NULL);
			SUB(resReg, op1Register, mulReg, "modulo", NULL);

			return resReg;
		}
		else
		{
			int op2Register = c_codegen_recurse(op2, registerNo, topLevel,
					getAddress, breakLabel, continueLabel);

			int divReg = (*registerNo)++;
			int mulReg = (*registerNo)++;
			int resReg = (*registerNo)++;

			DIV(divReg, op1Register, op2Register, "modulo", NULL);
			MUL(mulReg, divReg, op2Register, "modulo", NULL);
			SUB(resReg, op1Register, mulReg, "modulo", NULL);

			return resReg;
		}
	}
	else
	{
		c_codegen_recurse(op1, registerNo, topLevel, getAddress, breakLabel,
						continueLabel);

		c_codegen_recurse(op2, registerNo, topLevel, getAddress, breakLabel,
				continueLabel);

		return *registerNo;
	}
}