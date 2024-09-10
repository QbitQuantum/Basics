int main(int argc, char *argv[])
{
	/* program vars */
	byte *m; /* Brain'sFuck Memory */
	byte *p; /* Brain'sFuck Memory pointer */
	u__int i=0;//, c, times = 1;
	byte *stack[STACK_LEVELS];
	u__int stack_l=0;

	/* BF vars */
	byte *mem;
	byte *pos;

	signal(SIGTERM, quitHandler);

/*	if(argc == 3){
		if(argv[1][0] == '-'){
			if(argv[1][1] == 'e') ext = 1;
			else{
				printf("invalid argument %s\n", argv[1]);
				exit(1);
			}
		}
		else{
			printf("try: %s -e file\n", argv[0]);
			exit(1);
		}
	}*/
	if(argc == 2){ // <= 3
		//if(ext == 1) m = loadfile(argv[2]);
		/*else*/ m = loadfile(argv[1]);
	}
	else{
		printf("try: %s [-e] file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	p = m; // program pointer point to program memory start

	mem = alloc_mem(MEM_SIZE);
	pos = mem;

	//start = clock();

	while(*p){
/*		if(ext == 1)
			if(*p >= '0' && *p <= '9'){
				if(!(*(p+1) >= '0' && *(p+1) <= '9')){
					times = *p - '0';
					p++;
				}
			}
		else times = 1;
*/		//for(c=0; c < times; c++){
			switch(*p){
				case '+': (*pos)++; break;
				case '-': (*pos)--; break;
				case '<': pos--; break;
				case '>': pos++; break;
				case '[':
					i=0;
					if(!*pos)
						while(*++p != ']' || i)
							switch(*p){
								case '[': i++; break;
								case ']': i--; break;
							}
					else{
						stack[++stack_l]=p;
					}
					break;
				case ']':
					if(stack_l > 0){
						p = stack[stack_l]-1;
						stack_l--;
					}
					else{
						printf("Syntax error missed ]\n");
						exit(1);
					}
					break;
				case '.': putchar(*pos); break;
				case ',': *pos = getchar();	break;
			}
		//}
		p++;
		//times = 1;
	}
	//end = clock();
	//printf("\nThe program takes %2.2f seconds\n", ((float)end - start) / CLK_TCK);
	return(0);
}