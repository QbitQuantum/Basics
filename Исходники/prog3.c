int main()
{
	char cmd[CMDLEN]; //command string
	
	printf("Welcome to pSQL by 20061201 Kim Dong-Gyu\n");

	while(1){
		__fpurge(stdin); //keep buffer out
		
		printf("pSQL>>"); //prompt
		scanf("%s", cmd); //take a command
	
		if(strcmp(cmd, "CREATE") == 0){
			CREATE();	
		}
		else if(strcmp(cmd, "INFO") == 0){
			INFO();
		}
		else if(strcmp(cmd, "DROP") == 0){
			DROP();
		}
		else if(strcmp(cmd, "QUIT") == 0){
			QUIT();
			return 0;
		}
		else if(strcmp(cmd, "SELECT") == 0){
			SELECT();
		}
		//when a command is fault
		else{
			printf("Please give me a correct command!!\n");
		}
	}

	return 0;
}