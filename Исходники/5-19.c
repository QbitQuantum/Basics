int main(int argc, char *argv[]){
	char temp[MAXTOKEN];
	while(gettoken() != EOF){
		if(tokentype == PARENS || tokentype == BRACKETS){
			strcat(out, token);	
		}
		else if(tokentype == '*'){
			nexttoken();
			if(tokentype == PARENS || tokentype == BRACKETS){
				sprintf(temp, "(*%s)", out);
			}else{
				sprintf(temp, "*%s", out);
			}
			strcpy(out, temp);
		}
		else if(tokentype == NAME){
			sprintf(temp, "%s %s", token, out);
			strcpy(out, temp);
		}
	}
	printf("%s\n", out);
	return 0;
}