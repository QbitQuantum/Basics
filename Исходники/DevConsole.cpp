//make this split argList into arg tokens
void ConsoleArguments::TokenizeArgList(){
	char* tokenInBuffer;
	char* currentValue = currentValue = strtok_s(argList, " \0", &tokenInBuffer);

	
	while (currentValue != NULL){
		if (currentValue == NULL)break;

		argTokens.push_back(currentValue);

		currentValue = strtok_s(NULL, " ", &tokenInBuffer);
	}
}