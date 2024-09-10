// private methods
//
Token* PlotFunctionLexer::nextToken() {
    Token* token = 0;
    int tokenLine = getCurrentLineNumber();
    int tokenStart = getCurrentCharNumberInLine();

    try {
        do {
            // Skip whitespace including newlines
            //
            do {
                readChar();
            } while (isWhitespace(peek_));

            switch (peek_) {
            case '.':
                if (isDigit(nextChar()))
                    token = scanNumber();
                else
                    token = new Token(PlotFunctionTerminals::ID_DOT);
                break;  // case '.'

            case '+':
                token = new OperatorToken(PlotFunctionTerminals::ID_PLUS,peek_);
                break;  // case '+'

            case '-':
                token = new OperatorToken(PlotFunctionTerminals::ID_DASH,peek_);
                break;  // case '-'

            case '/':
                token = new OperatorToken(PlotFunctionTerminals::ID_SLASH,peek_);
                break;  // case '/'

            case '*':
                token = new OperatorToken(PlotFunctionTerminals::ID_STAR,peek_);
                break;  // case '*'

            case '[':
                token = new BracketToken(PlotFunctionTerminals::ID_LBRACKET,peek_);
                break;  // case '['

            case ']':
                token = new BracketToken(PlotFunctionTerminals::ID_RBRACKET,peek_);
                break;  // case ']'

            case '(':
                token = new BracketToken(PlotFunctionTerminals::ID_LPAREN,peek_);
                break;  // case '('

            case ')':
                token = new BracketToken(PlotFunctionTerminals::ID_RPAREN,peek_);
                break;  // case ')'

            case '^':
                token = new OperatorToken(PlotFunctionTerminals::ID_CARET,peek_);
                break;  // case '^'

            case ':':
                token = new IsolatorToken(PlotFunctionTerminals::ID_COLON,peek_);
                break;  // case ':'

            case ';':
                token = new IsolatorToken(PlotFunctionTerminals::ID_SEMICOLON,peek_);
                break;  // case ';'

            case ',':
                token = new IsolatorToken(PlotFunctionTerminals::ID_COMMA,peek_);
                break;  // case ','

            case '|':
                token = new IsolatorToken(PlotFunctionTerminals::ID_VERTICAL_BAR,peek_);
                break;  // case '|'

            }   // switch (peek_)

            if (token == 0) {
                if (isAlpha(peek_))
                    token = scanIdentifier();
                else if (isDigit(peek_) || (peek_ == '.'))
                    token = scanNumber();
            }
        } while (token == 0);
    } catch (std::runtime_error&) {
        if (token != 0) {
            token->setLineNumber(tokenLine);
            token->setCharNumber(tokenStart);
        }
        else if (tokenStart == 0)
            token = new IdentifierToken(PlotFunctionTerminals::ID_EMPTY,""); // EMPTY Expression

        return token;
    }

    if (token != 0) {
        token->setLineNumber(tokenLine);
        token->setCharNumber(tokenStart);
    }
    return token;
}