int main(){
	
    char buf[MAXLINE] = "";
	double num1 = 0,num2 = 0, num = 0;
	int i = 0;
	stack* stk = stack_create(MAXLINE);
	
	freopen("log.txt", "w+", stderr);
	
	fprintf(stderr, "No problem"); //clean log file
	
	fgets(buf, MAXLINE, stdin);

	while(buf[i] != '\n'){

		switch (buf[i]) {
			case '+': case '*': case '/': case '^': case 'l':
			  
				assert(stack_head(stk) >= 1);
				
				num1 = pop(stk);
				num2 = pop(stk);
				num = calculate(num2, num1, buf[i]);
				push(stk, num);
				break;
			case '-':
				if (buf[i + 1] == ' '){
					
					assert(stack_head(stk) >= 1);
					
					num1 = pop(stk);
					num2 = pop(stk);
					num = calculate(num2, num1, buf[i]);
					push(stk, num);
				}
				else {  
					i = float_reader(buf, i, &num);
					push(stk, num);
				}
				break;
			case '1': case '2': case '3': case '4': case '5': \
			case '6': case '7': case '8': case '9': case '0':
				i = float_reader(buf, i, &num);
				push(stk, num);
				break;
			default:
			printf("incorrect operation");
			abort();
		}
		++i;
	}
	
	if (stack_head(stk) != 0){
	errno = EINVAL;
	perror("Incorrect input expression\n");
	abort();
	}
	
	if (errno != 0){
		printf("program failed");
		abort();
	}
	printf("%lg\n", pop(stk));
	stack_delete(stk);
	return 0;
}