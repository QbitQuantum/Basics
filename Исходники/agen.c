/* Emit an instruction to the assembly program. */
void emit(context* ctx, assembly* casm,
		  int op, operand* op1, operand* op2, operand* opdest)
{
	int nextslot = casm->nextslot;
	operand o = {0};			/* a dummy operand for padding */
#ifdef ZEN_ENABLE_OPTIMIZATION
	/* a simple optimizing trick */
	if (op==opLD && nextslot &&
		casm->instructions[nextslot-1].op==opST &&
		casm->instructions[nextslot-1].op1.ival==op1->ival &&
		casm->instructions[nextslot-1].op2.ival==op2->ival &&
		casm->instructions[nextslot-1].opdest.ival==opdest->ival &&
		!(ctx->inleader&&ctx->insord==0))	/* can't be a leader's first ins */
		return;
#endif
	if (nextslot >= casm->size)	/* buffer is full, reallocate */
	{
		casm->size = casm->size*2+1;
		if ((casm->instructions =
			realloc(casm->instructions, casm->size*sizeof(instruction))) == NULL)
			setlasterror(ctx, ZEN_OUT_OF_MEMORY, "Not enough memory.\n");
	}
	casm->instructions[nextslot].op = op;
	casm->instructions[nextslot].op1 = (op1!=NULL?*op1:o);
	casm->instructions[nextslot].op2 = (op2!=NULL?*op2:o);
	casm->instructions[nextslot].opdest = (opdest!=NULL?*opdest:o);
	casm->nextslot++;
	ctx->insord++;
}