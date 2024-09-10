int Lexical::nextState( int curState, char input ){
                                    //   L,  D,  ",  \,  .,  +,  -,  *,  /,  >,  <,  !,  =,  &,  |,  {,  },  (,  ),',', ;
    int transitions[STATES][INPUTS] = { { 1,  2,  5, -1,  4,  8,  8,  9,  9, 10, 10, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22},
                                        { 1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1,  2, -1, -1,  3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1,  4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        { 5,  5,  7,  6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5},
                                        { 5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
                                        {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1} };
    int next = -1;

    switch( input ){
    case '.':
        next = transitions[curState][POINT];
        break;
    case '\\':
        next = transitions[curState][BACKSLASH];
        break;
    case '\"':
        next = transitions[curState][D_QUOTE];
        break;
    case '+':
        next = transitions[curState][PLUS];
        break;
    case '-':
        next = transitions[curState][MINUS];
        break;
    case '*':
        next = transitions[curState][PROD];
        break;
    case '/':
        next = transitions[curState][DIV];
        break;
    case '>':
        next = transitions[curState][GREATER];
        break;
    case '<':
        next = transitions[curState][LESSER];
        break;
    case '!':
        next = transitions[curState][NOT];
        break;
    case '=':
        next = transitions[curState][EQ];
        break;
    case '&':
        next = transitions[curState][AND];
        break;
    case '|':
        next = transitions[curState][OR];
        break;
    case '{':
        next = transitions[curState][LCB];
        break;
    case '}':
        next = transitions[curState][RCB];
        break;
    case '(':
        next = transitions[curState][LP];
        break;
    case ')':
        next = transitions[curState][RP];
        break;
    case ',':
        next = transitions[curState][COMMA];
        break;
    case ';':
        next = transitions[curState][SEMI_COLON];
    default:
        if( isalpha( input ) or input == '_' ){
            next = transitions[curState][LETTER];
        }
        else if( isdigit( input ) ){
            next = transitions[curState][DIGIT];
        }
        else if( curState == 5 || curState == 6 ){
            next = 5;
        }
        break;
    }

    return next;
}