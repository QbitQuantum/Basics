void OperandStack::drem(){
    Operand op1H, op1L, op2H, op2L;
    
    op2L = pop();
    op2H = pop();
    op1L = pop();
    op1H = pop();
    
    if( (op1H.type != TYPE_DOUBLE) || (op2H.type != TYPE_DOUBLE) ||
        (op1H.type != TYPE_DOUBLE) || (op2H.type != TYPE_DOUBLE)    ) {
        printf("Error type not double: :op_stack.drem\n");
        exit(0);
    }
    double val1, val2, val3;
    
    val1 = to_double(op1H.bytes, op1L.bytes);
    val2 = to_double(op2H.bytes, op2L.bytes);
    val3 = remainder(val1, val2);
    
    op1H.set_high(TYPE_DOUBLE, &val3);
    op1L.set_low(TYPE_DOUBLE, &val3);
    push(op1H);
    push(op1L);
    
    /*if(size < 4) {
		printf("Error  :op_stack.drem\n");
		exit(0);
	}
	if( ( (top-1)->bytes == 0x0 ) && (top->bytes==0x0) ) {
		exception("ArithmeticException: / by zero at OpStack.drem");
	}
	__opDrem(top);
	top-=2;
	size-=2;*/
}