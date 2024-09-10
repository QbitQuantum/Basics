token * nextToken(token *current,char *buffer,bool delPrev) {
	token * result=newToken();

	if (current!=NULL) {
		result->location=current->location+current->length;
		if (delPrev) freeToken(current);
	}

	while(result->length==0) {
		if (result->location >= strlen(buffer)) {
			free(result);
			return NULL;
		}
		switch(buffer[result->location]) {
			case ' ':
			case '\t':
				result->location=result->location+1;
				continue;
			case '+':
				result->type=PLUS;
				result->length=1;
				break;
			case '-':
				result->type=MINUS;
				result->length=1;
				break;
			case '*':
				result->type=MULTIPLY;
				result->length=1;
				break;
			case '/':
				result->type=DIVIDE;
				result->length=1;
				break;
			case ';' :
				result->type=EOS;
				result->length=1;
				break;
			case '(':
				result->type=LPAREN;
				result->length=1;
				break;
			case ')':
				result->type=RPAREN;
				result->length=1;
				break;
			case '{':
				result->type=LCURLY;
				result->length=1;
				break;
			case '}' :
				result->type=RCURLY;
				result->length=1;
				break;

			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				result->type=INTEGER;
				char *endptr;
				setValue(result,strtol(buffer+result->location,&endptr,10));
				result->length=(endptr-buffer)-result->location;
				break;

			case 's':
				if (0==strncmp(buffer+result->location,"set",3)) {
					if ( (strlen(buffer)<=result->location+3) ||
					     (buffer[result->location+3]==' ')   ) {
						result->type=SET;
						result->length=3;
						break;
					}
				}
				int ei=0;
				char varName[20];
				while(isalpha((int)buffer[result->location+ei])) {
					varName[ei]=buffer[result->location+ei];
					if (ei>=strlen(buffer)) break;
					ei++;
					varName[ei]='\0';
				}
				result->type=VARIABLE;
				setName(result,varName);
				result->length=ei;
				break;

			case 'w':
				if (0==strncmp(buffer+result->location,"while",5)) {
					if ( (strlen(buffer)<=result->location+5) ||
					     (buffer[result->location+5]==' ') ||
					     (buffer[result->location+5]=='(') ) {
							result->type=WHILE;
							result->length=5;
							break;
					}
				}
				ei=0;
				while(isalpha((int)buffer[result->location+ei])) {
					varName[ei]=buffer[result->location+ei];
					if (ei>=strlen(buffer)) break;
					ei++;
					varName[ei]='\0';
				}
				result->type=VARIABLE;
				setName(result,varName);
				result->length=ei;
				break;

			default:

				if (isalpha((int)buffer[result->location])) {
					ei=0;
					while(isalpha((int)buffer[result->location+ei])) {
						varName[ei]=buffer[result->location+ei];
						if (ei>=strlen(buffer)) break;
						ei++;
						varName[ei]='\0';
					}
					result->type=VARIABLE;
					setName(result,varName);
					result->length=ei;
					break;
				}

				tokenError("Unrecognized token in expression",buffer,result);
				free(result);
				exit(1);
		}
	}
	return result;
}