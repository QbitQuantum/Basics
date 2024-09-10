t_token nextToken(void){
    tokenString = "";
    hasTokenSecundario = false;
    // loop do estado inicial para pular os separadores
    while(isspace(nextChar)){
        nextChar = readChar();
    }
    
    if(nextChar == EOF){
        token = ENDFILE;
        return token;
    }
    
    if( isalpha(nextChar) ){
        do {
            tokenString = tokenString + nextChar;
            nextChar = readChar();
        } while( isalnum(nextChar) || nextChar == '_' );
        token = searchKeyWord(tokenString);
        //std::cout << "Read:" << text << ", Token: " << token;
        if(token == IDT){
            tokenSecundario = searchName(tokenString);
            hasTokenSecundario = true;
            //std::cout << ", Token Secundario IDT " << tokenSecundario << std::endl;
        }
        else{
            //std::cout << std::endl;
        }
    }
    else if( isdigit(nextChar) ){
        char numeral[MAX_NUM_LEN+1];
        int i = 0;
        //std::cout << "Read: ";
        do{
            tokenString = tokenString + nextChar;
            numeral[i++] = nextChar;
            //std::cout << nextChar;
            nextChar = readChar();
        }while( isdigit(nextChar) );
        numeral[i] = '\0';
        token = NUMERAL;
        //std::cout << ", Token: " << token;
        tokenSecundario = addIntConst(atoi(numeral));
        hasTokenSecundario = true;
        //std::cout << ", Token Secundario Const: " << tokenSecundario << std::endl;
    } else if( nextChar == '"' ){
        tokenString = "";
        nextChar = readChar();
        while(nextChar != '"'){
            tokenString += nextChar;
            nextChar = readChar();
        }
        token = STRINGVAL;
        char* cstr = new char[tokenString.size()+1];
        memcpy(cstr, tokenString.c_str(), tokenString.size()+1);
        tokenSecundario = addStringConst(cstr);
        hasTokenSecundario = true;
        nextChar = readChar();
        //std::cout << "Read: " << tokenString << ", Token: " << token << ", Token Secundario Const: " << tokenSecundario << std::endl;
    }else if( nextChar == '\''){
        nextChar = readChar();
        tokenString = nextChar;
        token = CHARACTER;
        tokenSecundario = addCharConst(nextChar);
        hasTokenSecundario = true;
        //std::cout << "Read: " << '\'' << nextChar << '\'' << ", Token: " << token << ", Token Secundario Const: " << tokenSecundario << std::endl;
        nextChar = readChar(); //pular o '
        nextChar = readChar();
    }
    else{ //SIMBOLOS
        //std::cout << "Read: " << nextChar;
        tokenString = nextChar;
        switch(nextChar){
            case ':':
                nextChar = readChar();
                token = COLON;
                break;
            case ';':
                nextChar = readChar();
                token = SEMI_COLON;
                break;
            case ',':
                nextChar = readChar();
                token = COMMA;
                break;
            case '[':
                nextChar = readChar();
                token = LEFT_SQUARE;
                break;
            case ']':
                nextChar = readChar();
                token = RIGHT_SQUARE;
                break;
            case '{':
                nextChar = readChar();
                token = LEFT_BRACES;
                break;
            case '}':
                nextChar = readChar();
                token = RIGHT_BRACES;
                break;
            case '(':
                nextChar = readChar();
                token = LEFT_PARENTHESIS;
                break;
            case ')':
                nextChar = readChar();
                token = RIGHT_PARENTHESIS;
                break;
            case '&':
                nextChar = readChar();
                if(nextChar == '&'){
                    tokenString += nextChar;
                    token = AND;
                    nextChar = readChar();
                }
                else{
                    token = UNKNOWN;
                }
                break;
            case '|':
                nextChar = readChar();
                if(nextChar == '|'){
                    tokenString += nextChar;
                    token = OR;
                    nextChar = readChar();
                }
                else{
                    token = UNKNOWN;
                }
                break;
            case '=':
                nextChar = readChar();
                if( nextChar == '=' )
                {
                    tokenString += nextChar;
                    token = EQUAL_EQUAL;
                    nextChar = readChar();
                } else {
                    token = EQUALS;
                } break;
            case '<':
                nextChar = readChar();
                if( nextChar == '=' )
                {
                    tokenString += nextChar;
                    token = LESS_OR_EQUAL;
                    nextChar = readChar();
                } else {
                    token = LESS_THAN;
                } break;
            case '>':
                nextChar = readChar();
                if( nextChar == '=' )
                {
                    tokenString += nextChar;
                    token = GREATER_OR_EQUAL;
                    nextChar = readChar();
                } else {
                    token = GREATER_THAN;
                } break;
            case '!':
                nextChar = readChar();
                if( nextChar == '=' )
                {
                    tokenString += nextChar;
                    token = NOT_EQUAL;
                    nextChar = readChar();
                } else {
                    token = NOT;
                } break;
            case '+':
                nextChar = readChar();
                if( nextChar == '+' )
                {
                    tokenString += nextChar;
                    token = PLUS_PLUS;
                    nextChar = readChar();
                } else {
                    token = PLUS;
                } break;
            case '-':
                nextChar = readChar();
                if( nextChar == '-' )
                {
                    tokenString += nextChar;
                    token = MINUS_MINUS;
                    nextChar = readChar();
                } else {
                    token = MINUS;
                } break;
            case '*':
                nextChar = readChar();
                token = TIMES;
                break;
            case '/':
                nextChar = readChar();
                token = DIVIDE;
                break;
            case '.':
                nextChar = readChar();
                token = DOT;
                break;
            default:
                token = UNKNOWN;
        }
        //std::cout << ", Token: " << token << std::endl;
    }
    
    return token;
}