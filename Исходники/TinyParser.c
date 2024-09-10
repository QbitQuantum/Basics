//Initialize everything
void Initialize2(char in[], char out[]){

	int tokens = 0;
	int i = 0;
	char tmp;

	//count the number of tokens in file for proper allocation
	fp = fopen(in, "r");
	while(!feof(fp)){
		tmp = fgetc(fp);
		if(tmp == ' ') tokens++;
	}

	//allocate space for our input and token variable
	token = malloc(sizeof(char*)* 12);
	input = malloc(sizeof(char*) * tokens+2);
	for(i = 0; i < tokens+2; i++){
		input[i] = malloc(sizeof(char) * 12);
	}

	fclose(fp);
	fp = fopen(in, "r");

	//read our rokens
	for(i = 0; i < tokens; i++){
		fscanf(fp, "%s", input[i]);
	}

	fclose(fp);
	fp = fopen(out, "w");

	//create our symbol table and our code list
	int tableSize = 100;
	st = CreateTable(tableSize);
	codegen = malloc(sizeof(code*) * (tableSize * 10));

}