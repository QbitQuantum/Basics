FSM_BlockState FSM::transition(char c){
	if(c == EOF && state != STATE_START && state != STATE_COMMENT && state != STATE_HALT_EOF && state != STATE_HALT_OUT_BRACE && state != STATE_HALT_SEMICOLON){
		THROW_ERROR("Unexpected end of file");
	}

	switch(state){
	case STATE_START:
		if(isWhiteSpace(c)){			//Ignore whitespace.
			//Do nothing.
			state = STATE_START;
		} else if(isNumeric(c)){		//Start integer
			intVal = atoi(&c);
			state = STATE_HALT_INTEGER;
		} else {
			//Handle special characters
			switch(c){
			case '+':
				state = STATE_HALT_PLUS;
				break;
			case '-':
				state = STATE_HALT_MINUS;
				break;
			case '*':
				state = STATE_HALT_MULT;
				break;
			case '/':
				state = STATE_HALT_DIVIDE;
				break;
			case '(':
				state = STATE_HALT_IN_PAREN;
				break;
			case ')':
				state = STATE_HALT_OUT_PAREN;
				break;
			case '{':
				state = STATE_HALT_IN_BRACE;
				break;
			case '}':
				state = STATE_HALT_OUT_BRACE;
				break;
			case '=':
				state = STATE_HALT_EQUALS;
				break;
			case '>':
				state = STATE_HALT_GT;
				break;
			case '<':
				state = STATE_HALT_LT;
				break;
			case '!':
				state = STATE_HALT_BANG;
				break;
			case ';':
				state = STATE_HALT_SEMICOLON;
				break;
			case ',':
				state = STATE_HALT_COMMA;
				break;
			case '\"':
				state = STATE_STRING_READ;
				break;
			case '|':
				state = STATE_OR;
				break;
			case '&':
				state = STATE_AND;
				break;
			case EOF:
				state = STATE_HALT_EOF;
				break;
			default:
				//Nothing special, must be an identifier if its valid.
				if(isAlpha(c)){
					state = STATE_HALT_IDENTIFIER;
					currentString<<c;
				}else{
					return FSM_BLOCK;
				}
			}
		}
		break;
	
	case STATE_HALT_INTEGER:
		if(isNumeric(c)){
			//Continue reading the int.
			state = STATE_HALT_INTEGER;
			if(intVal > (INT_MAX - atoi(&c))/10){
				THROW_ERROR("Constant too large!");
			}
			intVal = 10*intVal + atoi(&c);
		} else if(isAlpha(c)) {
			state = STATE_FAIL;
			THROW_ERROR("Variable starting with numeric characters detected!!")
		} else {
			return FSM_BLOCK;
		}
		break;
	case STATE_HALT_IDENTIFIER:
		if(isAlpha(c) || isNumeric(c)){
			currentString<<c;
			state = STATE_HALT_IDENTIFIER;
		}else{
			return FSM_BLOCK;
		}
		break;
	case STATE_HALT_EQUALS:
		if(c == '='){
			state = STATE_HALT_EQUIVALENCE;
		}else{
			return FSM_BLOCK;
		}
		break;
	case STATE_HALT_GT:
		if(c == '='){
			state = STATE_HALT_GTE;
		}else{
			return FSM_BLOCK;
		}
		break;
	case STATE_HALT_LT:
		if(c == '='){
			state = STATE_HALT_LTE;
		}else{
			return FSM_BLOCK;
		}
		break;
	case STATE_HALT_BANG:
		if(c == '='){
			state = STATE_HALT_NE;
		}else{
			return FSM_BLOCK;
		}
		break;
	case STATE_HALT_DIVIDE:
		if(c == '/'){
			state = STATE_COMMENT;
		}else if(c == '*'){
			state = STATE_COMMENT_BLOCK;
		}else{
			return FSM_BLOCK;
		}
		break;
	case STATE_COMMENT:
		//Keep reading and ignoring input untill a new line comes up.
		if(c == '\n' || c == EOF){
			state = STATE_START;
		}		
		break;
	case STATE_COMMENT_BLOCK:
		//Keep reading and ignoring input until a star comes up.
		if(c == '*' || c == EOF){
			state = STATE_COMMENT_BLOCK_STAR;
		}	
		break;
	case STATE_COMMENT_BLOCK_STAR:
		if(c == '/'){
			state = STATE_START;
		}else{
			state = STATE_COMMENT_BLOCK;
		}
		break;

	case STATE_STRING_READ:
		if(c == '\\'){
			state = STATE_STRING_ESCAPE;
		}else if(c == '\"'){
			state = STATE_HALT_STRING_FINISH;
		}else{
			currentString<<c;
		}
		break;
	case STATE_STRING_ESCAPE:
		state = STATE_STRING_READ;
		currentString<<convertEscapeChar(c);
		break;
	case STATE_OR:
		if(c != '|'){
			return FSM_BLOCK;
		}
		state = STATE_HALT_OR;
		break;
	case STATE_AND:
		if(c != '&'){
			return FSM_BLOCK;
		}
		state = STATE_HALT_AND;
		break;

	//States which block on all input
	case STATE_HALT_SEMICOLON:
	case STATE_HALT_IN_PAREN:
	case STATE_HALT_OUT_PAREN:
	case STATE_HALT_IN_BRACE:
	case STATE_HALT_OUT_BRACE:
	case STATE_HALT_COMMA:
	case STATE_HALT_EQUIVALENCE:
	case STATE_HALT_GTE:
	case STATE_HALT_LTE:
	case STATE_HALT_NE:
	case STATE_HALT_MINUS:
	case STATE_HALT_MULT:
	case STATE_HALT_PLUS:
	case STATE_HALT_STRING_FINISH:
	case STATE_HALT_AND:
	case STATE_HALT_OR:
	case STATE_HALT_EOF:
		return FSM_BLOCK;
	default:
		THROW_ERROR("My tummy has got the rumblies!!");
	}