deal_with_declarator(){
	/*处理标识符之后可能存在的数组/函数 */
	switch(cur.type){
		case '[':
			deal_with_arrays();
			break;
		case '(':
			deal_with_function_args();
	}

	deal_with_pointers();

	/* 处理在读入到标识符之前压入到堆栈中的符号 */
	while(top >= 0){
		if(stack[top].type == '('){
			pop;
			gettoken();
			deal_with_declarator();
		}else{
			printf("%s ", pop.string);
		}
	}
}