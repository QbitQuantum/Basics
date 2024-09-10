Token* AnnotationLexer::nextToken() {
    Token* token = 0;
    int tokenLine = getCurrentLineNumber();
    int tokenStart = getCurrentCharNumberInLine();

    try {
        do {
            if (readingString_) {
                readChar();
                if (peek_ == '"') {
                    readingString_ = false;
                    return new Token(AnnotationTerminals::ID_QUOTE);
                } else {
                    std::string str;
                    do {
                        str += peek_;
                        if (nextChar() != '"')
                            readChar();
                        else
                            break;
                    } while (true);
                    return new StringToken(AnnotationTerminals::ID_STRING, str);
                }
            }

            // Skip whitespace including newlines
            //
            do {
                readChar();
            } while (isWhitespace(peek_));

            switch (peek_) {
                case '@':
                    token = new Token(AnnotationTerminals::ID_AT);
                    break;

                case '=':
                    token = new Token(AnnotationTerminals::ID_EQUAL);
                    break;

                case '[':
                    token = new Token(AnnotationTerminals::ID_LBRACKET);
                    break;

                case ']':
                    token = new Token(AnnotationTerminals::ID_RBRACKET);
                    break;

                case ',':
                    token = new Token(AnnotationTerminals::ID_COMMA);
                    break;

                case '\"':
                    token = new Token(AnnotationTerminals::ID_QUOTE);
                    readingString_ = true;
                    break;

                case '\'':
                    token = new Token(AnnotationTerminals::ID_APOSTROPHE);
                    break;
            }   // switch (peek_)

            if (token == 0) {
                if (isAlpha(peek_))
                    token = scanIdentifier(AnnotationTerminals::ID_IDENTIFIER);
                else if (isDigit(peek_) || (peek_ == '.'))
                    token = scanNumber();
            }
        } while (token == 0);
    } catch (std::runtime_error&) {
        if (token != 0) {
            token->setLineNumber(tokenLine);
            token->setCharNumber(tokenStart);
        }

        return token;
    }

    if (token != 0) {
        token->setLineNumber(tokenLine);
        token->setCharNumber(tokenStart);
    }
    return token;
}